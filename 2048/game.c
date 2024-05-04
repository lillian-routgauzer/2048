#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define SIZE 4
int board[4][4];

// defines each individual tile.
typedef struct tile {
  int value;
  int locationx;
  int locationy;
} tile;

// defines board as an array of tiles.
typedef struct game {
  tile tiles[4][4];
  int score;
} game;

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
// 2048 math function for up.
void mathup(game *c, int *change) {

  for (int j = 0; j < SIZE; j++) {
    for (int i = 1; i < SIZE; i++) {
      int b = c->tiles[i][j].value;
      if (b != 0) {
        int k = i - 1;
        while (k >= 0) {
          int above_value = c->tiles[k][j].value;
          if (above_value == 0) {
            c->tiles[k][j].value = b;
            c->tiles[i][j].value = 0;
            i = k;
            *change = 1;
          } else if (above_value == b) {
            c->tiles[k][j].value = b * 2;
            c->tiles[i][j].value = 0;
            break;
            *change = 1;
          } else {
            break;
          }
          k--;
        }
      }
    }
  }
  if (*change == 1) {
    randtile(c);
    *change = 0;
  }
}

// 2048 math function for down.
void mathdown(game *c, int *change) {

  for (int i = SIZE - 2; i >= 0; i--) {
    for (int j = 0; j < SIZE; j++) {
      int b = c->tiles[i][j].value;
      if (b != 0) {
        int k = i + 1;
        while (k < SIZE) {
          int below_value = c->tiles[k][j].value;
          if (below_value == 0) {
            c->tiles[k][j].value = b;
            c->tiles[i][j].value = 0;
            *change = 1;
          } else if (below_value == b) {
            c->tiles[k][j].value = b * 2;
            c->tiles[i][j].value = 0;
            *change = 1;
            break;
          } else {
            break;
          }
          i = k;
          k++;
        }
      }
    }
  }
  if (*change == 1) {
    randtile(c);
    *change = 0;
  }
}

// 2048 math function for left.
void mathleft(game *c, int *change) {
  // iterate through every tile to find a tile with value (not 0)
  for (int i = 0; i < SIZE; i++) {
    for (int j = 1; j < SIZE; j++) {
      int b = c->tiles[i][j].value;
      if (b != 0) {
        // check tile to the left
        int k = j - 1;
        // move left while left tile value remains 0
        while (k >= 0) {
          int left_value = c->tiles[i][k].value;
          // update tile values
          if (left_value == 0) {
            c->tiles[i][k].value = b;
            c->tiles[i][j].value = 0;
            j = k;
            *change = 1;
          }
          // if left tile value is equal combine tiles (multiply value by 2 and
          // delete previous location)
          else if (left_value == b) {
            c->tiles[i][k].value = b * 2;
            c->tiles[i][j].value = 0;
            *change = 1;
            break;
          } else {
            break;
          }
          k--;
        }
      }
    }
  }
  // if a change was made to the board (motion or combination) add a random tile
  // to the board and set change variable back to 0
  if (*change == 1) {
    randtile(c);
    *change = 0;
  }
}
//*the comments on function mathleft apply to the remaining math functions*

// 2048 math function for right.
void mathright(game *c, int *change) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = SIZE - 1; j >= 0; j--) {
      int b = c->tiles[i][j].value;
      if (b != 0) {
        int k = j + 1;
        while (k < SIZE) {
          int right_value = c->tiles[i][k].value;
          if (right_value == 0) {
            c->tiles[i][k].value = b;
            c->tiles[i][j].value = 0;
            j = k;
            *change = 1;
          } else if (right_value == b) {
            c->tiles[i][k].value = b * 2;
            c->tiles[i][j].value = 0;
            *change = 1;
            break;
          } else {
            break;
          }
          k++;
        }
      }
    }
  }
  if (*change == 1) {
    randtile(c);
    *change = 0;
  }
}

// initialize board
void init_board() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      board[i][j] = 0;
    }
  }
}

// print board with emojis instead of numbers
void printboard(game *c) {
  char *emojis[] = {
      "⬜️ ", // Emoji for 0
      "😶 ",      // Emoji for 2
      "🙂 ",   // Emoji for 4
      "😊 ",      // Emoji for 8
      "😃 ",      // Emoji for 16
      "😁 ",      // Emoji for 32
      "🤩 ",   // Emoji for 64
      "🤗 ",   // Emoji for 128
      "😍 ",      // Emoji for 256
      "😎 ",      // Emoji for 512
      "🥳 ",   // Emoji for 1024
      "🤠 ",   // Emoji for 2048
      "🤓 ",   // Emoji for 4096
  };
  // use log base 2 to determine the tile hierarchy as it corresponds to the
  // emojis (multiplication by 2 increases the value of log2 by 1)
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      int value = c->tiles[i][j].value;
      if (value >= 0 && value <= 4096) {
        int index = (value == 0) ? 0 : (int)(log2(value));
        printf("%s", emojis[index]); // print emoji for the value
      } else {
        printf("%d ", value); // print number if no corresponding emoji
                              // (shouldn't happen in actual gameplay)
      }
    }
    printf("\n");
  }
}

