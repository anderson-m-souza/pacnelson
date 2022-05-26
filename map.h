#ifndef _MAP_H_
#define _MAP_H_

#define MAP_FILENAME "map.txt"
#define HERO '@'
#define GHOST 'F'
#define EMPTY ' '
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define CORNER_WALL '+'
#define FOOD '.'
#define BOMB 'B'

struct map {
  char** matrix;
  int rows;
  int cols;
};

typedef struct map MAP;

struct position {
  int x;
  int y;
};

typedef struct position POSITION;


void map_malloc(MAP *m);
void free_map(MAP *m);
void read_map(MAP *m, int ghosts);
int get_position(MAP *m, POSITION *pos, char item);
int valid_pos(MAP *m, char x, char y, char item);
int empty_pos(MAP *m, char x, char y);
int is_wall(MAP *m, char x, char y);
int is_item(MAP *m, char x, char y, char item);
void change_pos(MAP *m, MAP *m_food, int x, int y,
    int new_x, int new_y, char item);
void copy_map(MAP *map_dest, MAP *map_orig);
int new_pos(MAP *m, int x, int y,
    int *x_dest, int *y_dest);

#endif
