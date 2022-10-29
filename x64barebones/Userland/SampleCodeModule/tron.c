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

static char positions[192][256] = {{0}};

void setInitialPositions(int * x1, int * y1, int * x2, int * y2, int * playerOneDirection, int * playerTwoDirection);
void parsePositions(char scancode, int * playerOneDirection, int * playerTwoDirection);
void setNewDirection(int * currentPosition, int newPosition);
void moveCharacter(int currentPosition, int * x, int * y);

void tron() {
    clearScreen();
    sys_clear_buffer();
    int i, j;
    int playerOneDirection = RIGHT;
    int playerTwoDirection = LEFT;
    int x1 = WIDTH/4, x2 = (WIDTH*3)/4;
    int y1 = HEIGHT/2, y2 = HEIGHT/2;
    char isPlaying = 1;
    char newDirection = 0;
    while (isPlaying){
      newDirection = sys_check_buffer();
      printf("%d", newDirection);
      parsePositions(newDirection, &playerOneDirection, &playerTwoDirection);

      for(int z=0;z<10000000;z++){
          ;
      }

      positions[y1/4][x1/4] = 1;
      positions[y2/4][x2/4] = 1;

      for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
          sys_draw_point(x1, y1, magenta);
          sys_draw_point(x2, y2, yellow);
          moveCharacter(playerOneDirection, &x1, &y1);
          moveCharacter(playerTwoDirection, &x2, &y2);
        }
        if(positions[y1/4][x1/4] == 1 || positions[y2/4][x2/4] == 1) {
          i = 4;
          j = 4;
        }
      }

      while((positions[y1/4][x1/4] == 1 && positions[y2/4][x2/4] == 1) && isPlaying) {
        isPlaying = 0;
          // if(sysCheckBuffer() != 0) {
          // }
      }
    }
    sys_clear_buffer();
    // reiniciateVariables();
    clearScreen();
}


// ! 0 < x1 < WIDTH || !(0 < x2 < WIDTH) || !(0 < y1 < HEIGHT) || !(0 < y2 < HEIGHT) || 

// Otra función auxiliar que se encarge de asignar para donde se mueve

// void reiniciateVariables() {

// }

void parsePositions(char scancode, int * playerOneDirection, int * playerTwoDirection) {
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

void setNewDirection(int * currentDirection, int newDirection) {
  if(*currentDirection + newDirection == 0) { //Es para que cuando va a la dirección contraria no haga nada
      return;
  }
  *currentDirection = newDirection;
}

void moveCharacter(int currentDirection, int * x, int * y) {
    if (currentDirection == RIGHT) {
        *x += 1;
    } else if (currentDirection == LEFT) {
        *x -= 1;
    } else if (currentDirection == DOWN) {
        *y += 1;
    } else {
        *y -= 1;
    }
}
