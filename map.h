#define MAP_FILENAME "map.txt"
#define HERO '@'
#define GHOST 'F'
#define EMPTY '.'

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
void read_map(MAP *m);
void print_map(MAP *m);
void get_position(MAP *m, POSITION *pos, char item);
int valid_pos(MAP *m, char x, char y);
int empty_pos(MAP *m, char x, char y);
void change_pos(MAP *m, int x, int y,
                int new_x, int new_y, char item);
void copy_map(MAP *map_dest, MAP *map_orig);
int new_pos(int x, int y,
    int *x_dest, int *y_dest);