// getchar with termios.
char getch() {
  char buf = 0;

  // structure to store original terminal settings
  struct termios old = {0};
  fflush(stdout);

  // take current terminal attributes and store them in 'old'
  if (tcgetattr(0, &old) < 0) {
    perror("tcsetattr()");
  }

  // turns off canonical mode
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;

  // set minimum number of characters to read to 1 and timeout to 0 seconds
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;

  // apply modified terminal settings
  if (tcsetattr(0, TCSANOW, &old) < 0) {
    perror("tcsetattr ICANON");
  }
  // read a single character from the terminal
  if (read(0, &buf, 1) < 0) {
    perror("read()");
  }

  // restore og terminal settings
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;

  // apply restored terminal settings
  if (tcsetattr(0, TCSADRAIN, &old) < 0) {
    perror("tcsetattr ~ICANON");
  }

  // return the character read from the terminal
  return buf;
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

int main() {
  printf("                LET'S PLAY 2048!\n");
  printf("                  HOW TO PLAY:\n");
  printf("      Use your arrow keys to move the tiles.\n");
  printf("Tiles with the same number merge into one when they touch.\n");
  printf("            Add them up to reach 2048!\n");
  printf("               Press c to continue.\n");
  int m = 1;
  char input1 = getch();
  if (input1 == 'c') {
    game g = {};
    init_board();
    randtile(&g);
    randtile(&g);
    keepscore(&g);
    printf("SCORE: %d\n", keepscore(&g));
    printboard(&g);
    int change = 0;
    while (1) {
      printf("Enter your move (↑/←/↓/→): ");
      char input = getch();
      printf("%c\n", input);

      switch (input) {
      case '\033':          // Escape sequence
        input = getch();    // Get the next character
        if (input == '[') { // Check if it's '[' (indicating arrow key)
          input = getch();  // Get the specific arrow key character
          switch (input) {
          case 'A':              // Up arrow key
            mathup(&g, &change); // make moves
            keepscore(&g);       // count up points
            maxtile(&g);         // find max tile
            // print found values
            printf(" SCORE: %d \n", keepscore(&g));
            printf("MAX TILE: %d \n", maxtile(&g));
            printboard(&g);
            break;
          case 'D': // Left arrow key
            mathleft(&g, &change);
            keepscore(&g);
            maxtile(&g);
            printf(" SCORE: %d \n", keepscore(&g));
            printf("MAX TILE: %d \n", maxtile(&g));
            printboard(&g);
            break;
          case 'B': // Down arrow key
            mathdown(&g, &change);
            keepscore(&g);
            maxtile(&g);
            printf(" SCORE: %d \n", keepscore(&g));
            printf("MAX TILE: %d \n", maxtile(&g));
            printboard(&g);
            break;
          case 'C': // Right arrow key
            mathright(&g, &change);
            keepscore(&g);
            maxtile(&g);
            printf(" SCORE: %d \n", keepscore(&g));
            printf("MAX TILE: %d \n", maxtile(&g));
            printboard(&g);
            break;
          default:
            printf("Please use arrow keys (↑/←/↓/→). \n");
          }
        }
        break;
      default:
        printf("Please use arrow keys (↑/←/↓/→). \n");
      }
      // check if the game is over after every move (is the board full and no
      // moves can be made)
      if (check_game_over(&g)) {
        printf("GAME OVER\n");
        printf("You lose\n");
        break;
      }
      // check of the highest value is 2048 and allow user to continue playing
      // to achieve 4096
      if (check_tile_2048(&g)) {
        printf("You won 2048!\n");
        printf("Do you want to keep playing? (y/n): ");
        char choice = getch();
        printf("\n");
        if (choice == 'n' || choice == 'N') {
          printf("Game over. Thank you for playing!\n");
          break;
        } else if (choice == 'y' || choice == 'Y') {
          printf("Let's keep playing!\n");
        } else {
          printf("Invalid input. Please enter 'y' to keep playing or 'n' to "
                 "end the game.\n");
        }
      }
    }
  }
}
