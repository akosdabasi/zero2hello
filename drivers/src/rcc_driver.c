#include "rcc_driver.h"
#include "core_cm3.h"
#include "utils.h"

//Globals
volatile uint32_t ticks = 0;

//API
void rcc_cfg_sysclk(clk_src_t clk_src)
{
//enable and wait until selected clock source is stable
  switch(clk_src) {
    case CLOCK_HSI:
      // Enable HSI
      SET_BIT(RCC->CR, RCC_CR_HSION_Pos);
      // Wait until HSI is stable
      while (GET_BIT(RCC->CR, RCC_CR_HSIRDY_Pos) == 0);
      break;
    case CLOCK_HSE:
      // Enable HSE
      SET_BIT(RCC->CR, RCC_CR_HSEON_Pos);
      // Wait until HSE is stable
      while (GET_BIT(RCC->CR, RCC_CR_HSERDY_Pos) == 0);
      break;
    case CLOCK_PLL:
      // Make sure PLL configuration is set up before enabling
      // Configure PLL source and multiplier before enabling it

      // Enable PLL
      SET_BIT(RCC->CR, RCC_CR_PLLON_Pos);
      // Wait until PLL is stable
      while (GET_BIT(RCC->CR, RCC_CR_PLLRDY_Pos) == 0);
      break;
    default:
      // Invalid clock source, return without doing anything
      return;
  }

  // select clock_src as the system clock
  CLEAR_BITFIELD(RCC->CFGR, RCC_CFGR_SW_Msk);
  RCC->CFGR |= ((uint32_t)clk_src << RCC_CFGR_SW_Pos);
  
  //wait until the system clock switch status (SWS) is updated
  while (((RCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos) != clk_src);
}

void rcc_cfg_systick(uint32_t systick_ms) 
{
  uint32_t ticks_per_ms = (SYSTICK_CLK / 1000); 
  uint32_t reload_val =  ticks_per_ms * systick_ms;
  SysTick_Config(reload_val);
}


//IRQ handlers
void SysTick_Handler(void)
{
    ticks++;
}
