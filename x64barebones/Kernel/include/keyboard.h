#ifndef	_KEYBOARD_H
#define _KEYBOARD_H

/*--------  DEPENDENCIES --------*/
#include <stdint.h>
#include <syscalls.h>

/* --- CONSTANTS  --- */
#define SHIFT 19


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


/*
 * << consume_kb_buffer >>
 * ----------------------------------------------------------------------
 * Descripcion: Consumes keyboard buffer DUH
 * ----------------------------------------------------------------------
 * Recibe: --
 * Devuelve: 
 *      (uint) bytes consumed
 */
unsigned int consume_kb_buffer(char * buf, unsigned int count);

char checkIfAvailableKey();

#endif