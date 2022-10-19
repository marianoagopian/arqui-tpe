#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./syscalls.h"

/* --- CONSTANTS  --- */
#define SCREEN 1

// --- Caracteres especiales ---
#define PAUSE_SCREEN 17
#define ESCAPE_KEY 27


void realTime();

int scanf(char * format, char * dest);

int putChar(int character);

void print(char * string, int length);

void putchar(char c);

// void clear_screen(){
//     sys_clear_screen();
// }

void puts(char * string);

void read_line(char * buf, int length);

// unsigned int consume_buffer(char * buffer, int length){
//     return sys_consume_stdin(buffer, length);
// }

char getchar();

int strlen(const char * string);
#endif