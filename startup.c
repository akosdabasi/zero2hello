
int main(void);

// Startup code
__attribute__((naked, noreturn)) void Reset_Handler(void) {

  // memset .bss to zero, and copy .data section to RAM region
  extern long _sbss, _ebss, _sdata, _edata, _sidata;

  for (long *src = &_sbss; src < &_ebss; src++) *src = 0;
  for (long *src = &_sdata, *dst = &_sidata; src < &_edata;) *src++ = *dst++;

  main();             // Call main()
  for (;;) (void) 0;  // Infinite loop in the case if main() returns
}


extern void _estack(void);  // Defined in link.ld

// 16 standard and 43 STM32-specific handlers
__attribute__((section(".vectors"))) void (*const tab[16 + 68])(void) = {

    _estack,
    Reset_Handler,
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
    0,  //SysTick_Handler,
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
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0  //BootRAM          /* @0x108. This is for boot in RAM mode for
};