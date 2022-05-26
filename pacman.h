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
void ghosts();
void explode(int x, int y, int radius);
