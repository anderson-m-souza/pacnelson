#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "pacnelson.h"
#include "map.h"
#include "ui.h"

MAP m;
MAP m_food;
POSITION pos;
int has_bomb = 0;
int remaining_food;
int game_over = 0;
char direction = 'd';

void ncurses_init()
{
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  cbreak();
  timeout(350);
}

void exec_commands()
{
  char command;
  command = getch();

  if (has_bomb && command == EXPLODE) {
    explode();
    has_bomb = 0;
    command = direction;
  }

  if (command == -1) {
    command = direction;
  }

  move_hero(command);
}

void explode()
{
  int radius = 3;

  explode_helper(pos.x, pos.y,  0,  1, radius);
  explode_helper(pos.x, pos.y,  0, -1, radius);
  explode_helper(pos.x, pos.y,  1,  0, radius);
  explode_helper(pos.x, pos.y, -1,  0, radius);
}

void explode_helper(int x, int y,
                    int x_sum, int y_sum, int radius)
{
  int new_x = x + x_sum;
  int new_y = y + y_sum;

  if (radius == 0
      || is_wall(&m, new_x, new_y)) {

    return;
  }
  
  m.matrix[new_x][new_y] = m_food.matrix[new_x][new_y];
  explode_helper(new_x, new_y, x_sum, y_sum, radius - 1);
}

void move_hero(char command)
{
  int new_x = pos.x;
  int new_y = pos.y;

  switch (command) {
    case LEFT:
    case LEFT_VIM:
      new_y--;
      direction = LEFT;
      break;

    case RIGHT:
    case RIGHT_VIM:
      new_y++;
      direction = RIGHT;
      break;

    case UP:
    case UP_VIM:
      new_x--;
      direction = UP;
      break;

    case DOWN:
    case DOWN_VIM:
      new_x++;
      direction = DOWN;
      break;

    default:
      return;
  }

  if (!valid_pos(&m, new_x, new_y, HERO)) {
    return;
  }

  if (is_item(&m, new_x, new_y, GHOST)) {
    game_over = 1;
    return;
  }

  if (is_item(&m, new_x, new_y, BOMB)) {
    has_bomb = 1;
  }

  if (is_item(&m_food, new_x, new_y, FOOD)) {
    remaining_food--;
  }

  change_pos(&m, &m_food, pos.x, pos.y, new_x, new_y, HERO);
  pos.x = new_x;
  pos.y = new_y;
}

void ghosts()
{
  MAP m_copy;
  copy_map(&m_copy, &m);

  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.cols; j++) {

      if (m_copy.matrix[i][j] == GHOST) {
        int x_dest, y_dest;
        int can_move = new_ghost_pos(&m, i, j, &x_dest, &y_dest);

        if (can_move) {
          change_pos(&m, &m_food, i, j, x_dest, y_dest, GHOST);
        }
      }
    }
  }

  free_map(&m_copy);
}

void check_game_over()
{
  POSITION pos;

  int is_alive = get_position(&m, &pos, HERO);

  game_over = !is_alive || won();
}

int won()
{
  return remaining_food == 0;
}

void ncurses_update()
{
  refresh();
  move(0, 0);
}

void ncurses_end()
{
  refresh();
  timeout(2000);
  getch();
  endwin();
}

int main()
{
  read_map(&m, 1);
  read_map(&m_food, 0);
  count_food(m_food, &remaining_food);
  get_position(&m, &pos, HERO);
  ncurses_init();

  do {
    print_map(&m);
    exec_commands();

    if (!game_over) {
      ghosts();
      check_game_over();
    }

    ncurses_update();

  } while (!game_over);

  print_map(&m);
  free_map(&m);
  ncurses_end();

  return 0;
}
