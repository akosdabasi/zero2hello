#include "l_gpio.h"
#include "l_clk_cfg.h"

#define TICK_MS 1  //system tick period in ms
int main(void) {

  systick_init(TICK_MS);

  GPIO_PinConfig_t pin_cfg;
  pin_cfg.mode = MODE_OUT_2;
  pin_cfg.sub_mode = MODE_OUT_GP_PP;

  gpio_clk_enable(GPIOA);
  gpio_set_mode(GPIOA, 5, &pin_cfg);


  while(1)
  {
    delay_ms(2000);
    gpio_toggle_pin(GPIOA, 5);
  }

  return 0;
}
