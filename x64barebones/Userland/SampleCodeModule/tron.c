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

static char positions[HEIGHT/4][WIDTH/4] = {{0}};

void setInitialPositions(int * x1, int * y1, int * x2, int * y2, int * playerOneDirection, int * playerTwoDirection);
void parsePositions(char scancode, int * playerOneDirection, int * playerTwoDirection);
void setNewDirection(int * currentPosition, int newPosition);
void moveCharacter(int currentPosition, int * x, int * y);
void resetPositionsArray();

void tron() {
  clearScreen();

  printf("Bienvenido al Tron! El jugador 1 (color magenta) usara las teclas WASD para moverse y el jugador 2 (color amarillo) usara las flechas del teclado\n\n\n");

  printf("Toque la letra 'p' para comenzar\n");

  while(getChar() != 'p') {
    printf("Toque la letra 'p' para comenzar\n");
  }

  clearScreen();
  sys_clear_buffer();

  int playerOneDirection = RIGHT;
  int playerTwoDirection = LEFT;
  int x1 = WIDTH/4, x2 = (WIDTH*3)/4;
  int y1 = HEIGHT/2, y2 = HEIGHT/2;
  char isPlaying = 1;
  char newDirection = 0;
  int won;

  while (isPlaying){
    newDirection = sys_check_buffer();
    parsePositions(newDirection, &playerOneDirection, &playerTwoDirection);

    sys_holder(1);

    positions[y1/4][x1/4] = 1;
    positions[y2/4][x2/4] = 1;

    sys_draw_rect(x1,y1,4,4,magenta);
    sys_draw_rect(x2,y2,4,4,yellow);
    moveCharacter(playerOneDirection, &x1, &y1);
    moveCharacter(playerTwoDirection, &x2, &y2);

    if(positions[y1/4][x1/4] == 1 || x1 <= 0 || x1 >= WIDTH || y1 <= 0 || y1 >= HEIGHT) {
      won = 2;
      isPlaying = 0;
    }

    if(positions[y2/4][x2/4] == 1 || x2 <= 0 || x2 >= WIDTH || y2 <= 0 || y2 >= HEIGHT) {
      if(positions[y1/4][x1/4] == 1) {
        won = 0;
      } else {
        won = 1;
      }
      isPlaying = 0;
    }
  }
  clearScreen();

  if(won == 0) {
    printf("Han perdido ambos jugadores, toque la tecla 'c' para continuar\n");
  } else {
    printf("Ha ganado el jugador %d, toque la tecla 'c' para continuar\n", won);
  }

  while(getChar() != 'c') {
    ;
  }


  sys_clear_buffer();
  resetPositionsArray();
  clearScreen();
}

void resetPositionsArray() {
  for(int i = 0 ; i < HEIGHT/4 ; i++) {
    for(int j = 0; j < WIDTH/4 ; j++) {
      positions[i][j] = 0;
    }
  }
}

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
        *x += 4;
    } else if (currentDirection == LEFT) {
        *x -= 4;
    } else if (currentDirection == DOWN) {
        *y += 4;
    } else {
        *y -= 4;
    }
}
