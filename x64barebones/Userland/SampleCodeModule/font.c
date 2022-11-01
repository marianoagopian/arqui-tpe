#include <commands.h>
#include <syscalls.h>
#include <functions.h>

static char * noArgument = "For this function argument is necessary\n";


int my_getnbr(char *str){
  int result;
  int puiss;

  result = 0;
  puiss = 1;
  while (('-' == (*str)) || ((*str) == '+'))
  {
      if (*str == '-')
        puiss = puiss * -1;
      str++;
  }
  while ((*str >= '0') && (*str <= '9'))
  {
      result = (result * 10) + ((*str) - '0');
      str++;
  }
  return (result * puiss);
}

void changefontsize(char *par){
  if(*par == 0) {
    print(noArgument, strlen(noArgument));
    return;
  }
  int level = my_getnbr(par);
  if(level < 1 || level > 3){
    printf("The parameter must be a number between 1 and 3\n");
    return;
  }
  if(level == sys_get_level()){
    printf("Enter a different font size number to change from the current one\n");
    return;
  }
  sys_set_level(level);
}
