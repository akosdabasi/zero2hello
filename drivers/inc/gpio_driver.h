#pragma once

#include "utils.h"
#include "mcu_peripherals.h"

#define PULLDOWN  0u 
#define PULLUP    1u
#define NO_PUPD   2u

//Modes 
#define MODE_IN                    0b00u
#define MODE_OUT_10MHz             0b01u
#define MODE_OUT_2MHz              0b10u
#define MODE_OUT_50MHz             0b11u

//Sub-modes 
#define SUBMODE_POS                2u

#define SUBMODE_IN_ANALOG          (0b00u << SUBMODE_POS)
#define SUBMODE_IN_FLOAT           (0b01u << SUBMODE_POS)
#define SUBMODE_IN_PUPD            (0b10u << SUBMODE_POS)

#define SUBMODE_OUT_GP_PP          (0b00u << SUBMODE_POS)
#define SUBMODE_OUT_GP_OD          (0b01u << SUBMODE_POS)
#define SUBMODE_OUT_ALT_PP         (0b10u << SUBMODE_POS)
#define SUBMODE_OUT_ALT_OD         (0b11u << SUBMODE_POS)

typedef enum {
  portA,
  portB,
  portC,
  portD
} gpio_port_t;

typedef enum {
  pin0,
  pin1,
  pin2,
  pin3,
  pin4,
  pin5,
  pin6,
  pin7,
  pin8,
  pin9,
  pin10,
  pin11,
  pin12,
  pin13,
  pin14,
  pin15,
} gpio_pin_t;

//gpio configuration
typedef struct{
  uint8_t mode;
  uint8_t sub_mode;
  uint8_t pupd; 
} GPIO_PinConfig_t;

GPIO_t* gpio_get_port_handler(gpio_port_t port);
void gpio_clk_enable(GPIO_t *const pGPIO);
void gpio_clk_disable(GPIO_t *const pGPIO);
void gpio_clk_reset(GPIO_t *const pGPIO);
void gpio_get_default_cfg(GPIO_PinConfig_t *pCfg);
void gpio_set_mode(GPIO_t *const pGPIO, gpio_pin_t pin, GPIO_PinConfig_t *pCfg);
uint8_t gpio_read_pin(GPIO_t *const pGPIO, gpio_pin_t pin);
uint16_t gpio_read_port(GPIO_t *const pGPIO);
void gpio_write_pin(GPIO_t *const pGPIO, gpio_pin_t pin, uint8_t value);
void gpio_write_port(GPIO_t *const pGPIO, uint16_t value);
void gpio_toggle_pin(GPIO_t *const pGPIO, gpio_pin_t pin);
uint8_t gpio_lock_port(GPIO_t *const pGPIO, uint16_t pins); //returns 1 if the locking sequence was successfull or pins are already locked