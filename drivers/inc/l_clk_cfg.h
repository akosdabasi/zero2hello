#pragma once

#include "l_stdint.h"

#define SYSCLK 8000000u       /*!< System clock in Hz */
#define SYSTICK_CLK SYSCLK

extern volatile uint32_t ticks; /*!< Global tick counter */

void systick_init(uint32_t systick_ms);

void delay_ms(uint32_t delay);