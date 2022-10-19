#ifndef _SYSCALLS_H
#define _SYSCALLS_H

#include <stdint.h>

unsigned int sys_write(const char * string, unsigned int length);

unsigned int sys_read(char * buf, unsigned int length);

#endif