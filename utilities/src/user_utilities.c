#include "user_utilities.h"

/*----------------- TIMING -------------------*/
void delay_blocking_ms(uint32_t delay_ms)
{
  uint32_t start = ticks;
  while(ticks - start < delay_ms);
}


/*------------------ GPIO -------------------------*/
void toggle_led(GPIO_t *pgpio, gpio_pin_t pin)
{
  gpio_toggle_pin(pgpio, pin);
}

/*--------------------SPI-----------------------------*/
void config_spi1_to_master()
{
   //PA5 - SCK
  GPIO_PinConfig_t sck_cfg;
  sck_cfg.mode = MODE_OUT_2MHz;
  sck_cfg.sub_mode = SUBMODE_OUT_ALT_PP;

  //PA6 - MISO
  GPIO_PinConfig_t miso_cfg;
  miso_cfg.mode = MODE_IN;
  miso_cfg.sub_mode = SUBMODE_IN_FLOAT;

  //PA7 - MOSI
  GPIO_PinConfig_t mosi_cfg;
  mosi_cfg.mode = MODE_OUT_2MHz;
  mosi_cfg.sub_mode = SUBMODE_OUT_ALT_PP;
  
  //PA4 - NSS
  GPIO_PinConfig_t nss_cfg;
  nss_cfg.mode = MODE_OUT_2MHz;
  nss_cfg.sub_mode = SUBMODE_OUT_ALT_PP; //nss output enabled

  //configure gpio pins
  gpio_clk_enable(GPIOA);
  gpio_set_mode(GPIOA, 5, &sck_cfg);
  gpio_set_mode(GPIOA, 6, &miso_cfg);
  gpio_set_mode(GPIOA, 7, &mosi_cfg);
  gpio_set_mode(GPIOA, 4, &nss_cfg);

  //configure spi
  spi_get_default_cfg(hspi1.cfg); //use default configuration
}

void config_spi1_to_slave()
{
  //PA5 - SCK
  GPIO_PinConfig_t sck_cfg;
  sck_cfg.mode = MODE_IN;
  sck_cfg.sub_mode = SUBMODE_IN_FLOAT;

  //PA6 - MISO
  GPIO_PinConfig_t miso_cfg;
  miso_cfg.mode = MODE_OUT_2MHz;
  miso_cfg.sub_mode = SUBMODE_OUT_ALT_PP;

  //PA7 - MOSI
  GPIO_PinConfig_t mosi_cfg;
  mosi_cfg.mode = MODE_IN;
  mosi_cfg.sub_mode = SUBMODE_IN_FLOAT;
  
  //PA4 - NSS
  GPIO_PinConfig_t nss_cfg;
  mosi_cfg.mode = MODE_IN;
  mosi_cfg.sub_mode = SUBMODE_IN_FLOAT; //nss output enabled

  //configure gpio pins
  gpio_clk_enable(GPIOA);
  gpio_set_mode(GPIOA, 5, &sck_cfg);
  gpio_set_mode(GPIOA, 6, &miso_cfg);
  gpio_set_mode(GPIOA, 7, &mosi_cfg);
  gpio_set_mode(GPIOA, 4, &nss_cfg);

  //configure spi
  SPI_Config_t spi_cfg;
  spi_get_default_cfg(&spi_cfg); //use default configuration
  spi_cfg.mode = SPI_MODE_SLAVE;

  hspi1.cfg = &spi_cfg;
}

/*---------------------USART--------------------------*/
void config_usart2()
{
  //PA2 - TX
  GPIO_PinConfig_t tx_cfg;
  tx_cfg.mode = MODE_OUT_2MHz;
  tx_cfg.sub_mode = SUBMODE_OUT_ALT_PP;

  //PA3 - RX
  GPIO_PinConfig_t rx_cfg;
  rx_cfg.mode = MODE_IN;
  rx_cfg.sub_mode = SUBMODE_IN_FLOAT;

  //configure gpio pins
  gpio_clk_enable(GPIOA);
  gpio_set_mode(GPIOA, 2, &tx_cfg);
  gpio_set_mode(GPIOA, 3, &rx_cfg);

  //configure usart
  usart_get_default_cfg(husart2.cfg); //use default configuration
}

void config_usart3()
{
  //PB10 - TX
  GPIO_PinConfig_t tx_cfg;
  tx_cfg.mode = MODE_OUT_2MHz;
  tx_cfg.sub_mode = SUBMODE_OUT_ALT_PP;

  //PB11 - RX
  GPIO_PinConfig_t rx_cfg;
  rx_cfg.mode = MODE_IN;
  rx_cfg.sub_mode = SUBMODE_IN_FLOAT;

  //configure gpio pins
  gpio_clk_enable(GPIOB);
  gpio_set_mode(GPIOB, 10, &tx_cfg);
  gpio_set_mode(GPIOB, 11, &rx_cfg);

  //configure usart
  usart_get_default_cfg(husart3.cfg); //use default configuration
}

/*-------------------------LED---------------------------*/
void config_pin_to_led(GPIO_t *pgpio, gpio_pin_t pin)
{
  //LED
  GPIO_PinConfig_t led_cfg;
  led_cfg.mode = MODE_OUT_2MHz;
  led_cfg.sub_mode = SUBMODE_OUT_GP_PP;

  //configure gpio pins
  gpio_clk_enable(pgpio);
  gpio_set_mode(pgpio, pin, &led_cfg);
}

void config_pin_to_button_it(GPIO_t *pgpio, gpio_pin_t pin, gpio_callback_t cb)
{
  //BUTTON
  GPIO_PinConfig_t btn_cfg;
  btn_cfg.mode = MODE_IN;
  btn_cfg.sub_mode = SUBMODE_IN_FLOAT;

  //configure gpio pins
  gpio_clk_enable(pgpio);
  gpio_set_mode(pgpio, pin, &btn_cfg);

  gpio_port_t port;
  if(pgpio == GPIOA) port = portA;
  else if(pgpio == GPIOB) port = portB;
  else if(pgpio == GPIOC) port = portC;
  else if(pgpio == GPIOD) port = portD;
  else return;

  gpio_cfg_irq(port, pin, EXTI_TRIGGER_RISING_EDGE, cb);

  gpio_en_irq(port, pin);
}

/*----------------- COMMON --------------------------*/
void zero_array(uint8_t *arr, uint16_t length)
{
  for(uint16_t i = 0; i < length; arr[i++] = 0);
}

int my_strcmp(const char *str1, const char *str2)
{
  // Loop through both strings
  while(*str1 && *str2)
  {
    // If characters differ, return
    if(*str1 != *str2)return 0;
    
    // Move to the next character in both strings
    str1++;
    str2++;
  }
  
  // If both strings are equal up to the null terminator, check if one is longer
  return 1;
}

uint32_t my_strlen(const char *str)
{
  uint32_t length = 0;

  // Iterate through the string until the null terminator is reached
  while (str[length] != '\0')
  {
    length++;
  }

  return length;
}