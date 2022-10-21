#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define NO_KEY 0
#define VALID_KEY 1
#define DELETE_KEY 2
#define BUFFER_FULL 3
#define UNMAPPED 4

#define ESCAPE_KEY 27
#define F1_KEY 17
#define F2_KEY 18
#define F3_KEY 19
#define F5_SCAN_CODE 0X3F

extern uint64_t getKey();

char keyboard_handler();

char get_key();

char peek_key();

char checkIfAvailableKey();

unsigned int consume_kb_buffer(char * buf, unsigned int count);
#endif