#include "gpio_driver.h"
#include "rcc_driver.h"
#include "main_cfg.h"

void delay_blocking_ms(uint32_t delay_ms)
{
  uint32_t start = ticks;
  while(ticks - start < delay_ms);
}

int main(void) 
{

  rcc_cfg_systick(TICK_PERIOD_MS);

  GPIO_PinConfig_t pin_cfg;
  pin_cfg.mode = MODE_OUT_2MHz;
  pin_cfg.sub_mode = SUBMODE_OUT_GP_PP;

  GPIO_PinConfig_t pin_cfg_opendrain;
  pin_cfg_opendrain.mode = MODE_OUT_2MHz;
  pin_cfg_opendrain.sub_mode = SUBMODE_OUT_GP_OD;

  gpio_clk_enable(GPIOA);
  gpio_clk_enable(GPIOB);
  gpio_clk_enable(GPIOC);
  gpio_set_mode(GPIOA, 5, &pin_cfg);
  gpio_set_mode(GPIOB, 5, &pin_cfg_opendrain);
  gpio_set_mode(GPIOC, 4, &pin_cfg);

  uint8_t locked = gpio_lock_port(GPIOB, (uint16_t)(1u << 5));
  gpio_write_pin(GPIOC,4, HIGH);
  gpio_write_pin(GPIOB,5, HIGH);
  (void)locked; //suppress unused variable warning
  while(1)
  {
    delay_blocking_ms(1000);
    gpio_toggle_pin(GPIOA, 5);
    gpio_toggle_pin(GPIOC, 4);
    gpio_toggle_pin(GPIOB, 5);
  }

  return 0;
}
