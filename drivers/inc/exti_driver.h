#pragma once

#include "utils.h"
#include "mcu_peripherals.h"

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

inline void exti_en_irq(exti_line_t line);
inline void exti_dis_irq(exti_line_t line);

inline void exti_en_event(exti_line_t line);
inline void exti_dis_event(exti_line_t line);

inline void exti_en_rising_trig(exti_line_t line);
inline void exti_dis_rising_trig(exti_line_t line);

inline void exti_en_falling_trig(exti_line_t line);
inline void exti_dis_falling_trig(exti_line_t line);

inline void exti_generate_irq(exti_line_t line);

inline uint8_t exti_get_pend_stat(exti_line_t line);
inline void exti_clear_pend(exti_line_t line);
