#include "module.h"
#include "_string.h"
#include "ttys.h"

//private variables
//-------------------------

ttys_handle_t httys1 = {.husart = &husart1};
ttys_handle_t httys2 = {.husart = &husart2}; //stdout
ttys_handle_t httys3 = {.husart = &husart3};

//names of performance measurements.
/*static const char* pms_names[NUM_PMS] = {
  "uart rx overrun err",
  "uart rx noise err",
  "uart rx frame err",
  "uart rx parity err",
  "tx buf overrun err",
  "rx buf overrun err",
};*/

//public functions
//----------------------------
int32_t ttys_get_def_cfg(ttys_cfg_t* cfg)
{
  if (!cfg)return MOD_ERR_ARG;

  cfg->send_cr_after_nl = enabled;
  return 0;
}

int32_t ttys_init(ttys_handle_t *const httys)
{
  if(!(httys == &httys1 || httys == &httys2 || httys == &httys3)) return MOD_ERR_BAD_INSTANCE;
  
  ttys_cfg_t const *const cfg = &(httys->cfg);

  if(!cfg)return MOD_ERR_ARG;

  //reset ttys state
  if(httys->tx_buf_get_idx >= TTYS_TX_BUF_SIZE || httys->tx_buf_put_idx >= TTYS_TX_BUF_SIZE)
  {
    //*httys = (ttys_handle_t){0};
    _memset((uint8_t*)httys, 0u, sizeof(*httys));
  }
  else
  {
    httys->rx_buf_get_idx = 0;
    httys->rx_buf_put_idx = 0;
  }

  return 0;
}

int32_t ttys_start(ttys_handle_t *const httys)
{
  if(!(httys == &httys1 || httys == &httys2 || httys == &httys3)) return MOD_ERR_BAD_INSTANCE;

  //enable interrupts
  usart_enable_it_rx(httys->husart);
  usart_enable_it_tx(httys->husart);

  usart_nvic_enable_it(httys->husart);
  return 0;
}

// Other APIs.
int32_t ttys_putc(ttys_handle_t *const httys, char c)
{
  uint16_t next_put_idx;

  if(!(httys == &httys1 || httys == &httys2 || httys == &httys3)) return MOD_ERR_BAD_INSTANCE;

  //calculate the new TX buffer put index
  next_put_idx = httys->tx_buf_put_idx + 1;
  if (next_put_idx >= TTYS_TX_BUF_SIZE)
  {
    next_put_idx = 0;
  }

  //if buffer is full, then return error.
  while(next_put_idx == httys->tx_buf_get_idx)
  {
    httys->pms[CNT_TX_BUF_OVERRUN]++;
    return MOD_ERR_BUF_OVERRUN;
  }

  //put the char in the TX buffer.
  httys->tx_buf[httys->tx_buf_put_idx] = c;
  httys->tx_buf_put_idx = next_put_idx;

  //ensure the TX interrupt is enabled.
  //TODO: should we disable interrupts?
  usart_enable_it_tx(httys->husart);
  
  return 0;
}

int32_t ttys_getc(ttys_handle_t *const httys, char* c)
{
  uint16_t next_get_idx;

  if(!(httys == &httys1 || httys == &httys2 || httys == &httys3)) return MOD_ERR_BAD_INSTANCE;

  //check if buffer is empty.
  if (httys->rx_buf_get_idx == httys->rx_buf_put_idx)return 0;

  //get a character
  *c = httys->rx_buf[httys->rx_buf_get_idx];

  //advance the get index
  next_get_idx = httys->rx_buf_get_idx + 1;
  if (next_get_idx >= TTYS_RX_BUF_SIZE)
  {
    next_get_idx = 0;
  }
  httys->rx_buf_get_idx = next_get_idx;
  return 1;
}

//---------------- INTERRUPT HANDLING ---------------------

static void ttys_interrupt(ttys_handle_t *const httys)
{

  USART_t *const pUSART = httys->husart->instance;

  if(USART_GET_RXNE(pUSART))
  {
    //read incoming character.
    char rx_data =(uint8_t)pUSART->DR;
    
    //advance the rx put index
    uint16_t next_rx_put_idx = httys->rx_buf_put_idx + 1;
    if(next_rx_put_idx >= TTYS_RX_BUF_SIZE)
    {
      next_rx_put_idx = 0;
    }

    //if rx buffer is full
    if(next_rx_put_idx == httys->rx_buf_get_idx)
    {
      httys->pms[CNT_RX_BUF_OVERRUN]++;
    }
    else
    {
      httys->rx_buf[httys->rx_buf_put_idx] = rx_data;
      httys->rx_buf_put_idx = next_rx_put_idx;
    }
  }

  if(USART_GET_TXE(pUSART))
  {
    //can send a character.
    if (httys->tx_buf_get_idx == httys->tx_buf_put_idx)
    {
      //no characters to send, disable the interrrupt.
      usart_disable_it_tx(httys->husart);
    }
    else
    {
      httys->husart->instance->DR = httys->tx_buf[httys->tx_buf_get_idx];
      if (httys->tx_buf_get_idx < TTYS_TX_BUF_SIZE-1)
          httys->tx_buf_get_idx++;
      else
          httys->tx_buf_get_idx = 0;
    }
  }


  //error conditions, to clear the bit, we need to read the dataregister, but we don't use it.
  (void)httys->husart->instance->DR;
  if(USART_GET_OVE(pUSART))httys->pms[CNT_RX_UART_ORE]++;
  if(USART_GET_NE(pUSART))httys->pms[CNT_RX_UART_NE]++;
  if(USART_GET_FE(pUSART))httys->pms[CNT_RX_UART_FE]++;
  if(USART_GET_PE(pUSART))httys->pms[CNT_RX_UART_PE]++;
}

void USART1_IRQHandler(void)
{
  ttys_interrupt(&httys1);
}

void USART2_IRQHandler(void)
{
  ttys_interrupt(&httys2);
}

void USART3_IRQHandler(void)
{
  ttys_interrupt(&httys3);
}