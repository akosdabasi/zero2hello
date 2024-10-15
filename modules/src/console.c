#include "console.h"
#include "syscalls.h"

#define PROMPT _write(hconsole.httys, "> ", 2)
#define NEWLINE _write(hconsole.httys, "\n", 3)
#define DELETE _write(hconsole.httys, "\b \b", 3)

int isprint(int c)
{
  // Check if the character is within the printable ASCII range
  if (c >= 32 && c <= 126) 
  {
    return 1;  // Return 1 if printable
  }
  else
  {
    return 0;  // Return 0 if not printable
  }
}

//global consol handler
console_handler_t hconsole = {.httys = &httys2};

// Core module interface functions.
int32_t console_attach_ttys(ttys_handle_t *const httys)
{
  if(!httys)return -1;

  hconsole.httys = httys;

  return 0;
}

int32_t console_init(void)
{
  //todo: initialize lower modules
  return 0;
}

int32_t console_run(void)
{
  char c;
  if (!hconsole.first_run_done)
  {
    hconsole.first_run_done = 1;
    PROMPT;
  }
          
  while(ttys_getc(hconsole.httys, &c))
  {

    // Handle processing completed command line.
    if (c == '\n' || c == '\r')
    {
      hconsole.cmd_buf[hconsole.num_cmd_buf_chars] = '\0';
      NEWLINE;
      //cmd_execute(hconsole.cmd_bfr);
      hconsole.num_cmd_buf_chars = 0;
      PROMPT;
      continue;
    }

    // Handle backspace/delete.
    if (c == '\b' || c == '\x7f')
    {
      if (hconsole.num_cmd_buf_chars > 0)
      {
        // Overwrite last character with a blank.
        DELETE;
        hconsole.num_cmd_buf_chars--;
      }
      continue;
    }

    // Echo the character back.
    if (isprint(c)) {
      if (hconsole.num_cmd_buf_chars < (CONSOLE_CMD_BFR_SIZE-1))
      {
        hconsole.cmd_buf[hconsole.num_cmd_buf_chars++] = c;
        _write(hconsole.httys, &c, 1);
      }
      else
      {
        // No space in buffer for the character, so ring the bell.
        _write(hconsole.httys, "\a", 1);
      }
      continue;
    }
          
  }
  return 0;
}