#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "map.h"

char ui_wall[3][5] = {
  {"...."},
  {"...."},
  {"...."}
};

char ui_ghost[3][5] = {
  {".--."},
  {"|''|"},
  {"'~~'"}
};

char ui_hero[3][5] = {
  {".--."},
  {"| < "},
  {"'--'"}
};

char ui_bomb[3][5] = {
  {" \\|/"},
  {" -o-"},
  {" /|\\"}
};

char ui_food[3][5] = {
  {"    "},
  {"  o "},
  {"    "}
};

char ui_empty[3][5] = {
  {"    "},
  {"    "},
  {"    "}
};

void print_map(MAP *m)
{
  for (int i = 0; i < m->rows; i++) {

    for (int ui_row = 0; ui_row < 3; ui_row++) {

      for (int j = 0; j < m->cols; j++) {

        switch (m->matrix[i][j]) {
          case FOOD:
            printw("%s", ui_food[ui_row]);
            break;

          case EMPTY:
            printw("%s", ui_empty[ui_row]);
            break;

          case VERTICAL_WALL:
          case HORIZONTAL_WALL:
          case CORNER_WALL:
            printw("%s", ui_wall[ui_row]);
            break;

          case GHOST:
            printw("%s", ui_ghost[ui_row]);
            break;

          case HERO:
            printw("%s", ui_hero[ui_row]);
            break;

          case BOMB:
            printw("%s", ui_bomb[ui_row]);
            break;
        }
      }

      printw("\n");
    }
  }
}
