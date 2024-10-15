#pragma once

#include "utils.h"

#define TTYS_RX_BUF_SIZE 80
#define TTYS_TX_BUF_SIZE 1024

typedef struct{
  uint8_t send_cr_after_nl;
} ttys_cfg_t;

//forward declaration
struct ttys_handle_t;

typedef struct ttys_handle_t ttys_handle_t;

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