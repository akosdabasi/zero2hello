#include "exti_driver.h"

inline void exti_en_irq(exti_line_t line){SET_BIT(EXTI->IMR,line);}
inline void exti_dis_irq(exti_line_t line){CLEAR_BIT(EXTI->IMR,line);}

inline void exti_en_event(exti_line_t line){SET_BIT(EXTI->EMR,line);}
inline void exti_dis_event(exti_line_t line){CLEAR_BIT(EXTI->EMR,line);}

inline void exti_en_rising_trig(exti_line_t line){SET_BIT(EXTI->RTSR,line);}
inline void exti_dis_rising_trig(exti_line_t line){CLEAR_BIT(EXTI->RTSR,line);}

inline void exti_en_falling_trig(exti_line_t line){SET_BIT(EXTI->FTSR,line);}
inline void exti_dis_falling_trig(exti_line_t line){CLEAR_BIT(EXTI->FTSR,line);}

inline void exti_generate_irq(exti_line_t line){SET_BIT(EXTI->SWIER,line);}

inline uint8_t exti_get_pend_stat(exti_line_t line){return (uint8_t)GET_BIT(EXTI->PR,line);}
inline void exti_clear_pend(exti_line_t line){SET_BIT(EXTI->PR,line);}