#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <stdint.h>

/* The width of a character in pixels. */
#define CHAR_WIDTH 9
/* The height of a character in pixels. */
#define CHAR_HEIGHT 16

typedef struct {
	uint8_t b;
	uint8_t g;
	uint8_t r;
} Color;


/* Clears the whole screen to black. */
void scr_clear(void);

/* Sets a specified rectangle of pixels on the screen to the specified color. */
void scr_drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color color);

/* Sets the pen color for drawing characters on the screen as a console. */
void scr_setPenColor(Color color);

/* Advances the pen to the beginning of the next line. */
void scr_printNewline(void);

/* Prints a single character with the pen, wrapping around the end of the screen and pushing old lines up if necessary. */
void scr_printChar(char c);

/* Prints a string of characters with the pen, wrapping around the end of the screen and pushing old lines up if necessary.
Returns the new pen position as a 32 bit number, where the 16 lowest bits are the x and the upper 16 bits are the y. */
uint32_t scr_print(const char* s);

int getLevel();

void setLevel(int num);

#endif
