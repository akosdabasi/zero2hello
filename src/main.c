#include "gpio_driver.h"
#include "clock_driver.h"

#define TICK_MS 1  //system tick period in ms
int main(void) 
{

  systick_init(TICK_MS);

  GPIO_PinConfig_t pin_cfg;
  pin_cfg.mode = MODE_OUT_2;
  pin_cfg.sub_mode = MODE_OUT_GP_PP;

  gpio_clk_enable(GPIOA);
  gpio_clk_enable(GPIOB);
  gpio_clk_enable(GPIOC);
  gpio_set_mode(GPIOA, 5, &pin_cfg);
  gpio_set_mode(GPIOB, 5, &pin_cfg);
  gpio_set_mode(GPIOC, 4, &pin_cfg);

  gpio_write_pin(GPIOC,4, HIGH);
  gpio_write_pin(GPIOB,5, HIGH);
  while(1)
  {
    delay_ms(2000);
    gpio_toggle_pin(GPIOA, 5);
    gpio_toggle_pin(GPIOC, 4);
    gpio_toggle_pin(GPIOB, 5);
  }

  return 0;
}
