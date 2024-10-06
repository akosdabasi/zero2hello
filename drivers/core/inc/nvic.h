#pragma once

/*
* file: nvic.h
* description: low level driver layer for the Nested Vector Interrupt Controller (NVIC) of the Cortex M3 processor
* contains:
*     - NVIC configuration parameters
*     - type defintions related to exception handling
*     - Exception handling functions
*/

#include "core_cm3.h"
#include "utils.h"

//NVIC configuration
#define __NVIC_PRIO_BITS  4  //number of priority bit the MCU implements


typedef enum
{
/* -------------------  Processor Exceptions Numbers  ----------------------------- */
  NonMaskableInt_IRQn           = -14,     /*  2 Non Maskable Interrupt */
  HardFault_IRQn                = -13,     /*  3 HardFault Interrupt */
  MemoryManagement_IRQn         = -12,     /*  4 Memory Management Interrupt */
  BusFault_IRQn                 = -11,     /*  5 Bus Fault Interrupt */
  UsageFault_IRQn               = -10,     /*  6 Usage Fault Interrupt */
  SVCall_IRQn                   =  -5,     /* 11 SV Call Interrupt */
  DebugMonitor_IRQn             =  -4,     /* 12 Debug Monitor Interrupt */
  PendSV_IRQn                   =  -2,     /* 14 Pend SV Interrupt */
  SysTick_IRQn                  =  -1,     /* 15 System Tick Interrupt */

/* -------------------  STM32F103RB Specific Interrupt Numbers  ------------------- */
  WWDG_IRQn                     =  0,     /* Window WatchDog Interrupt */
  PVD_IRQn                      =  1,     /* PVD through EXTI Line detection Interrupt */
  TAMPER_IRQn                   =  2,     /* Tamper Interrupt */
  RTC_IRQn                      =  3,     /* RTC global Interrupt */
  FLASH_IRQn                    =  4,     /* FLASH global Interrupt */
  RCC_IRQn                      =  5,     /* RCC global Interrupt */
  EXTI0_IRQn                    =  6,     /* EXTI Line0 Interrupt */
  EXTI1_IRQn                    =  7,     /* EXTI Line1 Interrupt */
  EXTI2_IRQn                    =  8,     /* EXTI Line2 Interrupt */
  EXTI3_IRQn                    =  9,     /* EXTI Line3 Interrupt */
  EXTI4_IRQn                    =  10,    /* EXTI Line4 Interrupt */
  DMA1_Channel1_IRQn            =  11,    /* DMA1 Channel 1 Interrupt */
  DMA1_Channel2_IRQn            =  12,    /* DMA1 Channel 2 Interrupt */
  DMA1_Channel3_IRQn            =  13,    /* DMA1 Channel 3 Interrupt */
  DMA1_Channel4_IRQn            =  14,    /* DMA1 Channel 4 Interrupt */
  DMA1_Channel5_IRQn            =  15,    /* DMA1 Channel 5 Interrupt */
  DMA1_Channel6_IRQn            =  16,    /* DMA1 Channel 6 Interrupt */
  DMA1_Channel7_IRQn            =  17,    /* DMA1 Channel 7 Interrupt */
  ADC1_2_IRQn                   =  18,    /* ADC1 and ADC2 global Interrupt */
  USB_HP_CAN1_TX_IRQn           =  19,    /* USB High Priority or CAN1 TX Interrupts */
  USB_LP_CAN1_RX0_IRQn          =  20,    /* USB Low Priority or CAN1 RX0 Interrupts */
  CAN1_RX1_IRQn                 =  21,    /* CAN1 RX1 Interrupt */
  CAN1_SCE_IRQn                 =  22,    /* CAN1 SCE Interrupt */
  EXTI9_5_IRQn                  =  23,    /* External Line[9:5] Interrupts */
  TIM1_BRK_IRQn                 =  24,    /* TIM1 Break Interrupt */
  TIM1_UP_IRQn                  =  25,    /* TIM1 Update Interrupt */
  TIM1_TRG_COM_IRQn             =  26,    /* TIM1 Trigger and Commutation Interrupt */
  TIM1_CC_IRQn                  =  27,    /* TIM1 Capture Compare Interrupt */
  TIM2_IRQn                     =  28,    /* TIM2 global Interrupt */
  TIM3_IRQn                     =  29,    /* TIM3 global Interrupt */
  TIM4_IRQn                     =  30,    /* TIM4 global Interrupt */
  I2C1_EV_IRQn                  =  31,    /* I2C1 Event Interrupt */
  I2C1_ER_IRQn                  =  32,    /* I2C1 Error Interrupt */
  I2C2_EV_IRQn                  =  33,    /* I2C2 Event Interrupt */
  I2C2_ER_IRQn                  =  34,    /* I2C2 Error Interrupt */
  SPI1_IRQn                     =  35,    /* SPI1 global Interrupt */
  SPI2_IRQn                     =  36,    /* SPI2 global Interrupt */
  USART1_IRQn                   =  37,    /* USART1 global Interrupt */
  USART2_IRQn                   =  38,    /* USART2 global Interrupt */
  USART3_IRQn                   =  39,    /* USART3 global Interrupt */
  EXTI15_10_IRQn                =  40,    /* External Line[15:10] Interrupts */
  RTC_Alarm_IRQn                =  41,    /* RTC Alarm through EXTI Line Interrupt */
  USBWakeUp_IRQn                =  42,    /* USB Wakeup from suspend through EXTI Line Interrupt */
  TIM8_BRK_IRQn                 =  43,    /* TIM8 Break Interrupt */
  TIM8_UP_IRQn                  =  44,    /* TIM8 Update Interrupt */
  TIM8_TRG_COM_IRQn             =  45,    /* TIM8 Trigger and Commutation Interrupt */
  TIM8_CC_IRQn                  =  46,    /* TIM8 Capture Compare Interrupt */
  ADC3_IRQn                     =  47,    /* ADC3 global Interrupt */
  FSMC_IRQn                     =  48,    /* FSMC global Interrupt */
  SDIO_IRQn                     =  49,    /* SDIO global Interrupt */
  TIM5_IRQn                     =  50,    /* TIM5 global Interrupt */
  SPI3_IRQn                     =  51,    /* SPI3 global Interrupt */
  UART4_IRQn                    =  52,    /* UART4 global Interrupt */
  UART5_IRQn                    =  53,    /* UART5 global Interrupt */
  TIM6_IRQn                     =  54,    /* TIM6 global Interrupt */
  TIM7_IRQn                     =  55,    /* TIM7 global Interrupt */
  DMA2_Channel1_IRQn            =  56,    /* DMA2 Channel 1 global Interrupt */
  DMA2_Channel2_IRQn            =  57,    /* DMA2 Channel 2 global Interrupt */
  DMA2_Channel3_IRQn            =  58,    /* DMA2 Channel 3 global Interrupt */
  DMA2_Channel4_5_IRQn          =  59     /* DMA2 Channel 4 and Channel 5 global Interrupt */
} IRQn_t;

