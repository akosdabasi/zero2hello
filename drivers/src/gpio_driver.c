#include "nvic.h"
#include "gpio_driver.h"
#include "rcc_driver.h"
#include "afio_driver.h"

exti_line_t pin_to_exti_line_map[] = 
{
  line0,
  line1,
  line2,
  line3,
  line4,
  line5,
  line6,
  line7,
  line8,
  line9,
  line10,
  line11,
  line12,
  line13,
  line14,
  line15,
};

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

void gpio_port_reset(GPIO_t *const pGPIO)
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

uint8_t gpio_lock_port(GPIO_t *const pGPIO, uint16_t pins)
{
  if(GET_BIT(pGPIO->LCKR, GPIOx_LCKR_LCKK_Pos))
  {
    //pins are already locked.
    return 1;
  }

  //execute locking sequence with atomic operations
  pGPIO->LCKR = ((uint32_t)pins | GPIOx_LCKR_LCKK_Msk);
  pGPIO->LCKR = (uint32_t)pins;
  pGPIO->LCKR = ((uint32_t)pins | GPIOx_LCKR_LCKK_Msk);
  (void)pGPIO->LCKR;

  return (uint8_t)GET_BIT(pGPIO->LCKR, GPIOx_LCKR_LCKK_Pos);  
}



/*---------------------------- INTERRUPT HANDLING ---------------------------------*/

//internal callback functions for ISRs
static gpio_callback_t exti_cbs[NUM_OF_EXTI_LINES];

void gpio_cfg_irq(gpio_port_t port, gpio_pin_t pin, exti_trigger_t trigger, gpio_callback_t cb)
{
  //check if we got a valid callback
  if(!cb)return;

  //get corresponding exti line
  exti_line_t line = pin_to_exti_line_map[pin];

  //register callback to the appropriate exti line
  exti_cbs[line] = cb;

  afio_clk_enable();
  
  //attach pin to exti line in afio
  afio_attach_port_to_exti_line(port, line);

  //configure triggering mode in exti
  if(trigger == EXTI_TRIGGER_BOTH_EDGES || trigger == EXTI_TRIGGER_RISING_EDGE)
  {
    exti_en_rising_trig(line);
  }
  else 
  {
    exti_dis_rising_trig(line);
  }

  if(trigger == EXTI_TRIGGER_BOTH_EDGES || trigger == EXTI_TRIGGER_FALLING_EDGE)
  {
    exti_en_falling_trig(line);
  }
  else
  {
    exti_dis_falling_trig(line);
  }

  //clear exti line pending bit
  exti_clear_pend(line);
  
}

void gpio_en_irq(gpio_port_t port, gpio_pin_t pin)
{
  //port parameter is only used for readability
  (void)port; 

  //get corresponding exti line
  exti_line_t line = pin_to_exti_line_map[pin];

  //enable interrupt generation in exti
  exti_en_irq(line);

  //get the IRQ number
  IRQn_t irqn = exti_line_to_irqn(line);

  //enable interrupt in NVIC
  __NVIC_EnableIRQ(irqn);
}

void gpio_dis_irq(gpio_port_t port, gpio_pin_t pin)
{
  //port parameter is only used for readability
  (void)port; 

  //get corresponding exti line
  exti_line_t line = pin_to_exti_line_map[pin];

  //disable interrupt generation in exti
  exti_dis_irq(line);

  //get the IRQ number
  IRQn_t irqn = exti_line_to_irqn(line);

  //disable interrupt in NVIC
  __NVIC_DisableIRQ(irqn);
}

void gpio_clear_irq_flag(gpio_port_t port, gpio_pin_t pin)
{
  //port parameter is only used for readability
  (void)port; 

  exti_line_t line = pin_to_exti_line_map[pin];

  //clear pending bit in exti
  exti_clear_pend(line);
}


//IRQ handlers
static inline void gpio_exti_handle_it(exti_line_t line)
{
  //check and clear if pending flag is set
  if(exti_get_pend_stat(line))
  {
    exti_clear_pend(line);
    //call callback function if registered
    if(exti_cbs[line])
    {
      exti_cbs[line]();
    }
  }
}

void EXTI0_IRQHandler(void)
{
  gpio_exti_handle_it(line0);
}

void EXTI1_IRQHandler(void)
{
  gpio_exti_handle_it(line1);
}

void EXTI2_IRQHandler(void)
{
  gpio_exti_handle_it(line2);
}

void EXTI3_IRQHandler(void)
{
  gpio_exti_handle_it(line3);
}

void EXTI9_5_IRQHandler(void)
{
  gpio_exti_handle_it(line5);
  gpio_exti_handle_it(line6);
  gpio_exti_handle_it(line7);
  gpio_exti_handle_it(line8);
  gpio_exti_handle_it(line9);
}

void EXTI15_10_IRQHandler(void)
{
  gpio_exti_handle_it(line10);
  gpio_exti_handle_it(line11);
  gpio_exti_handle_it(line12);
  gpio_exti_handle_it(line13);
  gpio_exti_handle_it(line14);
  gpio_exti_handle_it(line15);
}
