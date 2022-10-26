#include <functions.h>

static char * invalidArgument = "Invalid argument!\nArgument must be number!";
static char * invalidMemoryAddress = "Invalid memory address!";

static uint64_t atoi(const char * string);

#define BUFFER_LENGTH 150;

void printmem(char * arg) {
    if(!isNum(arg)) {                                            // recibe un string que puede o no ser un numero
        puts(invalidArgument, strlen(invalidArgument));
        return;
    }
    uint64_t position = atoi(arg);


    char buffer[BUFFER_LENGTH];

    if(sys_printmem(position, buffer) == INVALID_POS){
        print(invalidMemoryAddress, strlen(invalidMemoryAddress));
    }
    else
        puts(buffer);
}

static uint64_t atoi(const char * string) {
    uint64_t result = 0;

    for(int i = 0 ; string[i] ; i++)
        result = result*10 + string[i] - '0';

    return result;
}

