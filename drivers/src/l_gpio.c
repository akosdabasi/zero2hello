#include "l_gpio.h"

void gpio_clk_enable(GPIO_t* const pGPIO)
{
  if(pGPIO == GPIOA)
  {
    SETBIT(RCC->APB2ENR, 2);
  }
  else if(pGPIO == GPIOB)
  {
    SETBIT(RCC->APB2ENR, 3);
  }
  else if(pGPIO == GPIOC)
  {
    SETBIT(RCC->APB2ENR, 4);
  }
  else if(pGPIO == GPIOD)
  {
    SETBIT(RCC->APB2ENR, 5);
  }
  else
  {
    /*error handling*/
  }
  
}

void gpio_clk_disable(GPIO_t* const pGPIO)
{
  if(pGPIO == GPIOA)
  {
    CLEARBIT(RCC->APB2ENR, 2);
  }
  else if(pGPIO == GPIOB)
  {
    CLEARBIT(RCC->APB2ENR, 3);
  }
  else if(pGPIO == GPIOC)
  {
    CLEARBIT(RCC->APB2ENR, 4);
  }
  else if(pGPIO == GPIOD)
  {
    CLEARBIT(RCC->APB2ENR, 5);
  }
  else
  {
    /*error handling*/
  }
}

void gpio_get_default_cfg(GPIO_PinConfig_t *pCfg)
{
  pCfg->mode = MODE_OUT_2;
  pCfg->sub_mode = MODE_OUT_GP_PP;
  pCfg->pupd = PULLDOWN; //only relevant if mode is input
}

void gpio_set_mode(GPIO_t* const pGPIO, gpio_pin_t pin, GPIO_PinConfig_t *pCfg)
{
  uint8_t reg_idx = pin / 8;
  uint8_t pos = pin % 8;
  uint32_t bits = pCfg->mode | pCfg->sub_mode;

  pGPIO->CR[reg_idx] &= ~(0b1111u << (pos*4));
  pGPIO->CR[reg_idx] |= (bits << (pos*4));

  if(pCfg->mode == MODE_IN && pCfg->sub_mode == MODE_IN_PP)
  {
    if(pCfg->pupd)
    {
      SETBIT(pGPIO->ODR, pin); 
    }
    else 
    {
      CLEARBIT(pGPIO->ODR, pin);
    }
  }
}

uint8_t gpio_read_pin(GPIO_t* const pGPIO, gpio_pin_t pin)
{
  return (uint8_t)GETBIT(pGPIO->IDR,pin);
}

uint16_t gpio_read_port(GPIO_t* const pGPIO)
{
  return (uint16_t)pGPIO->IDR;
}

void gpio_write_pin(GPIO_t* const pGPIO, gpio_pin_t pin, uint8_t value)
{
  if(value == HIGH)
  {
    pGPIO->BSRR = (1u << pin);
  }
  else
  {
    pGPIO->BSRR = (1u << (pin+16));
  }
}

void gpio_write_port(GPIO_t* const pGPIO, uint16_t value)
{
  pGPIO->ODR = (uint32_t)value;
}

void gpio_toggle_pin(GPIO_t* const pGPIO, gpio_pin_t pin)
{
  if(GETBIT(pGPIO->ODR, pin) == LOW)
  {
    pGPIO->BSRR = (1u << pin);
  }
  else
  {
    pGPIO->BSRR = (1u << (pin+16));
  }
}
