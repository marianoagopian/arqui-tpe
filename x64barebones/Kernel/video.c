#include <video.h>
#include <font.h>
#include <stdint.h>
#include <string.h>
#include <syscalls.h>

struct vbe_mode_info_structure {
    uint16_t attributes;        // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    uint8_t window_a;           // deprecated
    uint8_t window_b;           // deprecated
    uint16_t granularity;       // deprecated; used while calculating bank numbers
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr;      // deprecated; used to switch banks from protected mode without returning to real mode
    uint16_t pitch;         // number of bytes per horizontal line
    uint16_t width;         // width in pixels
    uint16_t height;            // height in pixels
    uint8_t w_char;         // unused...
    uint8_t y_char;         // ...
    uint8_t planes;
    uint8_t bpp;            // bits per pixel in this mode
    uint8_t banks;          // deprecated; total number of banks in this mode
    uint8_t memory_model;
    uint8_t bank_size;      // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    uint8_t image_pages;
    uint8_t reserved0;

    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direct_color_attributes;

    uint32_t framebuffer;       // physical address of the linear frame buffer; write here to draw to the screen
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size;   // size of memory in the framebuffer but not being displayed on the screen
    uint8_t reserved1[206];
} __attribute__ ((packed));

struct vbe_mode_info_structure* screenData = (void*)0x5C00;

static void* getPtrToPixel(uint16_t x, uint16_t y) {
    return (void*)(screenData->framebuffer + 3 * (x + (y * (uint64_t)screenData->width)));
}

uint16_t penX = 0, penY = 0;
Color penColor = {0x7F, 0x7F, 0x7F};

uint16_t scr_getWidth(void) {
    return screenData->width;
}

void scr_setPenPosition(uint16_t x, uint16_t y) {
    // We clamp the pen (x,y) to ensure there is enough space to draw a char in that position.
    uint16_t maxX = screenData->width - CHAR_WIDTH;
    uint16_t maxY = screenData->height - CHAR_HEIGHT;

    penX = x < maxX ? x : maxX;
    penY = y < maxY ? y : maxY;
}

void scr_setPenColor(Color color) {
  penColor = color;
}

uint16_t scr_getHeight(void) {
    return screenData->height;
}

uint16_t scr_getPenX(void) {
    return penX;
}

uint16_t scr_getPenY(void) {
    return penY;
}

void scr_clear(void) {
    uint8_t* pos = (uint8_t*)((uint64_t)screenData->framebuffer);
    for (uint32_t len = 3 * (uint32_t)screenData->width * screenData->height; len; len--, pos++)
        *pos = 0;
    penX = 0;
    penY = 0;
}

void scr_setPixel(uint16_t x, uint16_t y, Color color) {
    if (x >= screenData->width || y >= screenData->height)
        return;

    Color* pos = (Color*)getPtrToPixel(x, y);
    *pos = color;
}

void scr_drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color color) {
    if (x >= screenData->width || y >= screenData->height)
        return;
    
    uint16_t maxWidth = screenData->width - x;
    if (width > maxWidth) width = maxWidth;
    
    uint16_t maxHeight = screenData->height - y;
    if (height > maxHeight) height = maxHeight;

    Color* ptr = (Color*)getPtrToPixel(x, y);
    unsigned int adv = screenData->width - width;
    for (int i=0; i<height; i++) {
        for (int c=0; c<width; c++)
            *(ptr++) = color;
        ptr += adv;
    }
}

int level = 1;

void setLevel(int num){
    level = num;
}

int getLevel() {
  return level;
}

void level1(char *data){
    for (int h=0; h<CHAR_HEIGHT * level; h++) {
    	Color* pos = (Color*)getPtrToPixel(penX, penY+h);
    	if (*data & 0x01) pos[0] = penColor;
    	if (*data & 0x02) pos[1] = penColor;
    	if (*data & 0x04) pos[2] = penColor;
    	if (*data & 0x08) pos[3] = penColor;
    	if (*data & 0x10) pos[4] = penColor;
    	if (*data & 0x20) pos[5] = penColor;
    	if (*data & 0x40) pos[6] = penColor;
    	if (*data & 0x80) pos[7] = penColor;
    	data++;
    	if (*data & 0x01) pos[8] = penColor;
    	data++;
    }
}

