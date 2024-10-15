#include "utils.h"

//forward declaration of the main function (to be called from the reset handler)
int main(void);

// Symbols defined in linker script (linker.ld)
extern uint32_t _sstack, _sbss, _ebss, _sdata, _edata, _sidata;

// Default Handler: Infinite loop for unimplemented handlers
void Default_Handler(void) {
    while (1);
}

// System Exceptions and Interrupt Handlers forward declarations
void __attribute__((weak, alias("Default_Handler"))) NMI_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) HardFault_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) MemManage_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) BusFault_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) UsageFault_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) SVC_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) DebugMon_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) PendSV_Handler(void);
void __attribute__((weak, alias("Default_Handler"))) SysTick_Handler(void);

// Peripheral Interrupt Handlers (Weak Definitions as Aliases to Default_Handler)
void __attribute__((weak, alias("Default_Handler"))) WWDG_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) PVD_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TAMPER_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) RTC_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) FLASH_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) RCC_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) EXTI0_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) EXTI1_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) EXTI2_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) EXTI3_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) EXTI4_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) DMA1_Channel1_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) DMA1_Channel2_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) DMA1_Channel3_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) DMA1_Channel4_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) DMA1_Channel5_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) DMA1_Channel6_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) DMA1_Channel7_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) ADC1_2_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) USB_HP_CAN1_TX_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) USB_LP_CAN1_RX0_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) CAN1_RX1_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) CAN1_SCE_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) EXTI9_5_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM1_BRK_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM1_UP_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM1_TRG_COM_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM1_CC_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM2_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM3_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM4_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) I2C1_EV_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) I2C1_ER_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) I2C2_EV_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) I2C2_ER_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) SPI1_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) SPI2_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) USART1_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) USART2_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) USART3_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) EXTI15_10_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) RTC_Alarm_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) USBWakeUp_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM8_BRK_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM8_UP_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM8_TRG_COM_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM8_CC_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) ADC3_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) FSMC_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) SDIO_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM5_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) SPI3_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) UART4_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) UART5_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM6_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) TIM7_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) DMA2_Channel1_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) DMA2_Channel2_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) DMA2_Channel3_IRQHandler(void);
void __attribute__((weak, alias("Default_Handler"))) DMA2_Channel4_5_IRQHandler(void);

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



// 16 standard and 60 STM32-specific handlers
__attribute__((section(".vectors"))) uint32_t tab[16 + 60] = {

    (uint32_t)&_sstack,
    (uint32_t)Reset_Handler,
    (uint32_t)NMI_Handler,
    (uint32_t)HardFault_Handler,
    (uint32_t)MemManage_Handler,
    (uint32_t)BusFault_Handler,
    (uint32_t)UsageFault_Handler,
    0,
    0,
    0,
    0,
    (uint32_t)SVC_Handler,
    (uint32_t)DebugMon_Handler,
    0,
    (uint32_t)PendSV_Handler,
    (uint32_t)SysTick_Handler,
    (uint32_t)WWDG_IRQHandler,
    (uint32_t)PVD_IRQHandler,
    (uint32_t)TAMPER_IRQHandler,
    (uint32_t)RTC_IRQHandler,
    (uint32_t)FLASH_IRQHandler,
    (uint32_t)RCC_IRQHandler,
    (uint32_t)EXTI0_IRQHandler,
    (uint32_t)EXTI1_IRQHandler,
    (uint32_t)EXTI2_IRQHandler,
    (uint32_t)EXTI3_IRQHandler,
    (uint32_t)EXTI4_IRQHandler,
    (uint32_t)DMA1_Channel1_IRQHandler,
    (uint32_t)DMA1_Channel2_IRQHandler,
    (uint32_t)DMA1_Channel3_IRQHandler,
    (uint32_t)DMA1_Channel4_IRQHandler,
    (uint32_t)DMA1_Channel5_IRQHandler,
    (uint32_t)DMA1_Channel6_IRQHandler,
    (uint32_t)DMA1_Channel7_IRQHandler,
    (uint32_t)ADC1_2_IRQHandler,
    (uint32_t)USB_HP_CAN1_TX_IRQHandler,
    (uint32_t)USB_LP_CAN1_RX0_IRQHandler,
    (uint32_t)CAN1_RX1_IRQHandler,
    (uint32_t)CAN1_SCE_IRQHandler,
    (uint32_t)EXTI9_5_IRQHandler,
    (uint32_t)TIM1_BRK_IRQHandler,
    (uint32_t)TIM1_UP_IRQHandler,
    (uint32_t)TIM1_TRG_COM_IRQHandler,
    (uint32_t)TIM1_CC_IRQHandler,
    (uint32_t)TIM2_IRQHandler,
    (uint32_t)TIM3_IRQHandler,
    (uint32_t)TIM4_IRQHandler,
    (uint32_t)I2C1_EV_IRQHandler,
    (uint32_t)I2C1_ER_IRQHandler,
    (uint32_t)I2C2_EV_IRQHandler,
    (uint32_t)I2C2_ER_IRQHandler,
    (uint32_t)SPI1_IRQHandler,
    (uint32_t)SPI2_IRQHandler,
    (uint32_t)USART1_IRQHandler,
    (uint32_t)USART2_IRQHandler,
    (uint32_t)USART3_IRQHandler,
    (uint32_t)EXTI15_10_IRQHandler,
    (uint32_t)RTC_Alarm_IRQHandler,
    (uint32_t)USBWakeUp_IRQHandler,
    (uint32_t)TIM8_BRK_IRQHandler,
    (uint32_t)TIM8_UP_IRQHandler,
    (uint32_t)TIM8_TRG_COM_IRQHandler,
    (uint32_t)TIM8_CC_IRQHandler,
    (uint32_t)ADC3_IRQHandler,
    (uint32_t)FSMC_IRQHandler,
    (uint32_t)SDIO_IRQHandler,
    (uint32_t)TIM5_IRQHandler,
    (uint32_t)SPI3_IRQHandler,
    (uint32_t)UART4_IRQHandler,
    (uint32_t)UART5_IRQHandler,
    (uint32_t)TIM6_IRQHandler,
    (uint32_t)TIM7_IRQHandler,
    (uint32_t)DMA2_Channel1_IRQHandler,
    (uint32_t)DMA2_Channel2_IRQHandler,
    (uint32_t)DMA2_Channel3_IRQHandler,
    (uint32_t)DMA2_Channel4_5_IRQHandler,
};