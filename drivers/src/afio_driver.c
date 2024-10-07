#include "afio_driver.h"

AFIO_t *const pAFIO = AFIO;

void afio_sel_EVENTOUT_pin(gpio_port_t port ,gpio_pin_t pin)
{
  CLEAR_BITFIELD(pAFIO->EVCR, (AFIO_EVCR_PORT_Msk | AFIO_EVCR_PIN_Msk));
  uint32_t port_pin_cfg = ((uint32_t)port << AFIO_EVCR_PORT_Pos) | ((uint32_t)pin << AFIO_EVCR_PIN_Pos);
  pAFIO->EVCR |= port_pin_cfg;
}

void afio_attach_port_to_exti_line(gpio_port_t port, exti_line_t line)
{
  //in register there are 4 fields that are 4bits long corresponding to one line
  uint8_t reg_idx = line / 4;
  uint8_t reg_pos = (line % 4)*4;

  //clear bitfield
  pAFIO->EXTICR[reg_idx] &= ~(0b1111u << (reg_pos));

  //set bitfield
  pAFIO->EXTICR[reg_idx] |= ((uint32_t)port << (reg_pos));

} 
