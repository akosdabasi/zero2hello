#include "l_utils.h"
#include "l_stm32f103rb.h"


#define PULLDOWN  0 
#define PULLUP    1

#define LOW   0
#define HIGH  1
//Modes 
#define MODE_IN                    0U
#define MODE_OUT_2                 2U
#define MODE_OUT_10                1U
#define MODE_OUT_50                3U

//Sub-modes
#define MODE_IN_ANALOG          (0U << 2)
#define MODE_IN_FLOAT           (1U << 2)
#define MODE_IN_PP              (2U << 2)

#define MODE_OUT_GP_PP          (0U << 2)
#define MODE_OUT_GP_OD          (1U << 2)
#define MODE_OUT_ALT_PP         (2U << 2)
#define MODE_OUT_ALT_OD         (3U << 2)



typedef enum {
  gpio_input,
  gpio_input_pu,    //pull-up
  gpio_input_pd,    //pull-down
  gpio_analog,
  gpio_output_od,   //open-drain
  gpio_output_pp,   //push-pull
  gpio_alt_pp,      //alternate function push-pull
  gpio_alt_od       //alternate function open-drain
} gpio_mode_t;

typedef enum {
  gpio_2mhz,
  gpio_10mhz,
  gpio_50mhz
} gpio_speed_t;

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

void gpio_clk_enable(GPIO_t* const pGPIO);
void gpio_clk_disable(GPIO_t* const pGPIO);
void gpio_get_default_cfg(GPIO_PinConfig_t *pCfg);
void gpio_set_mode(GPIO_t* const pGPIO, gpio_pin_t pin, GPIO_PinConfig_t *pCfg);
uint8_t gpio_read_pin(GPIO_t* const pGPIO, gpio_pin_t pin);
uint16_t gpio_read_port(GPIO_t* const pGPIO);
void gpio_write_pin(GPIO_t* const pGPIO, gpio_pin_t pin, uint8_t value);
void gpio_write_port(GPIO_t* const pGPIO, uint16_t value);
void gpio_toggle_pin(GPIO_t* const pGPIO, gpio_pin_t pin);
