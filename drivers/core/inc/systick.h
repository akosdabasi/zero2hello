#pragma once

/*
* file: systick.h
* description: low level driver layer for the System Timer (SysTick) of the Cortex M3 processor
* contains:
*     - systick configuration parameters
*     - systick configuration function
*/

#include "core_cm3.h"

//configuration parameters

#define SysTick_CLKSOURCE  1u //0: external clock, 1: processor clock


/**
  \brief   System Tick Configuration
  \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  ticks  Number of ticks between two interrupts.
  \return          0  Function succeeded.
  \return          1  Function failed.
 */
static inline uint32_t SysTick_Config(uint32_t nticks)
{
  if ((nticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    return (1UL);                                                             /* Reload value impossible */
  }

  SysTick->RVR  = (uint32_t)(nticks - 1UL);                                   /* set reload register */
  SysTick->CVR   = 0UL;                                                       /* Load the SysTick Counter Value */
  SysTick->CSR  =  (SysTick_CLKSOURCE << SysTick_CTRL_CLKSOURCE_Pos) |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                                   /* Enable SysTick IRQ and SysTick Timer */
  return (0UL);                                                               /* Function successful */
}