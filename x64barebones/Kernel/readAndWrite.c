#include <keyboard.h>
#include <video.h>
#include <defs.h>
#include <lib.h>


void sysWrite(int fd, char * buf, int count) {
  if(fd != STDERR && fd != STDOUT) {
    return 0;
  }
  if (fd == STDERR) {
    scr_setPenColor((Color){0x00, 0x00, 0xFF});
  }
  scr_print(buf);
}

void sysClear() {
  scr_clear();
}

int sysScreenSize() {
  return scr_getWidth() | scr_getHeight() << 32;
}

unsigned int read_stdin(unsigned int fd, char * buf, unsigned int count) {
	char c = 0, keyboardResp = 0; 
	int i = 0;

	while(c != '\n' && keyboardResp != BUFFER_FULL) {
		keyboardResp = keyboard_handler();

		if(keyboardResp == VALID_KEY) {
			c = peek_key();
			scr_printChar(c);
		
			if(i<count)
				i++;
		}
		// else if(keyboardResp == DELETE_KEY) {
		// 	if(currentVideoPosition > initialPos) {  // no dejo que borre lo que ya habia
		// 		writeDispatcher(fd,"\b",1);
		// 		if(i > 0)
		// 			i--;
		// 	}
		// }
	}	

	for(int j=0 ; j < i ; j++)				// consumo el buffer de una, hasta el \n o fin de caracteres
		buf[j] = get_key();

	return i;
}

unsigned int readDispatcher(unsigned int fd, const char * buf, unsigned int count) {
  if(checkIfAvailableKey())
    return consume_kb_buffer(buf,count);		// Si el key buffer no esta vacio, primero tengo que consumirlo
  return read_stdin(fd, buf, count);				// El buffer esta vacio, puedo leer de pantalla
}

