#include <commands.h>
#include <functions.h>
#include <syscalls.h>

void reverseString(char * string, int length);

int intToString(int num, char *buffer);

void timer(){
    int aux = sys_time();
    if(aux < 3600 * 3) {
        aux += 3600 * 21;
    } else {
        aux -= 3600 * 3;
    }
    int hours = aux / 3600;
    char hoursStr[3] = {0};
    int hoursLength = intToString(hours, hoursStr);
    int minutes = (aux - hours * 3600) / 60;
    char minStr[3] = {0};
    int minutesLength = intToString(minutes, minStr);
    int seconds = aux % 60;
    char secondsStr[3] = {0};
    int secondsLen = intToString(seconds, secondsStr);
    print(hoursStr, hoursLength);
    print(":", 1);
    print(minStr, minutesLength);
    print(":", 1);
    print(secondsStr, secondsLen);
    print("\n", 2);
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