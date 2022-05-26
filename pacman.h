#ifndef _PACMAN_H_
#define _PACMAN_H_

#define UP 'w'
#define UP_VIM 'k'
#define DOWN 's'
#define DOWN_VIM 'j'
#define LEFT 'a'
#define LEFT_VIM 'h'
#define RIGHT 'd'
#define RIGHT_VIM 'l'
#define EXPLODE 'b'

void move(char command);
int game_over();
int won();
void ghosts();
void explode();
void explode_helper(int x, int y,
    int x_sum, int y_sum, int radius);

#endif
