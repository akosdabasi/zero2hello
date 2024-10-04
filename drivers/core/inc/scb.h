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
static inline  __attribute__((noreturn)) void  __NVIC_SystemReset(void)
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