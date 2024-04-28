//#ifndef 2048
//#define 2048

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define SIZE 4

int board[4][4];

//defines each individual tile.
typedef struct tile{
    int value;
    int locationx;
    int locationy;
}tile;

//defines board as an array of tiles.
typedef struct game{
    tile tiles[4][4];
    int score;
}game;


void init_board();
void randtile(game* c);
int keepscore(game *c);
void printboard(game *c);
void mathup(game *c, int *change);
void mathleft(game *c, int *change);
void mathdown(game *c, int *change);
void mathright(game *c, int *change);
char getch();
int maxtile(game *c);
bool check_game_over(game *c);
bool check_tile_2048(game *c);


//#endif 