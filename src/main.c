#include "user_snippets.h"
#include "rcc_clk_cfg.h"

//input buffer
uint8_t rx_data[10];

//output buffer
uint8_t tx_data[10];

void usartEventHandler(usart_handle_t *const husart, usart_event_t event)
{
  (void)husart;
  if(event == USART_EVENT_RECEPTION_COMPLETE)
  {
    char c = husart2.rx_buffer[0];
    if(c == '\n' || c == '\r')
    {
      tx_data[0] = '\n';
      tx_data[1] = '\r';
      usart_transmit_it(&husart2, tx_data, 2u);

    }
    else
    {
      tx_data[0] = c;
      usart_transmit_it(&husart2, tx_data, 1u);
    }
  }
}

int main(void) 
{

  /*System timer config*/
  rcc_cfg_systick(TICK_PERIOD_MS);

  /*USART2 config*/
  config_usart2();
  usart_init(&husart2);
  usart_register_cb(&husart2, usartEventHandler);
  
  while(1)
  {
    usart_receive_it(&husart2, rx_data, 1u);
  }

  return 0;
}
