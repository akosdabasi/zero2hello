#include "_string.h"

void _memset(uint8_t *byte_ptr, uint8_t val, uint32_t num)
{

  // Set memory byte-by-byte
  for(uint32_t i = 0; i < num; byte_ptr[i++] = val);

}
