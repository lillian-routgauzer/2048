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

int maxtile(game *c){
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

//function to generate random tile location and value.
void randtile(game* c) {
    int d = (rand() % 2) ? 2 : 4;
    int i, j;
    do {
        i = rand() % SIZE; 
        j = rand() % SIZE; 
    } while (c->tiles[i][j].value != 0); 

    c->tiles[i][j].value = d;
    c->tiles[i][j].locationx = i;
    c->tiles[i][j].locationy = j;
}
//2048 math function for up.
void mathup(game *c, int* change) {
    tile* result = NULL;

    for(int j = 0; j < SIZE; j++) {
        for(int i = 1; i < SIZE; i++) { 
            int b = c->tiles[i][j].value;
            if(b != 0) {
                int k = i - 1;
                while(k >= 0) {
                    int above_value = c->tiles[k][j].value;
                    if(above_value == 0) {
                        c->tiles[k][j].value = b;
                        c->tiles[i][j].value = 0;
                        result = &c->tiles[k][j];
                        i = k; 
                        *change = 1;
                    }
                    else if(above_value == b) {
                        c->tiles[k][j].value = b * 2;
                        c->tiles[i][j].value = 0;
                        result = &c->tiles[k][j];
                        break;
                        *change = 1;
                    }
                    else { 
                        break;
                    }
                    k--;
                }
            }
        }
    }
    if(*change == 1){
    randtile(c);
    *change = 0;
    }
}

//2048 math function for down.
void mathdown(game *c, int* change) {
    tile* result = NULL; 

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
                        result = &c->tiles[k][j];
                        *change = 1; 
                    } else if (below_value == b) { 
                        c->tiles[k][j].value = b * 2;
                        c->tiles[i][j].value = 0;
                        result = &c->tiles[k][j]; 
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

//2048 math function for left.
void mathleft(game *c, int *change) {
    tile* result = NULL;
    for(int i = 0; i < SIZE; i++) {
        for(int j = 1; j < SIZE; j++) { 
            int b = c->tiles[i][j].value;
            if(b != 0) {
                int k = j - 1;
                while(k >= 0) {
                    int left_value = c->tiles[i][k].value;
                    if(left_value == 0) {
                        c->tiles[i][k].value = b;
                        c->tiles[i][j].value = 0;
                        result = &c->tiles[i][k];
                        j = k; 
                        *change = 1;
                    }
                    else if(left_value == b) {
                        c->tiles[i][k].value = b * 2;
                        c->tiles[i][j].value = 0;
                        result = &c->tiles[i][k];
                        *change = 1;
                        break;
                    }
                    else {
                        break;
                    }
                    k--;
                }
            }
        }
    }
    if(*change == 1){
    randtile(c);
    *change = 0;
    }
}

//2048 math function for right.
void mathright(game *c, int *change) {
    tile* result = NULL; 
    for(int i = 0; i < SIZE; i++) { 
        for(int j = SIZE - 1; j >= 0; j--) { 
            int b = c->tiles[i][j].value; 
            if(b != 0) { 
                int k = j + 1; 
                while(k < SIZE) { 
                    int right_value = c->tiles[i][k].value; 
                    if(right_value == 0) { 
                        c->tiles[i][k].value = b;
                        c->tiles[i][j].value = 0;
                        result = &c->tiles[i][k]; 
                        j = k; 
                        *change = 1;
                    }
                    else if(right_value == b) { 
                        c->tiles[i][k].value = b * 2;
                        c->tiles[i][j].value = 0;
                        result = &c->tiles[i][k]; 
                        *change = 1;
                        break; 
                    }
                    else { 
                        break;
                    }
                    k++;
                }
            }
        }
    }
    if(*change == 1){
        randtile(c);
        *change = 0;
    }
}
      
void init_board(){
	for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

void printboard(game *c) {
    char *emojis[] = {
        "⬜️ ",   // Emoji for 0
        "😶 ",   // Emoji for 2
        "🙂 ",   // Emoji for 4
        "😊 ",   // Emoji for 8
        "😃 ",   // Emoji for 16
        "😁 ",   // Emoji for 32
        "🤩 ",   // Emoji for 64
        "🤗 ",   // Emoji for 128
        "😍 ",   // Emoji for 256
        "😎 ",   // Emoji for 512
        "🥳 ",   // Emoji for 1024
        "🤠 ",   // Emoji for 2048
        "🤓 ",   // Emoji for 4096 - do we want to allow play after 2048 reached?
    };
 
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            int value = c->tiles[i][j].value;
            if (value >= 0 && value <= 4096) {
                int index = (value == 0) ? 0 : (int)(log2(value));
                printf("%s", emojis[index]); // print emoji for the value
            } else {
                printf("%d ", value); // print number if no corresponding emoji (shouldn't happen in actual gameplay)
            }
        }
        printf("\n");
    }
}

// getchar with termios.
char getch() {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
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
    // if board is full, check if 2 of the same block are next to eachother horizontally
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

//check for win
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

int main(){
    printf("                LET'S PLAY 2048!\n");
    printf("                  HOW TO PLAY:\n");
    printf("      Use your arrow keys to move the tiles.\n");
    printf("Tiles with the same number merge into one when they touch.\n");
    printf("            Add them up to reach 2048!\n");
    printf("               Press c to continue.\n");
    int m = 1;
    char input1 = getch();
    if(input1 == 'c'){
    game g = {};
    init_board();
    randtile(&g);
    randtile(&g);
    keepscore(&g);
    printf("SCORE: %d\n", keepscore(&g));
    printboard(&g);
    int change = 0;
        while(1) {
            printf("Enter your move (↑/←/↓/→): ");
            char input = getch();
            printf("%c\n", input); 

            switch (input) {
                case '\033': // Escape sequence
                    input = getch(); // Get the next character
                    if (input == '[') { // Check if it's '[' (indicating arrow key)
                        input = getch(); // Get the specific arrow key character
                        switch (input) {
                            case 'A': // Up arrow key
                                mathup(&g, &change);
                                keepscore(&g);
                                maxtile(&g);
                                printf("SCORE: %d \n", keepscore(&g));
                                printf("MAX TILE: %d \n", maxtile(&g));
                                printboard(&g);
                                break;
                            case 'D': // Left arrow key
                                mathleft(&g, &change);
                                keepscore(&g);
                                maxtile(&g);
                                printf("SCORE: %d \n", keepscore(&g));
                                printf("MAX TILE: %d \n", maxtile(&g));
                                printboard(&g);
                                break;
                            case 'B': // Down arrow key
                                mathdown(&g, &change);
                                keepscore(&g);
                                maxtile(&g);
                                printf("SCORE: %d \n", keepscore(&g));
                                printf("MAX TILE: %d \n", maxtile(&g));
                                printboard(&g);
                                break;
                            case 'C': // Right arrow key
                                mathright(&g, &change);
                                keepscore(&g);
                                maxtile(&g);
                                printf("SCORE: %d \n", keepscore(&g));
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
 
            if (check_game_over(&g)) {
                printf("GAME OVER\n");
                printf("You lose\n");
                break;
            }
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
                printf("Invalid input. Please enter 'y' to keep playing or 'n' to end the game.\n");
        }
    }
        }
    }
}
