#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <time.h>
#include "pacman.h"
#include "map.h"

MAP m;
POSITION pos;

int new_pos(int x, int y,
    int *x_dest, int *y_dest) {

  int options[4][2] = {
    { x, y+1 },
    { x, y-1 },
    { x+1, y },
    { x-1, y }
  };

  srand(time(0));
  for (int i = 0; i < 10; i++) {
    int random = rand() % 4;
    int new_x = options[random][0];
    int new_y = options[random][1];
    
    if (valid_pos(&m, new_x, new_y, GHOST)) {
      *x_dest = new_x;
      *y_dest = new_y;
      return 1;
    }
  }
  
  return 0;
}

void ghosts() {
  MAP m_copy;
//  memset(&m_copy, 0, sizeof(MAP));
//  memcpy(&m_copy, &m, sizeof(MAP));

  copy_map(&m_copy, &m);

  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.cols; j++) {

      if (m_copy.matrix[i][j] == GHOST) {
        int x_dest, y_dest;
        int can_move = new_pos(i, j, &x_dest, &y_dest);

        if (can_move) {
          change_pos(&m, i, j, x_dest, y_dest, GHOST);
        }
      }
    }
  }

  free_map(&m_copy);
}

int game_over() {
  POSITION pos;
  int is_alive = get_position(&m, &pos, HERO);
  return !is_alive;
}

void move() {
  char direction;
  scanf(" %c", &direction);

  int new_x = pos.x;
  int new_y = pos.y;

  switch (direction) {
    case LEFT:
    case LEFT_VIM:
      new_y--;
      break;
    case RIGHT:
    case RIGHT_VIM:
      new_y++;
      break;
    case UP:
    case UP_VIM:
      new_x--;
      break;
    case DOWN:
    case DOWN_VIM:
      new_x++;
      break;
    default:
      return;
  }

  if (!valid_pos(&m, new_x, new_y, HERO))
    return;

  change_pos(&m, pos.x, pos.y, new_x, new_y, HERO);
  pos.x = new_x;
  pos.y = new_y;
}


int main () {
  read_map(&m);
  get_position(&m, &pos, HERO);

  do {
    print_map(&m);
    move();
    ghosts();
  } while (!game_over());

  print_map(&m);
  free_map(&m);
}