#define NVIC_USER_IRQ_OFFSET          16

/* The following EXC_RETURN values are saved the LR on exception entry */
#define EXC_RETURN_HANDLER         (0xFFFFFFF1UL)     /* return to Handler mode, uses MSP after return                               */
#define EXC_RETURN_THREAD_MSP      (0xFFFFFFF9UL)     /* return to Thread mode, uses MSP after return                                */
#define EXC_RETURN_THREAD_PSP      (0xFFFFFFFDUL)     /* return to Thread mode, uses PSP after return                                */


/**
  \brief   Set Priority Grouping
  \details Sets the priority grouping field using the required unlock sequence.
           The parameter PriorityGroup is assigned to the field SCB->AIRCR [10:8] PRIGROUP field.
           Only values from 0..7 are used.
           In case of a conflict between priority grouping and available
           priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set.
  \param [in]      PriorityGroup  Priority grouping field.
 */
static inline void __NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);             /* only values 0..7 are used          */

  reg_value  =  SCB->AIRCR;                                                   /* read old register configuration    */
  reg_value &= ~((uint32_t)(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk)); /* clear bits to change               */
  reg_value  =  (reg_value                                   |
                ((uint32_t)VECTKEY << SCB_AIRCR_VECTKEY_Pos) |
                (PriorityGroupTmp << SCB_AIRCR_PRIGROUP_Pos)  );              /* Insert write key and priority group */
  SCB->AIRCR =  reg_value;
}

