#pragma once

#include "ttys.h"

#define CONSOLE_CMD_BFR_SIZE 80

typedef struct 
{
  ttys_handle_t *httys;
  char cmd_buf[CONSOLE_CMD_BFR_SIZE];
  uint16_t num_cmd_buf_chars;
  uint8_t first_run_done;
} console_handler_t;

extern console_handler_t hconsole;

// Core module interface functions.
int32_t console_attach_ttys(ttys_handle_t *const httys);
int32_t console_init(void);
int32_t console_run(void);