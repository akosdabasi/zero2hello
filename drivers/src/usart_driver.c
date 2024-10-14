#include "usart_driver.h"
#include "nvic.h"

#define USART_ENABLE(pUSART)                SET_BIT(pUSART->CR1, USART_CR1_UE_Pos)
#define USART_ENABLE_RX(pUSART)             SET_BIT(pUSART->CR1, USART_CR1_RE_Pos)
#define USART_ENABLE_TX(pUSART)             SET_BIT(pUSART->CR1, USART_CR1_TE_Pos)
#define USART_ENABLE_RX_IT(pUSART)          SET_BIT(pUSART->CR1, USART_CR1_RXNEIE_Pos)
#define USART_ENABLE_TX_IT(pUSART)          SET_BIT(pUSART->CR1, USART_CR1_TXEIE_Pos)
#define USART_ENABLE_PE_IT(pUSART)          SET_BIT(pUSART->CR1, USART_CR1_PEIE_Pos)
#define USART_ENABLE_TCIE_IT(pUSART)        SET_BIT(pUSART->CR1, USART_CR1_TCIE_Pos)
#define USART_ENABLE_IDLEIE_IT(pUSART)      SET_BIT(pUSART->CR1, USART_CR1_IDLEIE_Pos)

#define USART_DISABLE(pUSART)               CLEAR_BIT(pUSART->CR1, USART_CR1_UE_Pos)
#define USART_DISABLE_TX(pUSART)            CLEAR_BIT(pUSART->CR1, USART_CR1_TE_Pos)
#define USART_DISABLE_RX(pUSART)            CLEAR_BIT(pUSART->CR1, USART_CR1_RE_Pos)
#define USART_DISABLE_TX_IT(pUSART)         CLEAR_BIT(pUSART->CR1, USART_CR1_TXEIE_Pos)
#define USART_DISABLE_RX_IT(pUSART)         CLEAR_BIT(pUSART->CR1, USART_CR1_RXNEIE_Pos)
#define USART_DISABLE_PE_IT(pUSART)         CLEAR_BIT(pUSART->CR1, USART_CR1_PEIE_Pos)
#define USART_DISABLE_TCIE_IT(pUSART)       CLEAR_BIT(pUSART->CR1, USART_CR1_TCIE_Pos)
#define USART_DISABLE_IDLEIE_IT(pUSART)     CLEAR_BIT(pUSART->CR1, USART_CR1_IDLEIE_Pos)

#define USART_GET_RXNEIE(pUSART)            GET_BIT(pUSART->CR1, USART_CR1_RXNEIE_Pos)
#define USART_GET_TXEIE(pUSART)             GET_BIT(pUSART->CR1, USART_CR1_TXEIE_Pos)
#define USART_GET_OVE(pUSART)               GET_BIT(pUSART->SR, USART_SR_OVE_Pos)
#define USART_GET_FE(pUSART)                GET_BIT(pUSART->SR, USART_SR_FE_Pos)
#define USART_GET_NE(pUSART)                GET_BIT(pUSART->SR, USART_SR_NE_Pos)
#define USART_GET_PE(pUSART)                GET_BIT(pUSART->SR, USART_SR_PE_Pos)
#define USART_GET_IDLE(pUSART)              GET_BIT(pUSART->SR, USART_SR_IDLE_Pos)
#define USART_GET_TXE(pUSART)               GET_BIT(pUSART->SR, USART_SR_TXE_Pos)
#define USART_GET_TC(pUSART)                GET_BIT(pUSART->SR, USART_SR_TC_Pos)
#define USART_GET_RXNE(pUSART)              GET_BIT(pUSART->SR, USART_SR_RXNE_Pos)
#define USART_GET_LBD(pUSART)               GET_BIT(pUSART->SR, USART_SR_LBD_Pos)
#define USART_GET_CTS(pUSART)               GET_BIT(pUSART->SR, USART_SR_CTS_Pos)

