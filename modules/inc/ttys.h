#pragma once

#include "utils.h"
#include "usart_driver.h"

#define TTYS_RX_BUF_SIZE 80
#define TTYS_TX_BUF_SIZE 1024

typedef struct{
  uint8_t send_cr_after_nl;
} ttys_cfg_t;

//performance measurement
typedef enum{
    CNT_RX_UART_ORE,
    CNT_RX_UART_NE,
    CNT_RX_UART_FE,
    CNT_RX_UART_PE,
    CNT_TX_BUF_OVERRUN,
    CNT_RX_BUF_OVERRUN,

    NUM_PMS
} ttys_pms_t;

//per-instance ttys state information.
typedef struct{
  usart_handle_t *husart;
  ttys_cfg_t cfg;
  int fd;
  uint16_t pms[NUM_PMS];
  uint16_t rx_buf_get_idx;
  uint16_t rx_buf_put_idx;
  uint16_t tx_buf_get_idx;
  uint16_t tx_buf_put_idx;
  uint8_t tx_buf[TTYS_TX_BUF_SIZE];
  uint8_t rx_buf[TTYS_RX_BUF_SIZE];
} ttys_handle_t;

extern ttys_handle_t httys1; 
extern ttys_handle_t httys2;  //stdout
extern ttys_handle_t httys3; 

//core module interface functions.
int32_t ttys_get_def_cfg(ttys_cfg_t *cfg);
int32_t ttys_init(ttys_handle_t *const httys);
int32_t ttys_start(ttys_handle_t *const httys);

// Other APIs.
int32_t ttys_putc(ttys_handle_t *const httys, char c);
int32_t ttys_getc(ttys_handle_t *const httys, char* c);
int ttys_get_fd(ttys_handle_t *const httys);