#pragma once

#include "mcu_peripherals.h"
#include "rcc_driver.h"

typedef enum {
  USART_MODE_RX = 0,             
  USART_MODE_TX = 1,             
  USART_MODE_TX_RX = 2
} usart_mode_t;

typedef enum {
  USART_DATA_LENGTH_8 = 0,
  USART_DATA_LENGTH_9 = 1
} usart_data_length_t;

typedef enum {
  USART_PARITY_NONE = 0,
  USART_PARITY_EVEN = 1,
  USART_PARITY_ODD = 2,
}usart_parity_t;

typedef enum {
  USART_STOP_BITS_1 = 0,
  USART_STOP_BITS_0_5 = 1,
  USART_STOP_BITS_2 = 2,
  USART_STOP_BITS_1_5 = 3,
} usart_stop_bits_t;

typedef enum {
  USART_HW_FLOWCTRL_NONE = 0,
  USART_HW_FLOWCTRL_RTS = 1,
  USART_HW_FLOWCTRL_CTS = 2,
  USART_HW_FLOWCTRL_RTS_CTS = 3,
} usart_hw_flow_ctrl_t;

typedef enum {
  USART_WAKEUP_IDLE = 0,
  USART_WAKEUP_ADDRESS = 1,
} usart_wakeup_t;

typedef enum {
  USART_OVERSAMPLING_8 = 0,
  USART_OVERSAMPLING_16 = 1,
} usart_oversampling_t;

typedef enum {
  USART_BAUDRATE_9600 = 9600,
  USART_BAUDRATE_19200 = 19200,
  USART_BAUDRATE_38400 = 38400,
  USART_BAUDRATE_115200 = 115200,
} usart_baudrate_t;

typedef struct {
  usart_mode_t mode;
  usart_data_length_t data_length;
  usart_parity_t parity;
  usart_stop_bits_t stop_bits;
  usart_oversampling_t oversampl;
  usart_baudrate_t baudrate;
  usart_hw_flow_ctrl_t hw_flow_ctrl;
  usart_wakeup_t wakeup;
} USART_Config_t;

typedef enum {
  USART_EVENT_BYTE_RECEIVED = 0,
  USART_EVENT_BYTE_SENT,
  USART_EVENT_TRANS_COMPLETE,
  USART_EVENT_OVR_ERR,
  USART_EVENT_CRC_ERR
} usart_event_t;

//forward declaration
struct usart_handle_t;

//usart event callback function
typedef void (*usart_callback_t)(struct usart_handle_t *const husart, usart_event_t event); 

typedef struct usart_handle_t{
  USART_t *instance;
  USART_Config_t *cfg;
} usart_handle_t;

//global usart handlers
extern usart_handle_t husart1;
extern usart_handle_t husart2;
extern usart_handle_t husart3;

//return the most common configuration
void usart_get_default_cfg(USART_Config_t *pCfg);

//control
void usart_clk_enable(usart_handle_t *const husart);
void usart_clk_disable(usart_handle_t *const husart);
void usart_reset(usart_handle_t *const husart);

void usart_init(usart_handle_t *const husart);

static inline void usart_send_break(USART_t *const pusart ){SET_BIT(pusart->CR1, USART_CR1_SBK_Pos);}
static inline void usart_mute(USART_t *const pusart ){SET_BIT(pusart->CR1, USART_CR1_RWU_Pos);}

//blocking transmit/receive functions
void usart_transmit(usart_handle_t *const husart, uint8_t *data, uint8_t length);
void usart_receive(usart_handle_t *const husart, uint8_t *data, uint8_t length);


/*----------------- INTERRUPT HANDLING -----------------------*/
//interrupt driven mode (non-blocking)
void usart_nvic_enable_it(usart_handle_t* husart);
void usart_nvic_disable_it(usart_handle_t* husart);
void usart_transmit_it(usart_handle_t *const husart, uint8_t *data, uint8_t length);
void usart_transmit_it(usart_handle_t *const husart, uint8_t *data, uint8_t length);
void usart_register_cb(usart_handle_t *const husart, usart_callback_t cb);