#include "./include/syscalls.h"

#define SYS_READ_FROM_SCREEN 0
#define SYS_WRITE_TO_SCREEN 1
#define SYS_CLEAR_SCREEN 2
#define SYS_REGISTER_PROCESS 3 
#define SYS_RTC 4
#define SYS_CONSUME_STDIN 7
#define SYS_KILL_PROCESS 8
#define SYS_PAUSE_PROCESS 9
#define SYS_INFOREG 10
#define SYS_PRINTMEM 11

#define NULL 0

extern uint64_t syscaller(uint64_t syscallID, uint64_t param1, uint64_t param2, uint64_t param3);

unsigned int sys_write(const char * string, unsigned int length){
    return syscaller(SYS_WRITE_TO_SCREEN, (uint64_t) string, (uint64_t) length, NULL);        // feo arreglar
}   

unsigned int sys_read(char * buf, unsigned int length){
    return syscaller(SYS_READ_FROM_SCREEN, (uint64_t) buf, (uint64_t) length, NULL);        // feo arreglar
}