#include <commands.h>
#include <syscalls.h>

void increaseFontSize() {
  if(sys_get_level() == 2) {
    printf("El tamaño es el mas grande posible\n"); //Hicimos hasta dos porque 3 nos parecía muy grande
    return;
  }
  sys_set_level(2);
}

void decreaseFontSize() {
  if(sys_get_level() == 1) {
    printf("El tamaño es el mas chico posible\n");
    return;
  }
  sys_set_level(1);
}