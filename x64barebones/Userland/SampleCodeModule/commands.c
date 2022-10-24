#include <commands.h>
#include <functions.h>

static const char* commands[COMMANDS_QTY] = {"DECRASEFONTSIZE", "DIVBYZERO", "HELP", "INCREASEFONTSIZE", "INFOREG",  "INVALIDOPERATIONCODE", "PRINTMEM",  "TIME", "TRONLIGHTCYCLE"};

void checkCommand(char command[BUFFER_LENGTH], char parameter[PARAMETER_LENGTH], char readbuf[BUFFER_LENGTH]) {
	int i, j;
	
	for(i=0, j=0; i<BUFFER_LENGTH && readbuf[i] != ' '; i++){
			command[j++] = readbuf[i];
	}

	command[j] = 0;

	while(i < BUFFER_LENGTH && readbuf[i] == ' '){ // Elimino el/los espacios entre el comando llamado y el parametro
		i++;
	}

	for(j = 0; i < BUFFER_LENGTH && readbuf[i] != ' ' ; ) {
		if(j >= PARAMETER_LENGTH) {
			return;
		}
		parameter[j++] = readbuf[i++];
	}
	parameter[j] = 0;
}

static void invalidCommand() {
	print(INVALID_COMMAND_MSG, strlen(INVALID_COMMAND_MSG));
}

static void help() {
	print(HELP_MSG, strlen(HELP_MSG));
}

void callFunction(char * command, char * parameter) {
	int functionIndex = -1;
	int i;
	for(i = 0; i < COMMANDS_QTY && functionIndex == -1; i++) {
		if(strcmp(command, commands[i]) == 0) {
			functionIndex = i;
		}
	}
	switch (functionIndex) {
	// case 0:
	// 	decreaseFontSize();
	// 	break;
	// case 1:
	// 	divByZero();
	// 	break;
	case 2:
		help();
		break;
	// case 3:
	// 	increaseFontSize();
	// 	break;
	// case 4:
	// 	inforeg();
	// 	break;
	// case 5:
	// 	invalidOperationCode();
	// 	break;
	// case 6:
	// 	printmem();
	// 	break;
	// case 7:
	// 	time();
	// 	break;
	// case 8:
	// 	tronLightCycle();
	// 	break;
	default:
		invalidCommand();
		break;
	}
}
