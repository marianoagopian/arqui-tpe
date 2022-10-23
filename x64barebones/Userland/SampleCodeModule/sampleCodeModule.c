/* sampleCodeModule.c */
#include <stdint.h>
#include <color.h>
#include <syscalls.h>
#include <functions.h>

uint32_t width, height;

#define BUFFER_LENGTH 32

static char * newLine = "$>:";

int main() {
	clearscreen();	

	print("Welcome to Shell! Type \"HELP\" for a list of commands.\n\n", 55);
	while(1) {
		print(newLine, strlen(newLine));
		char readBuffer[BUFFER_LENGTH] = {0};
		scanf(readBuffer, BUFFER_LENGTH);
		// getChar();
	}
}