void level2(char *data){
    for (int h=0; h<CHAR_HEIGHT * level; h+=level) {
    	Color* pos = (Color*)getPtrToPixel(penX, penY+h);
      Color* pos2 = (Color*)getPtrToPixel(penX, penY+h+1);
    	if (*data & 0x01) pos[0] = penColor, pos[1] = penColor, pos2[0] = penColor, pos2[1] = penColor;
    	if (*data & 0x02) pos[2] = penColor, pos[3] = penColor, pos2[2] = penColor, pos2[3] = penColor;
    	if (*data & 0x04) pos[4] = penColor, pos[5] = penColor, pos2[4] = penColor, pos2[5] = penColor;
    	if (*data & 0x08) pos[6] = penColor, pos[7] = penColor, pos2[6] = penColor, pos2[7] = penColor;
    	if (*data & 0x10) pos[8] = penColor, pos[9] = penColor, pos2[8] = penColor, pos2[9] = penColor;
    	if (*data & 0x20) pos[10] = penColor, pos[11] = penColor, pos2[10] = penColor, pos2[11] = penColor;
    	if (*data & 0x40) pos[12] = penColor, pos[13] = penColor, pos2[12] = penColor, pos2[13] = penColor;
    	if (*data & 0x80) pos[14] = penColor, pos[15] = penColor, pos2[14] = penColor, pos2[15] = penColor;
    	data++;
    	if (*data & 0x01) pos[16] = penColor, pos[17] = penColor, pos2[16] = penColor, pos2[17] = penColor;
    	data++;
    }
}

void scr_printChar(char c) {
    if(c == 0){
        return;
    }
    if (c == '\n') {
        scr_printNewline();
        return;
    }

    Color black = {0x00, 0x00, 0x00};

    if (c == '\b') {
        if(penX < CHAR_WIDTH * 4){
            //if(penY != 0) penY -= CHAR_HEIGHT;
            //penX = (sysScreenSize() / 9 - 1) * 9;
            return;
        }
        penX -= CHAR_WIDTH * level;
        scr_drawRect(penX, penY, CHAR_WIDTH * level, CHAR_HEIGHT * level, black);
        return;
    }


    if (c >= FIRST_CHAR && c <= LAST_CHAR) {
	    const char* data = font + 32*(c-33);
	    if(level == 1){
            level1(data);
        }
        if(level == 2){
            level2(data);
        }
    }

    penX += CHAR_WIDTH * level;
    if (penX > screenData->width - level * CHAR_WIDTH)
        scr_printNewline();
}

void scr_printNewline(void) {
    penX = 0; // pen x is set to full left.

    // If there is space for another line, we simply advance the pen y. Otherwise, we move up the entire screen and clear the lower part.
    if (penY + (2*CHAR_HEIGHT * level) <= screenData->height) {
        penY += CHAR_HEIGHT * level;
    } else {
        void* dst = (void*)((uint64_t)screenData->framebuffer);
        void* src = (void*)(dst + 3 * (CHAR_HEIGHT * level * (uint64_t)screenData->width));
        uint64_t len = 3 * ((uint64_t)screenData->width * (screenData->height - level * CHAR_HEIGHT));
        memcpy(dst, src, len);
        memset(dst+len, 0, 3 * (uint64_t)screenData->width * level * CHAR_HEIGHT);
    }
}

uint32_t scr_print(const char* s) {
    for (; *s != 0; s++)
		  scr_printChar(*s);
    return penX | ((uint32_t)penY << 16);
}

uint32_t scr_println(const char* s) {
    scr_print(s);
    scr_printNewline();
    return penX | ((uint32_t)penY << 16);
}
