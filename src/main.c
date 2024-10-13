#include "user_snippets.h"
#include "rcc_clk_cfg.h"


uint8_t transmissiondone = 0;
void spiEventHandler(spi_handle_t *const hspi, spi_event_t event)
{
  if(event == SPI_EVENT_TRANS_COMPLETE)
  {
    transmissiondone = 1;
    (void)hspi;
  }
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
  spi_nvic_enable_it(&hspi1);

  //input buffer
  uint8_t rx_data[10];
  zero_array(rx_data, 10);

  //output buffer
  uint8_t tx_data[10] = "toggle";
  
  spi_transcieve_it(&hspi1, &tx_data[0], &rx_data[0], (uint16_t)10u);
  (void)rx_data;

  while(1)
  {
    if(transmissiondone)
    {
      while (1)
      {
        /* code */
      }
      
    }
  }

  return 0;
}
