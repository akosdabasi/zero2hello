#include "user_utilities.h"
#include "rcc_clk_cfg.h"
#include "ttys.h"
#include "syscalls.h"
#include "console.h"

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
  //usart_register_cb(&husart2, usartEventHandler);
  usart_start(&husart2);

  ttys_get_def_cfg(&httys2.cfg);
  ttys_init(&httys2);
  ttys_start(&httys2);

  //const char* msg = "hello from ttys\n";

  console_init();

  while(1)
  {
    //delay_blocking_ms(1000);
    //_write(&httys2, msg, my_strlen(msg));
    console_run();

  }

  return 0;
}
