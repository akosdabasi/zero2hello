#pragma once

#include "main_cfg.h"
#include "gpio_driver.h"
#include "rcc_driver.h"
#include "afio_driver.h"
#include "spi_driver.h"
#include "usart_driver.h"

#include "user_snippets.h"

/*----------------- TIMING -------------------*/
void delay_blocking_ms(uint32_t delay_ms);

/*------------------ GPIO -------------------------*/
//pins that shouldnt be used by default: PA15, PA14, PA13 --> PB4(JTAG), PA2, PA3 --> USART2(stlink)
void toggle_led(GPIO_t *pgpio, gpio_pin_t pin);
void config_pin_to_led(GPIO_t *pgpio, gpio_pin_t pin);
void config_pin_to_button_it(GPIO_t *pgpio, gpio_pin_t pin, gpio_callback_t cb);

/*--------------------SPI-----------------------------*/
void config_spi1_to_master();
void config_spi1_to_slave();

/*---------------------USART--------------------------*/
void config_usart2();
void config_usart3();

/*----------------- COMMON --------------------------*/
void zero_array(uint8_t *arr, uint16_t length);
int my_strcmp(const char *str1, const char *str2);
uint32_t my_strlen(const char *str);
