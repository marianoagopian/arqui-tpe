#include "./include/syscalls.h"
#include <color.h>
#include <functions.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static uint32_t penpos = 0;

static const uint8_t scanCodeTable[256] = {
  0,    0,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  '9',   '0',   '-',  '=',    '\b',
  '    ', 'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',   'O',  'P',  '[',   ']',  '\n',
  0,     'A',  'S', 'D',  'F',  'G',  'H',  'J',  'K',  'L',  ';',  '\'',
  0,    0,  '\\',   'Z',  'X',     'C', 'V', 'B',  'N',  'M',  ',',  '.',  '/',    0,
  '*',     0,  ' ',    0,     0,     0,    0,       0,         0,
};

void putchar(char c) {
    print(&c, 1);
}

void print(const char* buf, uint64_t count) {
    penpos = _sys_write(STDOUT, buf, count);  // arreglar el tema del color
}

void clearscreen() {
    sys_clearscreen();
    penpos = 0;
}

char getChar() {
	char c;
	// uint16_t rectX = penpos & 0x0000FFFF;
	// uint16_t rectY = (penpos >> 16) + 13;
    // sys_read(STDIN, &c, 1);

// 	uint8_t isBlinkerOn = 1;
// 	sys_drawrect(rectX, rectY, 9, 3, gray);

//	while (sys_read(STDIN, &c, 1) == 0)  {
// 		if (isBlinkerOn) {
// 			sys_drawrect(rectX, rectY, 9, 3, black);
// 			isBlinkerOn = 0;
// 		} else {
// 			sys_drawrect(rectX, rectY, 9, 3, gray);
// 			isBlinkerOn = 1;
// 		}
//	}

// 	if (isBlinkerOn)
// 			sys_drawrect(rectX, rectY, 9, 3, black);

    scanf(&c,1);
	return c;
}

void scanf(char* readbuf, uint64_t maxlen) {
    int read = sys_read(STDIN, readbuf, maxlen);
    print(readbuf, read);
    // if (maxlen == 0)
    //     return;

    // // We read up to maxlen-1 characters from the input.
    // uint64_t count = 0;
    // do {
    //     char c = getChar();

    //     if (c == '\n') { // If a '\n' is found, we zero-terminate the string and return.
    //         readbuf[MIN(count, maxlen-1)] = '\0';
    //         // print(&c, 1);
    //         return;
    //     // } if (c == '\b') { If a '\b' character is found, we remove the last char from readbuf.
    //         // if (count != 0) {
    //         //     count--;
    //         //     uint32_t penX = penpos & 0x0000FFFF;
    //         //     uint32_t penY = penpos >> 16;
    //         //     if (penX < 9) {
    //         //         if (penY != (uint32_t)0) penY -= 16;
    //         //         penX = ((sys_screensize() & 0xFFFFFFFF) / 9 - 1) * 9;
    //         //     } else {
    //         //         penX -= 9;
    //         //     }
    //         //     penpos = penX | (penY << 16);
    //         //     sys_drawrect(penX, penY, 9, 16, black);
    //         // }
    //     } else {
    //         // We add the read character to the buffer and continue.
	//         // print(&c, 1);
    //         if (count < maxlen-1)
    //             readbuf[count] = c;
    //         count++;
    //     }
    // } while (1);
}

int strlen(const char * str) {
	int ans = 0;
	for (int i = 0; str[i] != 0; i++) {
		ans++;
	}
    return ans;
}
