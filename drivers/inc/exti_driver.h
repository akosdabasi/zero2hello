#pragma once

#include "utils.h"
#include "nvic.h"
#include "mcu_peripherals.h"

#define NUM_OF_EXTI_LINES 19u

typedef enum{
  line0,
  line1,
  line2,
  line3,
  line4,
  line5,
  line6,
  line7,
  line8,
  line9,
  line10,
  line11,
  line12,
  line13,
  line14,
  line15,
  line16,
  line17,
  line18,
} exti_line_t;

typedef enum {
  EXTI_TRIGGER_RISING_EDGE = 0,
  EXTI_TRIGGER_FALLING_EDGE,
  EXTI_TRIGGER_BOTH_EDGES
} exti_trigger_t;

IRQn_t exti_line_to_irqn(exti_line_t line);

static inline void exti_en_irq(exti_line_t line){SET_BIT(EXTI->IMR,line);}
static inline void exti_dis_irq(exti_line_t line){CLEAR_BIT(EXTI->IMR,line);}

static inline void exti_en_event(exti_line_t line){SET_BIT(EXTI->EMR,line);}
static inline void exti_dis_event(exti_line_t line){CLEAR_BIT(EXTI->EMR,line);}

static inline void exti_en_rising_trig(exti_line_t line){SET_BIT(EXTI->RTSR,line);}
static inline void exti_dis_rising_trig(exti_line_t line){CLEAR_BIT(EXTI->RTSR,line);}

static inline void exti_en_falling_trig(exti_line_t line){SET_BIT(EXTI->FTSR,line);}
static inline void exti_dis_falling_trig(exti_line_t line){CLEAR_BIT(EXTI->FTSR,line);}

static inline void exti_generate_irq(exti_line_t line){SET_BIT(EXTI->SWIER,line);}

static inline uint8_t exti_get_pend_stat(exti_line_t line){return (uint8_t)GET_BIT(EXTI->PR,line);}
static inline void exti_clear_pend(exti_line_t line){SET_BIT(EXTI->PR,line);}
