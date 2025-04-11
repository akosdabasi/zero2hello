#include "user_snippets.h"
#include "rcc_clk_cfg.h"

int main(void) 
{

  /*System timer config*/
  rcc_cfg_systick(TICK_PERIOD_MS);
  config_pin_to_led(GPIOA, 5);
  
  while(1)
  {
   toggle_led(GPIOA,5);
   delay_blocking_ms(5000);
  }

  return 0;
}
