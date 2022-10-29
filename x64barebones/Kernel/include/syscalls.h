#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <video.h>
#include <time.h>

#define REGISTERS 15

int sysWrite(int fd, char * buf, int count);

void sysClear();

unsigned int sysRead(unsigned int fd, char * buf, unsigned int count);

int sysScreenSize();

uint32_t sysWriteAt(const char * buf, uint64_t count, uint16_t x, uint16_t y, Color color);

void saveInfoReg(uint64_t * regDumpPos);

int sysInfoReg(uint64_t * buffer);

char sysCheckBuffer();

void sysClearBuffer(); 



#endif