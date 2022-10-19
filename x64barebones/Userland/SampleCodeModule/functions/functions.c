#include "../include/functions.h"

#define RTC 1
#define SYS_WRITE 2
#define SYS_READ 3

void print(char * string, int length) {
    sys_write(string, length);
}

void putchar(char c){
    print(&c,1);
}

// void clear_screen(){
//     sys_clear_screen();
// }

void puts(char * string) {
    print(string, strlen(string));
    print("\n",1);
}

void read_line(char * buf, int length) {
    sys_read(buf, length);
}

// unsigned int consume_buffer(char * buffer, int length){
//     return sys_consume_stdin(buffer, length);
// }

char getchar() {
    char c;
    read_line(&c, 1);

    return c;
}

int strlen(const char * string){
    int i = 0;
    while(string[i])
        i++;

    return i;
}




