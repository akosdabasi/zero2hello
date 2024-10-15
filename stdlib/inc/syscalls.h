#pragma once

#include "ttys.h"

int _write(ttys_handle_t *const httys, const char* ptr, uint32_t len);
int _read(ttys_handle_t *const httys, char* ptr, uint32_t len);

