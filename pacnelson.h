#ifndef _PACNELSON_H_
#define _PACNELSON_H_

#define UP 'w'
#define UP_VIM 'k'
#define DOWN 's'
#define DOWN_VIM 'j'
#define LEFT 'a'
#define LEFT_VIM 'h'
#define RIGHT 'd'
#define RIGHT_VIM 'l'
#define EXPLODE 'b'

void ncurses_init();
void exec_commands();
void explode();
void explode_helper(int x, int y,
                    int x_sum, int y_sum, int radius);
void move_hero(char command);
void ghosts();
void check_game_over();
int won();
void ncurses_update();
void ncurses_end();

#endif
