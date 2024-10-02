#include "stdint.h"

int main(void);
void SysTick_Handler(void);

// Symbols defined in linker.ld  
extern uint32_t _sstack, _sbss, _ebss, _sdata, _edata, _sidata;

// Startup code
__attribute__((naked, noreturn)) void Reset_Handler(void) {

  // init .bss section
  for(uint32_t *src = &_sbss; src < &_ebss; src++)
  {
    *src = 0;
  }

  // init .data section from flash
  for(uint32_t *src = &_sdata, *dst = &_sidata; src < &_edata;) 
  {
    *src++ = *dst++;
  }

  main();    // Call main()
  while(1);  // Infinite loop in the case if main() returns
}



// 16 standard and 68 STM32-specific handlers
__attribute__((section(".vectors"))) uint32_t tab[16 + 68] = {

    (uint32_t)&_sstack,
    (uint32_t)Reset_Handler,
    0,  //NMI_Handler,
    0,  //HardFault_Handler,
    0,  //MemManage_Handler,
    0,  //BusFault_Handler,
    0,  //UsageFault_Handler,
    0,
    0,
    0,
    0,
    0,  //SVC_Handler,
    0,  //DebugMon_Handler,
    0,
    0,  //PendSV_Handler,
    (uint32_t)SysTick_Handler,
    0,  //WWDG_IRQHandler,
    0,  //PVD_IRQHandler,
    0,  //TAMPER_IRQHandler,
    0,  //RTC_IRQHandler,
    0,  //FLASH_IRQHandler,
    0,  //RCC_IRQHandler,
    0,  //EXTI0_IRQHandler,
    0,  //EXTI1_IRQHandler,
    0,  //EXTI2_IRQHandler,
    0,  //EXTI3_IRQHandler,
    0,  //EXTI4_IRQHandler,
    0,  //DMA1_Channel1_IRQHandler,
    0,  //DMA1_Channel2_IRQHandler,
    0,  //DMA1_Channel3_IRQHandler,
    0,  //DMA1_Channel4_IRQHandler,
    0,  //DMA1_Channel5_IRQHandler,
    0,  //DMA1_Channel6_IRQHandler,
    0,  //DMA1_Channel7_IRQHandler,
    0,  //ADC1_2_IRQHandler,
    0,  //USB_HP_CAN1_TX_IRQHandler,
    0,  //USB_LP_CAN1_RX0_IRQHandler,
    0,  //CAN1_RX1_IRQHandler,
    0,  //CAN1_SCE_IRQHandler,
    0,  //EXTI9_5_IRQHandler,
    0,  //TIM1_BRK_IRQHandler,
    0,  //TIM1_UP_IRQHandler,
    0,  //TIM1_TRG_COM_IRQHandler,
    0,  //TIM1_CC_IRQHandler,
    0,  //TIM2_IRQHandler,
    0,  //TIM3_IRQHandler,
    0,  //TIM4_IRQHandler,
    0,  //I2C1_EV_IRQHandler,
    0,  //I2C1_ER_IRQHandler,
    0,  //I2C2_EV_IRQHandler,
    0,  //I2C2_ER_IRQHandler,
    0,  //SPI1_IRQHandler,
    0,  //SPI2_IRQHandler,
    0,  //USART1_IRQHandler,
    0,  //USART2_IRQHandler,
    0,  //USART3_IRQHandler,
    0,  //EXTI15_10_IRQHandler,
    0,  //RTC_Alarm_IRQHandler,
    0,  //USBWakeUp_IRQHandler,
    0,  //TIM8_BRK_IRQHandler,
    0,  //TIM8_UP_IRQHandler,
    0,  //TIM8_TRG_COM_IRQHandler,
    0,  //TIM8_CC_IRQHandler,
    0,  //ADC3_IRQHandler,
    0,  //FSMC_IRQHandler,
    0,  //SDIO_IRQHandler,
    0,  //TIM5_IRQHandler,
    0,  //SPI3_IRQHandler,
    0,  //UART4_IRQHandler,
    0,  //UART5_IRQHandler,
    0,  //TIM6_IRQHandler,
    0,  //TIM7_IRQHandler,
    0,  //DMA2_Channel1_IRQHandler,
    0,  //DMA2_Channel2_IRQHandler,
    0,  //DMA2_Channel3_IRQHandler,
    0,  //DMA2_Channel4_5_IRQHandler,
};