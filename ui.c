#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "map.h"

char ui_wall[4][7] = {
  {"......"},
  {"......"},
  {"......"},
  {"......"}
};

char ui_ghost[4][7] = {
  {" .-.  "},
  {"| oo| "},
  {"|   | "},
  {"'^^^' "}
};

char ui_hero[4][7] = {
  {" .--. "},
  {"/ _.-'"},
  {"\\  '-."},
  {" '--' "}
};

char ui_bomb[4][7] = {
  {"\\ | / "},
  {"_.-._ "},
  {" '-'  "},
  {"/ | \\ "}
};

char ui_food[4][7] = {
  {"      "},
  {" .-.  "},
  {" '-'  "},
  {"      "}
};

char ui_empty[4][7] = {
  {"      "},
  {"      "},
  {"      "},
  {"      "}
};

void print_map(MAP *m) {
  for (int i = 0; i < m->rows; i++) {
    for (int ui_row = 0; ui_row < 4; ui_row++) {
      for (int j = 0; j < m->cols; j++) {
        switch (m->matrix[i][j]) {
          case FOOD:
            printf("%s", ui_food[ui_row]);
            break;
          case EMPTY:
            printf("%s", ui_empty[ui_row]);
            break;
          case VERTICAL_WALL:
          case HORIZONTAL_WALL:
          case CORNER_WALL:
            printf("%s", ui_wall[ui_row]);
            break;
          case GHOST:
            printf("%s", ui_ghost[ui_row]);
            break;
          case HERO:
            printf("%s", ui_hero[ui_row]);
            break;
          case BOMB:
            printf("%s", ui_bomb[ui_row]);
            break;
        }
      }
      printf("\n");
    }
  }
}