//global usart config structures
USART_Config_t usart1_cfg;
USART_Config_t usart2_cfg;
USART_Config_t usart3_cfg;
//global usart handlers
usart_handle_t husart1 = {.instance = USART1, .cfg = &usart1_cfg};
usart_handle_t husart2 = {.instance = USART2, .cfg = &usart2_cfg};
usart_handle_t husart3 = {.instance = USART3, .cfg = &usart3_cfg};

//default event handler
static void usart_default_cb(usart_handle_t *const husart, usart_event_t event)
{
  /*switch (event)
  {
  case USART_EVENT_BYTE_RECEIVED:
    // code 
    break;
  case USART_EVENT_BYTE_SENT:
    // code
    break;
  case USART_EVENT_TRANS_COMPLETE:
    // code
    break;
  case USART_EVENT_OVE_ERR:
    // code 
    break;
  case USART_EVENT_PE_ERR:
    // code
    break;
  case USART_EVENT_IDLE_RECEIVED:
    // code
    break;
  default:
    // invalid event
      break;
  }
  */
 (void)husart;
 (void)event;
}

void usart_get_default_cfg(USART_Config_t *pCfg)
{
  if(!pCfg)return;

  pCfg->mode = USART_MODE_TX_RX;                  //enable both transmit and receive
  pCfg->data_length = USART_DATA_LENGTH_8;      
  pCfg->parity = USART_PARITY_NONE;     
  pCfg->stop_bits = USART_STOP_BITS_1;  
  //pCfg->oversampl = USART_OVERSAMPLING_16;  
  pCfg->baudrate = USART_BAUDRATE_9600;            
  pCfg->hw_flow_ctrl = USART_HW_FLOWCTRL_NONE;    //no hardware flow control
  pCfg->wakeup = USART_WAKEUP_IDLE;
}

void usart_clk_enable(usart_handle_t *const husart)
{
  if(!husart || !husart->instance)return;

  USART_t *pUSART = husart->instance;
  
  if(pUSART == USART1)
  {
    RCC_APB2ENR_USART1_CLK_ENABLE();
  }
  else if(pUSART == USART2)
  {
    RCC_APB1ENR_USART2_CLK_ENABLE();
  }
  else if(pUSART == USART3)
  {
    RCC_APB1ENR_USART3_CLK_ENABLE();
  }
  else
  {
    /*invalid instance*/
  }
}

void usart_clk_disable(usart_handle_t *const husart)
{
  if(!husart || !husart->instance)return;

  USART_t *pUSART = husart->instance;
  
  if(pUSART == USART1)
  {
    RCC_APB2ENR_USART1_CLK_DISABLE();
  }
  else if(pUSART == USART2)
  {
    RCC_APB1ENR_USART2_CLK_DISABLE();
  }
  else if(pUSART == USART3)
  {
    RCC_APB1ENR_USART3_CLK_DISABLE();
  }
  else
  {
    /*invalid instance*/
  }
}

void usart_reset(usart_handle_t *const husart)
{
  if(!husart || !husart->instance)return;

  USART_t *pUSART = husart->instance;
  
  if(pUSART == USART1)
  {
    RCC_APB2RSTR_USART1_RESET();
  }
  else if(pUSART == USART2)
  {
    RCC_APB1RSTR_USART2_RESET();
  }
  else if(pUSART == USART3)
  {
    RCC_APB1RSTR_USART3_RESET();
  }
  else
  {
    /*invalid instance*/
  }
}

