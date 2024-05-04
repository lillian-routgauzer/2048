#include "game.h"

// function that keeps score, uses tile value
int keepscore(game *c) {
  c->score = 0;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      int val = c->tiles[i][j].value;
      c->score += val;
    }
  }
  return c->score;
}

// check if player has lost
bool check_game_over(game *c) {
  // first check for empty tiles
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (c->tiles[i][j].value == 0) {
        return false;
      }
    }
  }
  // if board is full, check if 2 of the same block are next to eachother
  // horizontally
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE - 1; j++) {
      if (c->tiles[i][j].value == c->tiles[i][j + 1].value) {
        return false;
      }
    }
  }
  // same for vertical
  for (int i = 0; i < SIZE - 1; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (c->tiles[i][j].value == c->tiles[i + 1][j].value) {
        return false;
      }
    }
  }
  // game over if no moves
  return true;
}

// check for win
bool check_tile_2048(game *c) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (c->tiles[i][j].value == 2048) {
        return true;
      }
    }
  }
  return false;
}