/**
  \brief   Get Priority Grouping
  \details Reads the priority grouping field from the NVIC Interrupt Controller.
  \return                Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field).
 */
static inline uint32_t __NVIC_GetPriorityGrouping(void)
{
  return ((uint32_t)((SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos));
}


/**
  \brief   Enable Interrupt
  \details Enables a device specific interrupt in the NVIC interrupt controller.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
static inline void __NVIC_EnableIRQ(IRQn_t IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief   Get Interrupt Enable status
  \details Returns a device specific interrupt enable status from the NVIC interrupt controller.
  \param [in]      IRQn  Device specific interrupt number.
  \return             0  Interrupt is not enabled.
  \return             1  Interrupt is enabled.
  \note    IRQn must not be negative.
 */
static inline uint32_t __NVIC_GetEnableIRQ(IRQn_t IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief   Disable Interrupt
  \details Disables a device specific interrupt in the NVIC interrupt controller.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
static inline void __NVIC_DisableIRQ(IRQn_t IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __DSB();
    __ISB();
  }
}


/**
  \brief   Get Pending Interrupt
  \details Reads the NVIC pending register and returns the pending bit for the specified device specific interrupt.
  \param [in]      IRQn  Device specific interrupt number.
  \return             0  Interrupt status is not pending.
  \return             1  Interrupt status is pending.
  \note    IRQn must not be negative.
 */
static inline uint32_t __NVIC_GetPendingIRQ(IRQn_t IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief   Set Pending Interrupt
  \details Sets the pending bit of a device specific interrupt in the NVIC pending register.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
static inline void __NVIC_SetPendingIRQ(IRQn_t IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ISPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief   Clear Pending Interrupt
  \details Clears the pending bit of a device specific interrupt in the NVIC pending register.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
static inline void __NVIC_ClearPendingIRQ(IRQn_t IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief   Get Active Interrupt
  \details Reads the active register in the NVIC and returns the active bit for the device specific interrupt.
  \param [in]      IRQn  Device specific interrupt number.
  \return             0  Interrupt status is not active.
  \return             1  Interrupt status is active.
  \note    IRQn must not be negative.
 */
static inline uint32_t __NVIC_GetActive(IRQn_t IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->IABR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief   Set Interrupt Priority
  \details Sets the priority of a device specific interrupt or a processor exception.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  \param [in]      IRQn  Interrupt number.
  \param [in]  priority  Priority to set.
  \note    The priority cannot be set for every processor exception.
 */

static inline void __NVIC_SetPriority(IRQn_t IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->IP[((uint32_t)IRQn)]               = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
  else
  {
    SCB->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
}


/**
  \brief   Get Interrupt Priority
  \details Reads the priority of a device specific interrupt or a processor exception.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  \param [in]   IRQn  Interrupt number.
  \return             Interrupt Priority.
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
static inline uint32_t __NVIC_GetPriority(IRQn_t IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return(((uint32_t)NVIC->IP[((uint32_t)IRQn)]               >> (8U - __NVIC_PRIO_BITS)));
  }
  else
  {
    return(((uint32_t)SCB->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - __NVIC_PRIO_BITS)));
  }
}

static inline void __NVIC_SetVector(IRQn_t IRQn, uint32_t vector)
{
  uint32_t *vectors = (uint32_t *)SCB->VTOR;
  vectors[(int32_t)IRQn + NVIC_USER_IRQ_OFFSET] = vector;
  /* ARM Application Note 321 states that the M3 does not require the architectural barrier */
}


/**
  \brief   Get Interrupt Vector
  \details Reads an interrupt vector from interrupt vector table.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  \param [in]   IRQn      Interrupt number.
  \return                 Address of interrupt handler function
 */
static inline uint32_t __NVIC_GetVector(IRQn_t IRQn)
{
  uint32_t *vectors = (uint32_t *)SCB->VTOR;
  return vectors[(int32_t)IRQn + NVIC_USER_IRQ_OFFSET];
}
