#include "rcc_driver.h"
#include "core_cm3.h"
#include "utils.h"
#include "rcc_clk_cfg.h"

//Globals
volatile uint32_t ticks = 0;

RCC_t *const gRCC = RCC;

//API
void rcc_cfg_pll(rcc_pll_src_t pll_src, rcc_pll_mul_t pll_mul)
{
  // 1. Disable the PLL before configuring it
  CLEAR_BIT(gRCC->CR, RCC_CR_PLLON_Pos);        // Disable the PLL
  while(GET_BIT(gRCC->CR, RCC_CR_PLLRDY_Pos));  // Wait until the PLL is fully stopped

  // 2. Configure PLL source
  if(pll_src == RCC_PLL_SRC_HSE) 
  {
    CLEAR_BIT(gRCC->CFGR, RCC_CFGR_PLLXTPRE_Pos); //dont divide HSE by 2
    SET_BIT(gRCC->CFGR, RCC_CFGR_PLLSRC_Pos); //set HSE as pll source
  }
  else if(pll_src == RCC_PLL_SRC_HSE_DIV_2)
  {
    SET_BIT(gRCC->CFGR, RCC_CFGR_PLLXTPRE_Pos); //divide HSE by 2
    SET_BIT(gRCC->CFGR, RCC_CFGR_PLLSRC_Pos); //set HSE as source
  }
  else 
  {
    // Use HSI as PLL source
    CLEAR_BIT(gRCC->CFGR, RCC_CFGR_PLLSRC_Pos); //set HSI as source
  }

  // 3. Configure the PLL multiplication factor
  CLEAR_BITFIELD(gRCC->CFGR, RCC_CFGR_PLLMUL_Msk);
  RCC->CFGR |= (pll_mul << RCC_CFGR_PLLMUL_Pos);  //set PLL multiplier

  // 4. Enable the PLL and wait for it to be ready
  SET_BIT(gRCC->CR, RCC_CR_PLLON_Pos); //enable the PLL

  while (!GET_BIT(gRCC->CR, RCC_CR_PLLRDY_Pos));  //wait until PLL is ready
}

void rcc_cfg_sysclk(rcc_sysclk_src_t clk_src)
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

void rcc_cfg_adc_prescalers(rcc_adc_prescaler_t adc_prsclr) {
  // Clear the ADC prescaler bits
  CLEAR_BITFIELD(RCC->CFGR, RCC_CFGR_ADCPRE_Msk);
  
  // Set the ADC prescaler
  RCC->CFGR |= (adc_prsclr << RCC_CFGR_ADCPRE_Pos);
}

void rcc_cfg_ahb_prescalers(rcc_ahb_prescaler_t ahb_prsclr) {
  // Clear the AHB prescaler bits
  CLEAR_BITFIELD(RCC->CFGR, RCC_CFGR_HPRE_Msk);
  
  // Set the AHB prescaler
  RCC->CFGR |= (ahb_prsclr << RCC_CFGR_HPRE_Pos);
}

void rcc_cfg_apb1_prescalers(rcc_apb1_prescaler_t apb1_prsclr) {
  // Clear the APB1 prescaler bits
  CLEAR_BITFIELD(RCC->CFGR, RCC_CFGR_PPRE1_Msk);
  
  // Set the APB1 prescaler
  RCC->CFGR |= (apb1_prsclr << RCC_CFGR_PPRE1_Pos);
}

void rcc_cfg_apb2_prescalers(rcc_apb2_prescaler_t apb2_prsclr) {
  // Clear the APB2 prescaler bits
  CLEAR_BITFIELD(RCC->CFGR, RCC_CFGR_PPRE2_Msk);
  
  // Set the APB2 prescaler
  RCC->CFGR |= (apb2_prsclr << RCC_CFGR_PPRE2_Pos);
}

