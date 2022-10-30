#include "./include/syscalls.h"
#include <color.h>
#include <functions.h>
#include <stdarg.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define REGISTERS 15
#define REGISTER_LENGTH 16
#define BUFF_SIZE 20

static const uint8_t scanCodeTable[256] = {
  0,    0,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  '9',   '0',   '-',  '=',    '\b',
  '\t', 'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',   'o',  'p',  '[',   ']',  '\n',
  0,     'a',  's', 'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  '\'',
  0,    0,  '\\',   'z',  'x',     'c', 'v', 'b',  'n',  'm',  ',',  '.',  '/',    0,
  '*',     0,  ' ',    0,     0,     0,    0,       0,         0,
};

void putchar(char c) {
    print(&c, 1);
}

void print(const char* buf, uint64_t count) {
    sys_write(STDOUT, buf, count);
}

void clearScreen() {
    sys_clear_screen();
}

char getChar() {
	char c;

  while (sys_read(STDIN, &c, 1) == 0){
      ;
  }
	return c;
}

void scanf(char* readbuf, uint64_t maxlen) {
    if (maxlen == 0)
        return;

    // We read up to maxlen-1 characters from the input.
    uint64_t count = 0;
    do {
        char c = getChar();

        if (c == '\n') { // If a '\n' is found, we zero-terminate the string and return.
            readbuf[MIN(count, maxlen-1)] = '\0';
            print(&c, 1);
            return;
        } 
        if (c == '\b'){
            if (count != 0){
                count--;
            }
            print(&c, 1);
        }
         else {
            //We add the read character to the buffer and continue.
	        print(&c, 1);
            if (count < maxlen-1 && c != 0) {
                readbuf[count] = c;
                count++;
            }
        }
    } while (1);
}

int strlen(const char * str) {
	int ans = 0;
	for (int i = 0; str[i] != 0; i++) {
		ans++;
	}
    return ans;
}

int strcmp(const char* s1, const char* s2) {
    while(*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void reverseString(char * string, int length) {
    char aux;
    for(int i = 0, j = length - 1; i < j ; i++, j--) {
        aux = string[i];
        string[i] = string[j];
        string[j] = aux;
    }
}

int intToString(int num, char *buffer) {
    if(num==0) {
        buffer[0] = '0';
        buffer[1] = 0;
        return 2;
    }
    int i = 0;
    while(num > 0) {
        buffer[i++] = num % 10 + '0';
        num /= 10;
    }
    reverseString(buffer, i);
    buffer[i] = 0;
    return i;
}

int hexToString(uint64_t num, char * buffer, int fixedLength) {
    int i = 0;

    for(int aux ; num > 0 ; i++, num/=16){
        aux = num % 16;
        if(aux >=0 && aux < 10)                     // convierto a hex
            buffer[i] = aux + '0';
        else
            buffer[i] = aux - 10 + 'A';

    }
    while(i<fixedLength) {                   // le agrego 0 por deltante para llegar a la longitud deseada
        buffer[i++] = '0';
    }
    reverseString(buffer,i);
    buffer[i] = 0;

    return i;
}

void printf(char *fmt,...){
    va_list ap; 
    char *p, *sval;
    int ival;
    //double dval;

    va_start(ap, fmt);
    char *aux = {0};
    int len = 0;
    for(p = fmt; *p; p++) {
        if(*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                //*aux = {0};
                len = intToString(ival, aux);
                print(aux,len);
                break;
            case 'x':
                ival  = va_arg(ap, int);
                //*aux = {0};
                len = hexToString(ival, aux, 16);
                print(aux,len);
                break;
            case 's':
                for(sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap); 
}
