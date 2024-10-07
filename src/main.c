#include "gpio_driver.h"
#include "rcc_driver.h"
#include "afio_driver.h"
#include "main_cfg.h"

void delay_blocking_ms(uint32_t delay_ms)
{
  uint32_t start = ticks;
  while(ticks - start < delay_ms);
}

void toggle_led(void)
{
  gpio_toggle_pin(GPIOA, 5);
}

int main(void) 
{

  rcc_cfg_systick(TICK_PERIOD_MS);

  GPIO_PinConfig_t out_pp;
  out_pp.mode = MODE_OUT_2MHz;
  out_pp.sub_mode = SUBMODE_OUT_GP_PP;

  GPIO_PinConfig_t in_pu;
  in_pu.mode = MODE_IN;
  in_pu.sub_mode = SUBMODE_IN_PUPD;
  in_pu.pupd = PULLUP;

  gpio_clk_enable(GPIOA);
  gpio_clk_enable(GPIOB);
  gpio_set_mode(GPIOA, 5, &out_pp);
  gpio_set_mode(GPIOB, 0, &in_pu);

  afio_clk_enable();
  gpio_cfg_irq(portB, 0, EXTI_TRIGGER_FALLING_EDGE, toggle_led);
  gpio_en_irq(portB, 0);

  while(1)
  {
  }

  return 0;
}
