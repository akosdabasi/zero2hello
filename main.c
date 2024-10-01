#include "l_gpio.h"

int main(void) {

  GPIO_PinConfig_t pin_cfg;
  pin_cfg.mode = MODE_OUT_2;
  pin_cfg.sub_mode = MODE_OUT_GP_PP;

  gpio_clk_enable(GPIOA);
  gpio_set_mode(GPIOA, 5, &pin_cfg);


  while(1)
  {
    uint32_t delay = 100000;
    while(delay--);
    gpio_toggle_pin(GPIOA, 5);
  }

  return 0;
}