void usart_init(usart_handle_t *const husart)
{
  if(!husart || !husart->instance || !husart->cfg)return;

  USART_t *pUSART = husart->instance;
  USART_Config_t *pCfg = husart->cfg;
  usart_clk_enable(husart);

  EN_DIS_BIT(pUSART->CR1,USART_CR1_M_Pos,pCfg->data_length);
  EN_DIS_BIT(pUSART->CR1,USART_CR1_WAKE_Pos,pCfg->wakeup);
  //parity control
  state_t tmp = pCfg->parity > USART_PARITY_NONE ? enabled : disabled;
  EN_DIS_BIT(pUSART->CR1,USART_CR1_PCE_Pos,tmp);
  
  //parity
  tmp = pCfg->parity == USART_PARITY_ODD ? enabled : disabled;
  EN_DIS_BIT(pUSART->CR1,USART_CR1_PS_Pos,tmp);

  //stopbits
  CLEAR_BITFIELD(pUSART->CR2, USART_CR2_STOP_Msk);
  pUSART->CR2 |= (pCfg->stop_bits << USART_CR2_STOP_Pos);

  if(!husart->cb)
  {
    husart->cb = usart_default_cb;
  }

  //configuring the baudrate
  uint32_t fck = husart == &husart1 ? rcc_get_pclk2() : rcc_get_pclk1();
  uint32_t div_100 = fck*100/16/pCfg->baudrate;
  uint32_t div_mantissa = div_100/100;
  uint32_t div_fraction = (((div_100-(div_mantissa*100))*16)+50)/100;
  //carry
  if(div_fraction == 16)div_mantissa++;
  CLEAR_BITFIELD(pUSART->BRR, USART_BRR_DIV_Mantissa_Msk | USART_BRR_DIV_Fraction_Msk);
  pUSART->BRR |= ((div_mantissa & 0x0FFFu) << USART_BRR_DIV_Mantissa_Pos) | (div_mantissa & 0x0Fu);

  USART_ENABLE_RX(pUSART);
  USART_ENABLE_TX(pUSART);
  //todo hardware flow control 
  //todo synchronous mode
  //USART_ENABLE(pUSART);
}

void usart_transmit(usart_handle_t *const husart, uint8_t *data, uint8_t length)
{
  if(!husart || !husart->instance || !husart->cfg)return;

  USART_t *pUSART = husart->instance;
  //TODO: checking parity and data length 
  //usart_data_length_t data_length = husart->cfg->data_length; 
  //usart_parity_t data_length = husart->cfg->parity; 


  USART_ENABLE(pUSART);

  for (uint8_t i = 0; i < length; i++)
  {
    //wait until the transmit data register (TDR) is empty
    while (!USART_GET_TXE(pUSART));  
    
    // load the data into the transmit data register (TDR)
    pUSART->DR = data[i];
  }

  // wait until the transmission is complete 
  while (!USART_GET_TC(pUSART));  
  
}

void usart_receive(usart_handle_t *const husart, uint8_t *data, uint8_t length)
{
  if(!husart || !husart->instance || !husart->cfg)return;

  USART_t *pUSART = husart->instance;
  //TODO: checking parity and data length 
  //usart_data_length_t data_length = husart->cfg->data_length; 
  //usart_parity_t data_length = husart->cfg->parity;

  USART_ENABLE(pUSART);

  for (uint8_t i = 0; i < length; i++)
  {
    // wait until the receive data register (RDR) is not empty (RXNE bit set)
    while (!USART_GET_RXNE(pUSART));

    // Read the received data from the data register (DR)
    data[i] = (uint8_t)(pUSART->DR);
  }
}

void usart_nvic_enable_it(usart_handle_t* husart)
{
  if(husart == &husart1)
  {
    __NVIC_EnableIRQ(USART1_IRQn);
  }
  else if(husart == &husart2)
  {
    __NVIC_EnableIRQ(USART2_IRQn);
  }
  if(husart == &husart3)
  {
    __NVIC_EnableIRQ(USART3_IRQn);
  }
}

void usart_nvic_disable_it(usart_handle_t* husart)
{
  if(husart == &husart1)
  {
    __NVIC_DisableIRQ(USART1_IRQn);
  }
  else if(husart == &husart2)
  {
    __NVIC_DisableIRQ(USART2_IRQn);
  }
  if(husart == &husart3)
  {
    __NVIC_DisableIRQ(USART3_IRQn);
  }
}

