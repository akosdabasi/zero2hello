#pragma once

#include "mcu_peripherals.h"
#include "rcc_driver.h"

typedef enum {
  USART_DATA_LENGTH_8 = 0,
  USART_DATA_LENGTH_9 = 1
} usart_data_length_t;

typedef enum {
  USART_PARITY_DISABLED = 0,
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

typedef struct {
  usart_data_length_t data_length;
  usart_parity_t parity;

} USART_Cfg_t;

typedef struct {
  USART_t *instance;
  USART_Cfg_t *cfg;
} usart_handle_t;

static inline void usart_send_break(USART_t *const pusart ){SET_BIT(pusart->CR1, USART_CR1_SBK_Pos);}
static inline void usart_mute(USART_t *const pusart ){SET_BIT(pusart->CR1, USART_CR1_RWU_Pos);}
