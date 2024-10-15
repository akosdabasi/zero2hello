#include "syscalls.h"
#include "ttys.h"

/*
 * @brief System call function for write().
 *
 * @param[in] file File descriptor.
 * @param[in] ptr Data to be written.
 * @param[in] len Length of data.
 *
 * @return Number of characters written, or -1 for error.
 *
 * @note Characters might be dropped due to buffer overrun, and this is not
 *       reflected the return value. An alternative would be to return -1 and
 *       errno=EWOULDBLOCK.
 */
int _write(ttys_handle_t *const httys, const char* ptr, uint32_t len)
{
  uint32_t idx;

  for(idx = 0; idx < len; idx++)
  {
    char c = *ptr++;
    ttys_putc(httys, c);
    if(c == '\n' && httys->cfg.send_cr_after_nl)
    {
      ttys_putc(httys, '\r');
    }
  }
  return 0;
}

/*
 * @brief System call function for read().
 *
 * @param[in] file File descriptor.
 * @param[in] ptr Location of buffer to place characters.
 * @param[in] len Length of buffer.
 *
 * @return Number of characters written, or -1 for error.
 *
 * @note Assumes non-blocking operation.
 */
int _read(ttys_handle_t *const httys, char* ptr, uint32_t len)
{
  int rc = 0;
  char c;

  if (httys->rx_buf_get_idx == httys->rx_buf_put_idx)
  {  
    rc = -1;
  }
  else
  {
    while((uint32_t)rc < len && ttys_getc(httys, &c))
    {
      *ptr++ = c;
      rc++;
    }
  }
  return rc;
}