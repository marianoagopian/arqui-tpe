#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#include <stdint.h>
#include <color.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2
//#define KBDIN 3

/* The width of a character in pixels. */
#define CHAR_WIDTH 9
/* The height of a character in pixels. */
#define CHAR_HEIGHT 16

uint64_t sys_read(uint64_t fd, char* buf, uint64_t count);
uint64_t sys_write(uint64_t fd, const char* buf, uint64_t count);
// uint64_t sys_time(void);
// uint64_t sys_date(void);
// uint64_t sys_millis(void);
int sys_time();
void sys_clear_screen();
uint32_t sys_write_at(const char* buf, uint64_t count, uint16_t x, uint16_t y, Color color);
// uint64_t sys_screen_size();
// uint64_t sys_pollread(uint64_t fd, char* buf, uint64_t count, uint64_t timeout_ms);
// void sys_drawpoint(uint16_t x, uint16_t y, Color color);
// void sys_drawrect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color color);
// void sys_drawline(uint16_t fromX, uint16_t fromY, uint16_t toX, uint16_t toY, Color color);
uint8_t sys_info_reg(uint64_t reg[15]);
unsigned int sys_printmem(uint64_t position, char * buffer);
void sys_draw_point(uint16_t x, uint16_t y, Color color);
int sys_screen_size();
void sys_clear_buffer();
char sys_check_buffer();
void set_level(int num);

#endif
