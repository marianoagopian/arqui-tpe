#include <keyboard.h>
#include <video.h>
#include <defs.h>
#include <syscalls.h>
#include <lib.h>

static uint8_t * videoPosition = (uint8_t*)0xB8000;

static unsigned int currentVideoPosition = START;


void deleteKey(unsigned int * offset, unsigned int start,  unsigned int length , unsigned int step) {
	if(*offset == start)			// si llegue al principio de la pantalla, no puedo ir para atras
		return;						

	if( ((*offset - 2) % SCREEN_WIDTH) < start || ((*offset - 2) % SCREEN_WIDTH) > start + length) // si estamos por fuera de los limites, entro devuelta pero una linea arriba
		*offset -= step;			
	
	*offset -= 2;					// voy uno para atras
	*(videoPosition + *offset) = ' ';	
}

/* Writes to given screen */
unsigned int write(const char * buf, char format, unsigned int count, 
	unsigned int * offset, unsigned int start,  unsigned int length , unsigned int step){
	int i;

	for(i=0; i<count; i++) {

		// if(*offset >= (SCREEN_HEIGHT-1) * SCREEN_WIDTH + length + start) {	// llego al final de pantalla, tengo que hacer scroll up
		// 	scrollUp(start, length, step);
		// 	*offset = (SCREEN_HEIGHT-1) * SCREEN_WIDTH + start;
		// }
		
		char c = buf[i];

		//------ CARACTERES EPECIALES ------	
		if(c == '\n') {		
			int aux = length - (*offset % length);			// avanzo a la proxima linea en pantalla
			*offset += aux + step;
		}
		else if(c == '\b')				
			deleteKey(offset, start, length, step);
		

		//------ CARACTERES NORMALES ------	
		else {	
			*(videoPosition + (*offset)++) = c;			// escribo letra y formato
			*(videoPosition + (*offset)++) = format;

			if(*offset % length  == 0)						// salto a new line si llego a fin 
        *offset += step;
		}

	}
	return i;
}

/* Decides how to proceed depending on screen to write */
unsigned int writeDispatcher(unsigned int fd, const char * buf, unsigned int count) {
	char format;

	if(fd % 2 != 0) { // notar que solo los pares son ERROR
		format = STDOUT_COLOR;
  } else  {
		format = STDERR_COLOR;
  }

  write(buf, format, count, &currentVideoPosition, START, LENGTH, 0);
  return 0;
}

unsigned int read_stdin(unsigned int fd, char * buf, unsigned int count) {
	char c = 0, keyboardResp = 0; 
	int i = 0;
	unsigned int initialPos = currentVideoPosition;

	while(c != '\n' && keyboardResp != BUFFER_FULL) {
		keyboardResp = keyboard_handler();

		if(keyboardResp == VALID_KEY) {
			c = peek_key();
			writeDispatcher(fd, &c, 1);
		
			if(i<count) 
				i++;
		}
		else if(keyboardResp == DELETE_KEY) {
			if(currentVideoPosition > initialPos) {  // no dejo que borre lo que ya habia
				writeDispatcher(fd,"\b",1);
				if(i > 0)
					i--;
			}
		}
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

void ncClear() {
	int i;

	for (i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++){
		videoPosition[i * 2] = ' ';
		videoPosition[(i * 2) + 1] = DEFAULT;
	}
	currentVideoPosition = START;
}