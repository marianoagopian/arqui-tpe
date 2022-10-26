#include <commands.h>
#include <functions.h>
#include <syscalls.h>


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