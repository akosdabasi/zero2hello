#include "exti_driver.h"

IRQn_t exti_line_to_irqn(exti_line_t line)
{
  IRQn_t result;
  switch (line)
  {
  case line0: result = EXTI0_IRQn; break;
  case line1: result = EXTI1_IRQn; break;
  case line2: result = EXTI2_IRQn; break;
  case line3: result = EXTI3_IRQn; break;
  case line4: result = EXTI4_IRQn; break;
  case line5: 
  case line6: 
  case line7: 
  case line8: 
  case line9: result = EXTI9_5_IRQn; break;
  case line10:
  case line11:
  case line12:
  case line13:
  case line14:
  case line15: result = EXTI15_10_IRQn; break;
  case line16: result = PVD_IRQn; break;
  case line17: result = RTC_Alarm_IRQn; break;
  case line18: result = USBWakeUp_IRQn; break;
  default: break;/*normally we should never come here*/
  }

  return result;
}
