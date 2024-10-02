#include "clock_driver.h"
#include "core_peripherals.h"
#include "utils.h"

//Globals
volatile uint32_t ticks = 0;

//API
void systick_init(uint32_t systick_ms) 
{

  uint32_t reload_val = (SYSTICK_CLK / 1000) * systick_ms;

  if ((reload_val - 1) > 0xffffff) return;  // Systick timer is 24 bit
  SYSTICK->RVR = reload_val - 1;
  SYSTICK->CVR = 0;
  /*
    - use processor clock
    - trigger systick exception
    - enable counter
  */
  SYSTICK->CSR = BIT(0) | BIT(1) | BIT(2);
}

void delay_ms(uint32_t delay) 
{
    uint32_t start = ticks;
    while ((ticks - start) < delay) {
        // Busy wait
    }
}

//IRQ handlers
void SysTick_Handler(void)
{
    ticks++;
}
