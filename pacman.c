#include <stdio.h>
#include <stdlib.h>
#include "pacman.h"
#include "map.h"

MAP m;
POSITION pos;
int has_bomb = 0;

void ghosts() {
  MAP m_copy;

  copy_map(&m_copy, &m);

  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.cols; j++) {

      if (m_copy.matrix[i][j] == GHOST) {
        int x_dest, y_dest;
        int can_move = new_pos(&m, i, j, &x_dest, &y_dest);

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

void move(char command) {
  int new_x = pos.x;
  int new_y = pos.y;

  switch (command) {
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

  if (!valid_pos(&m, new_x, new_y, HERO)) {
    return;
  }

  if (is_item(&m, new_x, new_y, BOMB)) {
    has_bomb = 1;
  }

  change_pos(&m, pos.x, pos.y, new_x, new_y, HERO);
  pos.x = new_x;
  pos.y = new_y;
}

void explode() {
  int radius = 3;
  explode_helper(pos.x, pos.y,  0,  1, radius);
  explode_helper(pos.x, pos.y,  0, -1, radius);
  explode_helper(pos.x, pos.y,  1,  0, radius);
  explode_helper(pos.x, pos.y, -1,  0, radius);
}

void explode_helper(int x, int y,
    int x_sum, int y_sum, int radius) {
  int new_x = x + x_sum;
  int new_y = y + y_sum;

  if (radius == 0
      || is_wall(&m, new_x, new_y)) {
    return;
  }

  m.matrix[new_x][new_y] = EMPTY;
  explode_helper(new_x, new_y, x_sum, y_sum, radius - 1);
}

int main() {
  read_map(&m);
  get_position(&m, &pos, HERO);

  do {
    print_map(&m);
    printf("has_bomb == %d\n", has_bomb);

    char command;
    scanf(" %c", &command);
    if (has_bomb && command == EXPLODE) {
      explode();
      has_bomb = 0;
    } else {
      move(command);
    }

    ghosts();
  } while (!game_over());

  print_map(&m);
  free_map(&m);
}
