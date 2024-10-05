#pragma once

/*
* file: scb.h
* description: low level driver layer for the System Control Block (SCB) of the Cortex M3 processor
* contains:
*/

#include "core_cm3.h"


/**
  \brief   System Reset
  \details Initiates a system reset request to reset the MCU.
 */
static inline  __attribute__((noreturn)) void  __SCB_SystemReset(void)
{
  __DSB();                                                          /* Ensure all outstanding memory accesses included
                                                                       buffered write are completed before reset */
  SCB->AIRCR  = (uint32_t)((0x5FAUL << SCB_AIRCR_VECTKEY_Pos)    |
                           (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
                            SCB_AIRCR_SYSRESETREQ_Msk    );         /* Keep priority group unchanged */
  __DSB();                                                          /* Ensure completion of memory access */

  for(;;)                                                           /* wait until reset */
  {
    __NOP();
  }
}

#define __SCB_PEND_NMI()            SCB->ICSR |= SCB_ICSR_NMIPENDSET_Msk
#define __SCB_PEND_PENDSV()         SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk
#define __SCB_UNPEND_PENDSV()       SCB->ICSR &= ~SCB_ICSR_PENDSVCLR_Msk
#define __SCB_GET_NEXT_IRQ()        SCB->ICSR & SCB_ICSR_VECTPENDING_Msk
#define __SCB_SET_SLEEPONEXIT()     SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk   //enter sleep on return from an ISR (interrupt driven application)
#define __SCB_CLEAR_SLEEPONEXIT()   SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk
#define __SCB_SET_SLEEPDEEP()       SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk
#define __SCB_CLEAR_SLEEPDEEP()     SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk
#define __SCB_SET_SEVONPEND()       SCB->SCR |= SCB_SCR_SEVONPEND_Msk
#define __SCB_CLEAR_SEVONPEND()     SCB->SCR &= ~SCB_SCR_SEVONPEND_Msk