void usart_transmit_it(usart_handle_t *const husart, uint8_t *data, uint8_t length)
{
  //if one of the pointers is a null pointer then return
  if(!husart || !husart->instance || !data )return;
  USART_t *const pUSART = husart->instance;

  //if previous transmission is not finished then return
  if(husart->tx_buffer_length)return;

  //set handle members
  husart->tx_buffer = data;
  husart->tx_buffer_length = length;

  //enable interrupts in NVIC
  usart_nvic_enable_it(husart);

  //enable peripheral
  USART_ENABLE(pUSART);

  //enable interrupts
  USART_ENABLE_TX_IT(pUSART);
}

void usart_receive_it(usart_handle_t *const husart, uint8_t *data, uint8_t length)
{
  //if one of the pointers is a null pointer then return
  if(!husart || !husart->instance || !data )return;
  USART_t *const pUSART = husart->instance;

  //if previous reception is not finished then return
  if(husart->rx_buffer_length)return;

  //set handle members
  husart->rx_buffer = data;
  husart->rx_buffer_length = 0;
  husart->rx_bytes_left = length;

  //enable interrupts in NVIC
  usart_nvic_enable_it(husart);

  //enable peripheral
  USART_ENABLE(pUSART);

  //enable interrupts
  USART_ENABLE_RX_IT(pUSART);
}

void usart_register_cb(usart_handle_t *const husart, usart_callback_t cb)
{
  if(!husart || !cb)return;

  husart->cb = cb;
}

static inline void usart_handle_txe_it(usart_handle_t *husart)
{
  USART_t *pUSART = husart->instance;
  if(husart->tx_buffer_length > 0)
  {
    //write the next byte to Tx buffer
    pUSART->DR = *husart->tx_buffer++;
    husart->tx_buffer_length--;
    
    //call event handler
    husart->cb(husart, USART_EVENT_BYTE_SENT);
  }
  else
  {
    //end transmission
    USART_DISABLE_TX_IT(pUSART);

    //call user callback with received data
    husart->cb(husart, USART_EVENT_TRANS_COMPLETE);

    //reset tx buffer
    husart->tx_buffer = NULL;
  }
}

static inline void usart_handle_rxne_it(usart_handle_t *husart)
{
  USART_t *pUSART = husart->instance;

  //get the arrived data
  husart->rx_buffer[husart->rx_buffer_length++] = (uint8_t)pUSART->DR;
  husart->rx_bytes_left--;
    
  if(husart->rx_bytes_left > 0)
  {
    //call user callback with received data
    husart->cb(husart, USART_EVENT_BYTE_RECEIVED);
  }
  else
  {
    //end reception
    USART_DISABLE_RX_IT(pUSART);

    //call user callback with received data
    husart->cb(husart, USART_EVENT_RECEPTION_COMPLETE);

    //reset rx buffer
    husart->rx_buffer = NULL;
    husart->rx_buffer_length = 0;
  }
}

static inline void USARTx_IRQHandler(usart_handle_t *husart)
{
  if(!husart || !husart->instance)return;

  USART_t *pUSART = husart->instance;

  if(USART_GET_TXE(pUSART) && USART_GET_TXEIE(pUSART))
  {
    usart_handle_txe_it(husart);
  }

  if(USART_GET_RXNE(pUSART) && USART_GET_RXNEIE(pUSART))
  {
    usart_handle_rxne_it(husart);
  }

  //TODO: error handling
  
}

void USART1_IRQHandler(void)
{
  USARTx_IRQHandler(&husart1);
}

void USART2_IRQHandler(void)
{
  USARTx_IRQHandler(&husart2);
}

void USART3_IRQHandler(void)
{
  USARTx_IRQHandler(&husart3);
}