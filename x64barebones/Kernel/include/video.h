#ifndef _VIDEO_H
#define _VIDEO_H

/* --- CONSTANTS --- */
// Columna de comienzo en pantalla
#define START 0

// Dimensión de pantalla
#define LENGTH 160

#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 160

// Colores 
#define STDOUT_COLOR 7
#define STDERR_COLOR 4

void ncClear();
void deleteKey(unsigned int * offset, unsigned int start,  unsigned int length , unsigned int step);
unsigned int write(const char * buf, char format, unsigned int count, unsigned int * offset, unsigned int start,  unsigned int length , unsigned int step);
unsigned int writeDispatcher(unsigned int fd, const char * buf, unsigned int count);
unsigned int readDispatcher(unsigned int fd, const char * buf, unsigned int count);

#endif