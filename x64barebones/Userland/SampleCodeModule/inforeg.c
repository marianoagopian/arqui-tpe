#include <stdint.h>
#include <functions.h>
#include <syscalls.h>

#define REGISTERS 15
#define REGISTER_LENGTH 16
#define BUFF_SIZE 20

static char * registerOrder[] = {
    "RAX: ","RBX: ","RCX: ","RDX: ",
    "RBP: ","RSI: ","RDI: ","R8: ", 
    "R9: ","R10: ","R11: ","R12: ",
    "R13: ","R14: ","R15: "
};

static void reverseString(char * string, int length) {
    char aux;
    for(int i = 0, j = length - 1; i < j ; i++, j--) {
        aux = string[i];
        string[i] = string[j];
        string[j] = aux;
    }
}

static int hexToString(uint64_t num, char * buffer, int fixedLength) {
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

void infoReg() {
    char stringBuffer[BUFF_SIZE];
    uint64_t regBuffer[REGISTERS];

    sys_info_reg(regBuffer);
    for(int i = 0 ; i < REGISTERS ; i++) {
        hexToString(regBuffer[i], stringBuffer, REGISTER_LENGTH);
        print(registerOrder[i], strlen(registerOrder[i]));
        print(stringBuffer, BUFF_SIZE);
        print("\n", 2);
    }
}
