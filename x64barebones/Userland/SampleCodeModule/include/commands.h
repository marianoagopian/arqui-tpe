#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#define COMMANDS_QTY 9
#define PARAMETER_LENGTH 10
#define BUFFER_LENGTH 32

#define INVALID_COMMAND_MSG "-Invalid command. Check available commands with help.\n"

#define HELP_MSG "\
	decreasefontsize				Reduces the font size\n\
	divbyzero								    Simulates the error that occurs when dividing by zero\n\
	help										        Prints all commands and their description\n\\
	increasefontsize				Reduces the font size\n\
	inforeg									Prints the value of the registers\n\
	invalidopcode						Simulates the error that occurs when using an invalid operation code\n\
	printmem								Given an address pointer prints the following 32 bytes\n\
	time										Prints the current time\n\
	tronlightcycle					Executes the game tron light cycle. It requires two players, one will move with the arrow-keys and the other with the keys W A S D\n\
	"

void checkCommand(char command[BUFFER_LENGTH], char parameter[PARAMETER_LENGTH], char readbuf[BUFFER_LENGTH]);
void callFunction(char * command, char * parameter);

#endif
