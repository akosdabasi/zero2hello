#include "user_snippets.h"
#include "rcc_clk_cfg.h"


uint8_t spi_trans_done = 0;
uint8_t usart_trans_done = 0;
//output buffer
uint8_t tx_data[12] = "hello there";
uint8_t rx_data[12];


void spiEventHandler(spi_handle_t *const hspi, spi_event_t event)
{
  if(event == SPI_EVENT_TRANS_COMPLETE)
  {
    spi_trans_done = 1;
    (void)hspi;
  }
}

void usartEventHandler(usart_handle_t *const husart, usart_event_t event)
{
  if(event == USART_EVENT_TRANS_COMPLETE)
  {
    usart_trans_done = 1;
    (void)husart;
  }
  else if(event == USART_EVENT_RECEPTION_COMPLETE)
  {
    usart_transmit_it(&husart2, husart2.rx_buffer, husart2.rx_buffer_length);
  }
}

void buttonEventHandler()
{
  usart_transmit_it(&husart2, tx_data, 12u);
  spi_transcieve_it(&hspi1, tx_data, rx_data, 12u);
}

int main(void) 
{

  /*System timer config*/
  rcc_cfg_systick(TICK_PERIOD_MS);

  /*SP1 config*/
  config_spi1_to_master();
  spi_init(&hspi1); //init SPI1
  spi_set_ssoe(&hspi1, enabled); //automatic SSN managment
  spi_register_cb(&hspi1, spiEventHandler);

  /*USART2 config*/
  config_usart2();
  usart_init(&husart2);
  usart_register_cb(&husart2, usartEventHandler);
  
  /*button config*/
  config_pin_to_button_it(GPIOC, 10, buttonEventHandler);

  //usart_transmit(&husart2, tx_data, 12u);
  //spi_transcieve_it(&hspi1, &tx_data[0], &rx_data[0], (uint16_t)10u);
  //(void)rx_data;
  

  while(1)
  {
    usart_receive_it(&husart2, rx_data, 1u);
  }

  return 0;
}
