#include <commands.h>
#include <functions.h>

const char* helpString = 
  "clear                  Clears screen's content\n"
  "decreasefontsize				Reduces the font size.\n"
	"divbyzero					    Simulates the error that occurs when dividing by zero.\n"
	"help							      Prints all commands and their description.\n"
	"increasefontsize				Reduces the font size.\n"
	"inforeg						    Prints the value of the registers when screenshotted. Use ; or ñ to screenshot\n"
	"invalidopcode		      Simulates the error that occurs when using an invalid operation code.\n"
  "printmem						    Given an address pointer prints the following 32 bytes.\n"
	"time							      Prints the current time.\n"
	"tronlightcycle					Executes the game tron light cycle. It requires two players, one will move with the arrow-keys and the other with the keys W A S D.\n";

void help() {
	print(helpString, strlen(helpString));
}