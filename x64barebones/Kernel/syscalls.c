#include <keyboard.h>
#include <video.h>
#include <defs.h>
#include <lib.h>
#include <interrupts.h>
#include <RTC.h>

static uint64_t infoReg[REGISTERS] = {0};

static int getFormat(int n) {
	int dec = n & 240;
	dec = dec >> 4;
	int units = n & 15;
	return dec * 10 + units;
}

int sysWrite(int fd, char * buf, int count) {
  if(fd != STDERR && fd != STDOUT) {
    return 0;
  }
  if (fd == STDERR) {
    scr_setPenColor((Color){0x00, 0x00, 0xFF});
  }
	for (int i = 0; i < count; i++)
		scr_printChar(buf[i]);
	scr_setPenColor((Color){0x7F, 0x7F, 0x7F});
	
	return count;
}

uint32_t sysWriteAt(const char * buf, uint64_t count, uint16_t x, uint16_t y, Color color) {
	scr_setPenPosition(x, y);
	scr_setPenColor(color);
	for (int i = 0; i < count; i++)
		scr_printChar(buf[i]);
	return scr_getPenX() | ((uint32_t)scr_getPenY() << 16);
}

void sysClear() {
  scr_clear();
}

int sysScreenSize() {
  return scr_getWidth() | scr_getHeight() << 32;
}

/*unsigned int sysRead(unsigned int fd, char * buf, unsigned int count) {
	char c = 0, keyboardResp = 0; 
	int i = 0;

	if(checkIfAvailableKey()) {
		consume_kb_buffer(buf, count);
	}
	while(c != '\n' && keyboardResp != BUFFER_FULL) {
		
		keyboardResp = keyboard_handler();

		if(keyboardResp == VALID_KEY) {
			//c = peek_key();
			//scr_printChar(c);
		
			if(i<count) {
				i++;
			}
		}
		else if(keyboardResp == DELETE_KEY) {
				//scr_printChar('\b');
				if(i > 0) {
					i--;
				}
			}
	}

	for(int j=0 ; j < i ; j++) {				// consumo el buffer de una, hasta el \n o fin de caracteres
		buf[j] = get_key();
	}

	return i;
}*/

unsigned int sysRead(unsigned int fd, char * buf, unsigned int count){
	unsigned int totalRead = 0;
	do {
			_hlt();
			totalRead += kbd_readCharacters(buf + totalRead, count - totalRead);
		} while (totalRead == 0);

	return totalRead;
}

void saveInfoReg(uint64_t * regDumpPos) {
	for(int i = 0 ; i < REGISTERS ; i++) {
		infoReg[i] = regDumpPos[i];
	}
}

void sysInfoReg(uint64_t * buffer) {
	for(int i = 0 ; i < REGISTERS ; i++) {
		buffer[i] = infoReg[i];
	}
}

char * sysTime() {
  char * hours = intToString(getFormat(_NRTCGetHours()));
  char * minutes = intToString(getFormat(_NRTCGetMins()));
  char * seconds =  intToString(getFormat(_NRTCGetSeconds()));
}