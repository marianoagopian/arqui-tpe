#include <stdint.h>
#include <syscalls.h>
#include <lib.h>
#include <defs.h>
#include <interrupts.h>
#include <keyboard.h>

#define ZERO_EXCEPTION_ID 0

static void zeroDivision();
static void exceptionHandler();

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
	exceptionHandler("An exception has occurred dividing by zero\n", registerDumpPos);
}

static void exceptionHandler(char * msg, uint64_t * registerDumpPos) {
  sysWrite(STDERR, msg, _strlen(msg));
  printRegisters(registerDumpPos);
  sysWrite(STDERR, "Press any key to continue.", _strlen("Press any key to continue"));
  do { _hlt(); } while(kbd_getBufferLength() == 0);
}
