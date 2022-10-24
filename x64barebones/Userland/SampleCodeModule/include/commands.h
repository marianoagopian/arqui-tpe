#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#define COMMANDS_QTY 9
#define PARAMETER_LENGTH 10
#define BUFFER_LENGTH 32

#define INVALID_COMMAND_MSG "-Invalid command. Check available commands with help.\n"

void checkCommand(char command[BUFFER_LENGTH], char parameter[PARAMETER_LENGTH], char readbuf[BUFFER_LENGTH]);
void callFunction(char * command, char * parameter);

void help();

#endif
