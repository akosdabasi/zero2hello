#pragma once

#include "core_cm3.h"

#define SYSCLK 8000000u       //System clock in Hz, needs to match with the clock configuration. (default is 8Mhz)
#define SYSTICK_CLK SYSCLK    //Clock used for systick peripheral.

extern volatile uint32_t ticks; //Global tick counter

void systick_init(uint32_t systick_ms);

void delay_ms(uint32_t delay);