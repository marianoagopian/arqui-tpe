#ifndef	_KEYBOARD_H
#define _KEYBOARD_H

/*--------  DEPENDENCIES --------*/
#include <stdint.h>
#include <syscalls.h>

/* --- CONSTANTS  --- */
#define SEMICOLON 19

extern char getKey();

/*
 * << keyboard_handler >>
 * ----------------------------------------------------------------------
 *  Descripcion: Handles keyboard functionality
 * ----------------------------------------------------------------------
 *  Recibe: --
 *  Devuelve:
 *      1 <=> wrote buffer
 *      0 <=> otherwise
 */
void keyboard_handler();

unsigned int kbd_readCharacters(char* buf, unsigned int n);

int kbd_getBufferLength();

void kbd_clearBuffer();

#endif