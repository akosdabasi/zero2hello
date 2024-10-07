#include "gpio_driver.h"
#include "rcc_driver.h"

GPIO_t* gpio_get_port_handler(gpio_port_t port)
{
  switch (port)
  {
  case portA: return GPIOA;
  case portB: return GPIOB;
  case portC: return GPIOC;
  case portD: return GPIOD;
  default: return (GPIO_t*)NULL;    
  }
}


void gpio_clk_enable(GPIO_t *const pGPIO)
{
  if(pGPIO == GPIOA)
  {
    RCC_APB2ENR_IOPA_CLK_ENABLE();    
  }
  else if(pGPIO == GPIOB)
  {
    RCC_APB2ENR_IOPB_CLK_ENABLE();    
  }
  else if(pGPIO == GPIOC)
  {
    RCC_APB2ENR_IOPC_CLK_ENABLE();    
  }
  else if(pGPIO == GPIOD)
  {
    RCC_APB2ENR_IOPD_CLK_ENABLE();    
  }
  else
  {
    /*error handling*/
  }
  
}

void gpio_clk_disable(GPIO_t *const pGPIO)
{
  if(pGPIO == GPIOA)
  {
    RCC_APB2ENR_IOPA_CLK_DISABLE();    
  }
  else if(pGPIO == GPIOB)
  {
    RCC_APB2ENR_IOPB_CLK_DISABLE();    
  }
  else if(pGPIO == GPIOC)
  {
    RCC_APB2ENR_IOPC_CLK_DISABLE();    
  }
  else if(pGPIO == GPIOD)
  {
    RCC_APB2ENR_IOPD_CLK_DISABLE();    
  }
  else
  {
    /*error handling*/
  }
}

void gpio_clk_reset(GPIO_t *const pGPIO)
{
  if(pGPIO == GPIOA)
  {
    RCC_APB2RSTR_IOPA_RESET();    
  }
  else if(pGPIO == GPIOB)
  {
    RCC_APB2RSTR_IOPB_RESET();    
  }
  else if(pGPIO == GPIOC)
  {
    RCC_APB2RSTR_IOPC_RESET();    
  }
  else if(pGPIO == GPIOD)
  {
    RCC_APB2RSTR_IOPD_RESET();    
  }
  else
  {
    /*error handling*/
  }
}

void gpio_get_default_cfg(GPIO_PinConfig_t *pCfg)
{
  pCfg->mode = MODE_IN;
  pCfg->sub_mode = SUBMODE_IN_FLOAT;
  pCfg->pupd = NO_PUPD; //only relevant if submode is SUBMODE_IN_PUPD
}

void gpio_set_mode(GPIO_t *const pGPIO, gpio_pin_t pin, GPIO_PinConfig_t *pCfg)
{
  uint8_t reg_idx = pin / 8;
  uint8_t pos = pin % 8;
  uint32_t bits = pCfg->mode | pCfg->sub_mode;

  pGPIO->CR[reg_idx] &= ~(0b1111u << (pos*4));  //clearing mode bits
  pGPIO->CR[reg_idx] |= (bits << (pos*4));      //setting mode bits

  //Activate pullup or pulldown resistor if we are in input pullup-pulldown mode
  if(pCfg->mode == MODE_IN && pCfg->sub_mode == SUBMODE_IN_PUPD)
  {
    if(pCfg->pupd == PULLUP)
    {
      SET_BIT(pGPIO->ODR, pin); 
    }
    else if(pCfg->pupd == PULLDOWN)
    {
      CLEAR_BIT(pGPIO->ODR, pin);
    }
    else
    {
      //error handling
    }
  }
}

uint8_t gpio_read_pin(GPIO_t *const pGPIO, gpio_pin_t pin)
{
  return (uint8_t)GET_BIT(pGPIO->IDR,pin);
}

uint16_t gpio_read_port(GPIO_t *const pGPIO)
{
  return (uint16_t)pGPIO->IDR;
}

void gpio_write_pin(GPIO_t *const pGPIO, gpio_pin_t pin, uint8_t value)
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

void gpio_write_port(GPIO_t *const pGPIO, uint16_t value)
{
  pGPIO->ODR = (uint32_t)value;
}

void gpio_toggle_pin(GPIO_t *const pGPIO, gpio_pin_t pin)
{
  if(GET_BIT(pGPIO->ODR, pin) == LOW)
  {
    pGPIO->BSRR = (1u << pin);
  }
  else
  {
    pGPIO->BSRR = (1u << (pin+16));
  }
}
