#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "map.h"

void read_map(MAP *m, int ghosts)
{
  char map_file[20] = MAP_FILENAME;

  FILE *f;
  f = fopen(map_file, "r");

  if (f == 0) {
    printf("Failed reading %s\n", map_file);
    exit(1);
  }

  fscanf(f, "%d %d", &m->rows, &m->cols);
  map_malloc(m);

  for (int i = 0; i < m->rows; i++) {

    fscanf(f, "%s", m->matrix[i]);

    if (!ghosts) {

      for (int j = 0; m->matrix[i][j] != '\0';j++) {

        if (m->matrix[i][j] == GHOST) {
          m->matrix[i][j] = EMPTY;
        } else {
          continue;
        }
      }
    }
  }

  fclose(f);
}

void map_malloc(MAP *m)
{
  m->matrix = malloc(sizeof(char*) * m->rows);

  for (int i = 0; i < m->rows; i++) {
    m->matrix[i] = malloc(sizeof(char) * (m->cols + 1));
  }
}

void count_food(MAP m, int *remaining_food)
{
  int food = 0;

  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.cols; j++) {

      if (m.matrix[i][j] == FOOD) {
        food++;
      }
    }
  }

  *remaining_food = food;
}

int get_position(MAP *m, POSITION *pos, char item)
{
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {

      if (m->matrix[i][j] == item) {
        pos->x = i;
        pos->y = j;

        return 1;
      }
    }
  }

  return 0;
}

int valid_pos(MAP *m, char x, char y, char item)
{
  return !is_wall(m, x, y)
         && !is_item(m, x, y, item);
}

int is_wall(MAP *m, char x, char y)
{
  return m->matrix[x][y] == VERTICAL_WALL
         || m->matrix[x][y] == HORIZONTAL_WALL
         || m->matrix[x][y] == CORNER_WALL;
}

int is_item(MAP *m, char x, char y, char item)
{
  return m->matrix[x][y] == item;
}

void change_pos(MAP *m, MAP *m_food, int x, int y,
                int new_x, int new_y, char item)
{
  if (item == HERO) {
    m_food->matrix[x][y] = EMPTY;
    m->matrix[x][y] = EMPTY;

  } else {
    m->matrix[x][y] = m_food->matrix[x][y];
  }

  m->matrix[new_x][new_y] = item;
}

void copy_map(MAP *map_dest, MAP *map_orig)
{
  map_dest->rows = map_orig->rows;
  map_dest->cols = map_orig->cols;
  
  map_malloc(map_dest);

  for (int i = 0; i < map_orig->rows; i++) {
    strcpy(map_dest->matrix[i], map_orig->matrix[i]);
  }
}

int new_ghost_pos(MAP *m, int x, int y,
                  int *x_dest, int *y_dest)
{

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

    if (valid_pos(m, new_x, new_y, GHOST)) {
      *x_dest = new_x;
      *y_dest = new_y;

      return 1;
    }
  }

  return 0;
}

void free_map(MAP *m)
{
  for (int i = 0; i < m->rows; i++) {
    free(m->matrix[i]);
  }

  free(m->matrix);
}
