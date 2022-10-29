#include <commands.h>
#include <functions.h>
#include <syscalls.h>
#include <color.h>

#define LEFT -1
#define UP -2
#define RIGHT 1
#define DOWN 2
#define HEIGHT 768
#define WIDTH 1024

void setInitialPositions(int * x1, int * y1, int * x2, int * y2, int * playerOneDirection, int * playerTwoDirection);
void parsePositions(int scancode, int * playerOneDirection, int * playerTwoDirection);
void setNewDirection(int * currentPosition, int newPosition);
void moveCharacter(int currentPosition, int * x, int * y);

void tron(){
    clearScreen();
    // sysClearBuffer();
    /*for(int i = 0; i < 50;i++)
        for(int j = 0; j < 50;j++)
            sys_draw_point(i,j,magenta);*/
    int positions[192][256] = {{0}}; // Hago una matriz y la lleno de cero para despues y fijandome donde estuvieron los jugadores. Hago de esas dimensiones porque son las dimensiones de la pantalla dividida 4
    int x1, y1, x2, y2; //Para ir fijandome las current positions de cada jugador
    int playerOneDirection;
    int playerTwoDirection;
    int i, j;
    setInitialPositions(&x1, &y1, &x2, &y2, &playerOneDirection, &playerTwoDirection);
    positions[y1/4][x1/4] = 1;
    positions[y2/4][x2/4] = 1;
    char isPlaying = 1;
    int newDirection;
    while (isPlaying){
      // newDirection = sysCheckBuffer();
      // parsePositions(newDirection &playerOneDirection, &playerTwoDirection);
      // moveCharacter(playerOneDirection, &x1, &y1);
      // moveCharacter(playerTwoDirection, &x2, &y2);


      for(i = 0; i < 4; i++) {
        for(j = 0; j < 4 ; j++) {
          sys_draw_point(x1, y1, magenta);
          sys_draw_point(x2, y2, yellow);
        }
      }

      // for(int z=0;z<20000000;z++){
      //     ;
      // }
      // i2 = i + 4;
      // for(;i < i2;i++){
      //     for(int j = 10; j < 14; j++){
      //         sys_draw_point(i, j, magenta);

      //     }
      // }
    }
    
    // sysClearBuffer();
    clearScreen();
}

void setInitialPositions(int * x1, int * y1, int * x2, int * y2, int * playerOneDirection, int * playerTwoDirection) {
  *y1 = HEIGHT/2;
  *y2 = HEIGHT/2;

  *x1 = WIDTH/4;
  *x2 = (WIDTH * 3)/4;

  *playerOneDirection = RIGHT;
  *playerTwoDirection = LEFT;
}

// Otra función auxiliar que se encarge de asignar para donde se mueve

void parsePositions(int scancode, int * playerOneDirection, int * playerTwoDirection) {
  switch (scancode) {
    case 0x11:
      setNewDirection(playerOneDirection, UP);
      break;
    case 0x1E:
      setNewDirection(playerOneDirection, LEFT);
      break;
    case 0x1F:
      setNewDirection(playerOneDirection, DOWN);
      break;
    case 0x20:
      setNewDirection(playerOneDirection, RIGHT);
      break;
    case 0x48:
      setNewDirection(playerTwoDirection, UP);
      break;
    case 0x4B:
      setNewDirection(playerTwoDirection, LEFT);
      break;
    case 0x50:
      setNewDirection(playerTwoDirection, DOWN);
      break;
    case 0x4D:
      setNewDirection(playerTwoDirection, RIGHT);
      break;
    default:
      break;
  }
}

void setNewDirection(int * currentPosition, int newPosition) {
  if(*currentPosition + newPosition == 0) { //Es para que cuando va a la dirección contraria no haga nada
      return;
  }
  *currentPosition = newPosition;
}

void moveCharacter(int currentPosition, int * x, int * y) {
    if (currentPosition == RIGHT) {
        *x += 1;
    } else if (currentPosition == LEFT) {
        *x -= 1;
    } else if (currentPosition == DOWN) {
        *y += 1;
    } else {
        *y -= 1;
    }
}
