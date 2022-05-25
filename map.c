#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

void copy_map(MAP *map_dest, MAP *map_orig) {
  map_dest->rows = map_orig->rows;
  map_dest->cols = map_orig->cols;
  
  map_malloc(map_dest);

  for (int i = 0; i < map_orig->rows; i++) {
    strcpy(map_dest->matrix[i], map_orig->matrix[i]);
  }
}

void get_position(MAP *m, POSITION *pos, char item) {
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      if (m->matrix[i][j] == item) {
        pos->x = i;
        pos->y = j;
        return;
      }
    }
  }
}

int valid_pos(MAP *m, char x, char y) {
  return (x < m->rows
       && x > 0
       && y < m->cols
       && y > 0);
}

int empty_pos(MAP *m, char x, char y) {
  return m->matrix[x][y] == EMPTY;
}

void change_pos(MAP *m, int x, int y,
                int new_x, int new_y, char item) {
  m->matrix[x][y] = EMPTY;
  m->matrix[new_x][new_y] = item;
}

void map_malloc(MAP *m) {
  m->matrix = malloc(sizeof(char*) * m->rows);
  for (int i = 0; i < m->rows; i++) {
    m->matrix[i] = malloc(sizeof(char) * (m->cols + 1));
  }
}

void free_map(MAP *m) {
  for (int i = 0; i < m->rows; i++) {
    free(m->matrix[i]);
  }
  free(m->matrix);
}

void read_map(MAP *m) {
  char map_file[20] = MAP_FILENAME;

  FILE *f;
  f = fopen(map_file, "r");
  if (f == 0) {
    printf("Failed reading %s\n", map_file);
    exit(1);
  }

  fscanf(f, "%d %d", &m->rows, &m->cols);
  printf("rows: %d\ncols: %d\n", m->rows, m->cols);

  map_malloc(m);

  for (int i = 0; i < m->rows; i++) {
    fscanf(f, "%s", m->matrix[i]);
  }
  fclose(f);
}

void print_map(MAP *m) {
  for (int i = 0; i < m->rows; i++) {
    printf("%s\n", m->matrix[i]);
  }
}
