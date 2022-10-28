#include <commands.h>
#include <functions.h>
#include <syscalls.h>
#include <color.h>

#define LEFT -1
#define UP -2
#define RIGHT 1
#define DOWN 2

static int playerOneDirection = RIGHT;
static int playerTwoDirection = LEFT;

void tronLightCycle(){
    clearscreen();
    /*for(int i = 0; i < 50;i++)
        for(int j = 0; j < 50;j++)
            sys_draw_point(i,j,magenta);*/
    int height = 768, width = 1024;
    char c;
    int i=0;
    int i2 = 5;
    int time = 0;
    char *aux={0};
    while (1){

        for(int z=0;z<20000000;z++){
            ;
        }
        i2= i + 5;
        for(;i < i2;i++){
            for(int j = 10; j < 14; j++){
                sys_draw_point(i, j, magenta);
            }    
        }
    }
    
    clearscreen();
}

/*
    hace función auxiliar y llamarla con la posición y que esta se encargue de restar.

if(int currentPosition, int * x, int * y) {
    if (currentPosition == RIGHT) {
        *x += 1;
    } else if (currentPosition == LEFT) {
        *x -= 1;
    } else if (currentPosition === DOWN) {
        *y += 1;
    } else {
        *y -= 1;
    }
}

Otra función auxiliar que se encarge de asignar para donde se mueve
void setNewDirection(int * currentPosition, int newPosition) {
    if(*currentPosition + newPosition == 0) { //Es para que cuando va a la dirección contraria no haga nada
        return;
    }
    *currentPosition = newPosition;
    } 
}