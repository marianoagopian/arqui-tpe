#include <stdint.h>
#include <syscalls.h>
#include <lib.h>
#include <defs.h>
#include <interrupts.h>
#include <keyboard.h>

extern void resetmain(void);

#define ZERO_EXCEPTION_ID 0

static void zeroDivision();
static void handlerException();

void exceptionDispatcher(int exception, uint64_t * registerDumpPos) {
  switch (exception) {
    case ZERO_EXCEPTION_ID:
      zeroDivision(registerDumpPos);
      break;
    
    default:
      break;
    }
}

static void zeroDivision(uint64_t * registerDumpPos) {
	handlerException("An exception has occurred dividing by zero\n", registerDumpPos);
}

static void handlerException(char * msg, uint64_t * registerDumpPos) {
  sysWrite(STDERR, msg, _strlen(msg));
  printRegisters(registerDumpPos);
  sysWrite(STDERR, "Press any key to continue.", _strlen("Press any key to continue"));

  kbd_clearBuffer();
  char *aux = {0};
  do { _hlt(); sysRead(STDOUT, aux, 2); } while(*aux == 0);

  kbd_clearBuffer();
  scr_clear();
  _cli();
  resetmain();
}
