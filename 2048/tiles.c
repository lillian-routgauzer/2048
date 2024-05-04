#include "game.h"

// function to calculate max tile value.
int maxtile(game *c) {
  int max = c->tiles[0][0].value;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      int val = c->tiles[i][j].value;
      if (val > max) {
        max = val;
      }
    }
  }
  return max;
}

// function to generate random tile location and value.
void randtile(game *c) {
  int d = (rand() % 2) ? 2 : 4;
  int i, j;
  do {
    i = rand() % SIZE;
    j = rand() % SIZE;
  } while (c->tiles[i][j].value != 0);

  // updates values of tile struct
  c->tiles[i][j].value = d;
  c->tiles[i][j].locationx = i;
  c->tiles[i][j].locationy = j;
}