#include <commands.h>
#include <syscalls.h>
#include <functions.h>

void increaseFontSize() {
  if(sys_get_level() == 2) {
    printf("There is no bigger font size available\n"); //Hicimos hasta dos porque 3 nos parecía muy grande
    return;
  }
  sys_set_level(2);
}

void decreaseFontSize() {
  if(sys_get_level() == 1) {
    printf("There is no smaller font size available\n");
    return;
  }
  sys_set_level(1);
}