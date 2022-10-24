#include <keyboard.h>
#include <stdint.h>
#include <video.h>
#include <interrupts.h>
#include <lib.h>

static const uint8_t scanCodeTable[256] = {
    0,    0,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  '9',   '0',   '-',  '=',    '\b',
    '    ', 'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',   'O',  'P',  '[',   ']',  '\n',
    0,     'A',  'S', 'D',  'F',  'G',  'H',  'J',  'K',  'L',  ';',  '\'',
    0,    0,  '\\',   'Z',  'X',     'C', 'V', 'B',  'N',  'M',  ',',  '.',  '/',    0,
    '*',     0,  ' ',    0,     0,     0,    0,       0,         0,
};

extern char getKey();		// en libasm.asm

/*-------- CONSTANTS --------*/
#define BUFFER_SIZE 200

/*--------- MACROS ----------*/
#define INCREASE_MOD(x,total)	(x) = ((x) + 1) % total;
#define DECREASE_MOD(x, total) 	x--;\
				if((x)<0)\
    					x=((total) + (x)) % (total);\
				else\
   					x = (x) % (total);

/*-------- STATIC FILE VARIABLES --------*/
static char keyBuffer[BUFFER_SIZE];             // Buffer de caracters de teclado
static int writePos;				// Posicion a escribir en el buffer
static int readPos;				// Posicion a consumir en el buffer
static int peekPos;			        // Posicion para observar en el buffer

void  keyboard_handler(uint64_t * regDumpPos) {

	int c = getKey();
    
	// if(c == F5_SCAN_CODE)
	// 	saveInfoReg(regDumpPos);	// caso: aprienta boton de captura de registros

	/*if(c<0 || c>=128)			// caso: codigo invalido 
		return NO_KEY;
	
	if(keyBuffer[writePos]!=0)		// caso: no hay espacio en el buffer
		return BUFFER_FULL;		
			
	c = scanCodeTable[c];			// convierto a ascii
    //scr_printChar(c);
	// ------ Caracteres especiales ------
	if(c=='\b'){
		DECREASE_MOD(writePos,BUFFER_SIZE)

		if(keyBuffer[writePos]!=0){
			keyBuffer[writePos] = 0; 			// elimino del buffer
			if(writePos + 1 == peekPos)			// me muevo para atras en el peek 
				DECREASE_MOD(peekPos, BUFFER_SIZE)
		}
		else
			INCREASE_MOD(writePos,BUFFER_SIZE)		// no habia nada en el buffer, vuelvo adonde estaba
		return DELETE_KEY;
	}

	// ------ Caracteres normales -------
	if(c != UNMAPPED){
		keyBuffer[writePos] = c;					// se agraga al buffer
		INCREASE_MOD(writePos,BUFFER_SIZE)

		return VALID_KEY;
	}*/
	if(writePos < BUFFER_SIZE)
		keyBuffer[writePos++]=c;
}

/* Consumo letra del buffer y sobreescribe con 0 para denotar una posicion vacia. */
char get_key()
{
	if(!checkIfAvailableKey())
		return 0;

	if(peekPos == readPos)          	// para que el peek no quede apuntando a nada
		INCREASE_MOD(peekPos,BUFFER_SIZE)	

	char c = keyBuffer[readPos];		// consumo letra 
	keyBuffer[readPos] = 0;

	INCREASE_MOD(readPos,BUFFER_SIZE)
	
	return c;
}


/* Como el get_key pero no lo consumo, es decir, no pone en 0 sino que lo deja. */
char peek_key()
{
	if(keyBuffer[peekPos]==0)		// corto sin aumentar
		return 0;

	char c = keyBuffer[peekPos];
	INCREASE_MOD(peekPos,BUFFER_SIZE)	
	return c;
}


unsigned int consume_kb_buffer(char * buf, unsigned int count) 
{
	int i=0;
	
	while(checkIfAvailableKey() && i<count) {
		char c = get_key();
		buf[i++] = c;
	}
	return i;
}


char checkIfAvailableKey() {
	return keyBuffer[readPos] != 0;
}

unsigned int kbd_readCharacters(char* buf, unsigned int n) {
    _cli();
    unsigned int charsRead = 0;
    unsigned int scancodeIndex;
    for (scancodeIndex = 0; scancodeIndex < writePos && charsRead < n; scancodeIndex++) {
        //int8_t sc = keyBuffer[scancodeIndex];
        char c = keyBuffer[scancodeIndex];
        if (c>0 && c<128)
            buf[charsRead++] = scanCodeTable[c];
    }

    writePos -= scancodeIndex;
    memcpy(keyBuffer, keyBuffer + scancodeIndex, writePos);
    _sti();
    return charsRead;
}