uint32_t rcc_get_pllclk()
{
  uint32_t pllclk = 0;
  rcc_pll_mul_t pll_mul = GET_BITFIELD(RCC->CFGR, RCC_CFGR_PLLMUL_Msk, RCC_CFGR_PLLMUL_Pos);  // Get PLL multiplier
  
  uint8_t pll_src = GET_BITFIELD(RCC->CFGR, RCC_CFGR_PLLSRC_Msk, RCC_CFGR_PLLSRC_Pos);  // Get PLL source
  uint32_t pll_src_hz = 0;
  
  if (pll_src == RCC_PLL_SRC_HSI_DIV_2)
  {
    // HSI divided by 2 is used as PLL input
    pll_src_hz = HSI_HZ / 2;
  } 
  else
  {
    // HSE or HSE divided by 2 is used as PLL input
    uint32_t hse_div = GET_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE_Pos);  // Get HSE divider (HSE Div2 bit)
    pll_src_hz = (hse_div == 0) ? HSE_HZ : (HSE_HZ / 2);
  }

  // Calculate the PLL clock based on the multiplier
  // Note: the actual multiplier is PLLMUL + 2 
  pllclk = pll_src_hz * (pll_mul + 2);  // PLLMUL value 0 corresponds to 2x multiplication

  return pllclk;
}

uint32_t rcc_get_sysclk()
{
  uint32_t sysclk = 0;
  rcc_sysclk_src_t clk_src = GET_BITFIELD(RCC->CFGR, RCC_CFGR_SWS_Msk, RCC_CFGR_SWS_Pos);  // Get SYSCLK source

  switch (clk_src) {
    case CLOCK_HSI:  // HSI selected as system clock
      sysclk = HSI_HZ;
      break;
    case CLOCK_HSE:  // HSE selected as system clock
      sysclk = HSE_HZ;
      break;
    case CLOCK_PLL:  // PLL selected as system clock
      sysclk = rcc_get_pllclk();  // Get PLL clock
      break;
    default:
      // Invalid clock source
      sysclk = 0;
      break;
  }
    
  return sysclk;
}

uint32_t rcc_get_hclk()
{
  uint32_t sysclk = rcc_get_sysclk();  // Get system clock
  rcc_ahb_prescaler_t hpre = GET_BITFIELD(RCC->CFGR, RCC_CFGR_HPRE_Msk, RCC_CFGR_HPRE_Pos);  // Get AHB prescaler

  uint32_t hclk = sysclk;

  // Map prescaler value to division factor
  if (hpre >= RCC_AHB_PRESCALER_DIV2) {
      static const uint16_t ahb_prescaler_table[] = {2u, 4u, 8u, 16u, 64u, 128u, 256u, 512u};
      hclk = sysclk / ahb_prescaler_table[hpre - 8u];
  }

  return hclk;
}

uint32_t rcc_get_pclk1()
{
  uint32_t hclk = rcc_get_hclk();  // Get AHB clock
  rcc_apb1_prescaler_t ppre1 = GET_BITFIELD(RCC->CFGR, RCC_CFGR_PPRE1_Msk, RCC_CFGR_PPRE1_Pos);  // Get APB1 prescaler

  uint32_t pclk1 = hclk;

  // Map prescaler value to division factor
  if (ppre1 >= 4) {
    static const uint16_t apb1_prescaler_table[] = {2u, 4u, 8u, 16u};
    pclk1 = hclk / apb1_prescaler_table[ppre1 - 4u];
  }

  return pclk1;
}

uint32_t rcc_get_pclk2()
{
  uint32_t hclk = rcc_get_hclk();  // Get AHB clock
  rcc_apb2_prescaler_t ppre2 = GET_BITFIELD(RCC->CFGR, RCC_CFGR_PPRE2_Msk, RCC_CFGR_PPRE2_Pos);  // Get APB2 prescaler

  uint32_t pclk2 = hclk;

  // Map prescaler value to division factor
  if (ppre2 >= 4) {
    static const uint16_t apb2_prescaler_table[] = {2u, 4u, 8u, 16u};
    pclk2 = hclk / apb2_prescaler_table[ppre2 - 4u];
  }

  return pclk2;
}

uint32_t rcc_get_systick_clk() {
uint32_t systick_clk;
uint32_t hclk = rcc_get_hclk();  // Get the AHB (HCLK) clock frequency

// Check the CLKSOURCE bit in the SysTick Control and Status Register (STK_CTRL)
systick_clk = GET_BIT(SysTick->CSR, SysTick_CSR_CLKSOURCE_Pos) ? hclk : hclk/8;

return systick_clk;
}

void rcc_cfg_systick(uint32_t tick_period_ms) 
{
  //ticks per second
  uint32_t systick_clk = rcc_get_systick_clk();

  //ticks per ms
  uint32_t ticks_per_ms = (systick_clk / 1000); 
  
  uint32_t reload_val =  ticks_per_ms * tick_period_ms;
  
  SysTick_Config(reload_val);
}

//IRQ handlers
void SysTick_Handler(void)
{
    ticks++;
}
