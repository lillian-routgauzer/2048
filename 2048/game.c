#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

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

//function add tiles to game.
tile* addtile(game *c, tile *t){
    int i = t->locationx;
    int j = t->locationy;
    if(i >= 0 && i <SIZE && j>=0 && j<SIZE){
    return &c->tiles[i][j];
    }
return NULL;
}
//function to generate random tile location and value.
tile* randtile(game* c) {
    int d = (rand() % 2) ? 2 : 4;
    int i, j;
    do {
        i = rand() % SIZE; 
        j = rand() % SIZE; 
    } while (c->tiles[i][j].value != 0); 

    c->tiles[i][j].value = d;
    c->tiles[i][j].locationx = i;
    c->tiles[i][j].locationy = j;
    return &(c->tiles[i][j]); 
}
//2048 math function for up.
tile* mathup(game *c, int* change) {
    printf("Moved up\n");
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
                        printf("slid\n");
                        i = k; 
                        *change = 1;
                    }
                    else if(above_value == b) {
                        c->tiles[k][j].value = b * 2;
                        c->tiles[i][j].value = 0;
                        result = &c->tiles[k][j];
                        printf("mathed\n");
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
    tile* l = randtile(c);
    addtile(c, l);
    *change = 0;
    }
    return result;
}

//2048 math function for down.
tile* mathdown(game *c, int* change) {
    printf("Moved down\n");
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
                    printf("slid\n");
                    *change = 1; 
                    break;
                }
                if (below_value == b) { 
                    c->tiles[k][j].value = b * 2;
                    c->tiles[i][j].value = 0;
                    result = &c->tiles[k][j]; 
                    printf("mathed\n");
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
    tile* l = randtile(c);
    addtile(c, l);
    *change = 0;
    }
    return result; 
}

//2048 math function for left.
tile* mathleft(game *c, int *change) {
    printf("Moved left\n");
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
                        printf("slid\n");
                        j = k; 
                        *change = 1;
                    }
                    else if(left_value == b) {
                        c->tiles[i][k].value = b * 2;
                        c->tiles[i][j].value = 0;
                        result = &c->tiles[i][k];
                        printf("mathed\n");
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
    tile* l = randtile(c);
    addtile(c, l);
    *change = 0;
    }
    return result;
}

//2048 math function for right.
tile* mathright(game *c, int *change) {
    tile* result = NULL; 
    printf("Moved right\n");
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
                        printf("slid\n");
                        j = k; 
                        *change = 1;
                    }
                    else if(right_value == b) { 
                        c->tiles[i][k].value = b * 2;
                        c->tiles[i][j].value = 0;
                        result = &c->tiles[i][k]; 
                        printf("mathed\n");
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
    tile* l = randtile(c);
    addtile(c, l);
    *change = 0;
    }
    return result;
}
      
void init_board(){
	for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

void printboard(game *c){
    for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
               // if(c->tiles[i][j].value != 0){
                    printf("%d ",c->tiles[i][j].value);
               // }
            }
        printf("\n");
        }
    }


//move function.
int move(void){
	char input[4] = {'s','w','a','d'};
	int m;
	while (isspace(m = getchar()));
	if (m == EOF)
		return m;
	for (int i = 0; i < 4; ++i)
		if (m == input[i])
			return i;
	return EOF;
}

// getchar with termios.
char getch() {
    struct termios oldattr, newattr;
    char ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}


int main() {
    game g = {};
    init_board();
    addtile(&g, randtile(&g));
    addtile(&g, randtile(&g));
    keepscore(&g);
    printf("SCORE: %d\n", keepscore(&g));
    printboard(&g);
    int change = 0;

    // Main game loop
    while (1) {
        printf("Enter your move (w/a/s/d): ");
        char input = getch();
        printf("%c\n", input); 

        switch (input) {
            case 'w':
            {
            tile* moved_up = mathup(&g, &change);
                if (moved_up != NULL) {
                    addtile(&g, moved_up);
                    keepscore(&g);
                    printf("SCORE: %d \n", keepscore(&g));
                }
                printboard(&g);
                break;
            }
            case 'a':{
            tile* moved_left = mathleft(&g, &change);
                if (moved_left != NULL) {
                    addtile(&g, moved_left);
                    keepscore(&g);
                    printf("SCORE: %d \n", keepscore(&g));
                }
                printboard(&g);
                break;
            }    
            case 's':{
            tile* moved_down = mathdown(&g, &change);
                if (moved_down != NULL) {
                    addtile(&g, moved_down);
                    keepscore(&g);
                    printf("SCORE: %d \n", keepscore(&g));
                    
                }
                printboard(&g);
                break;
            }
            case 'd':{
            tile* moved_right = mathright(&g, &change);
                if (moved_right != NULL) {
                    addtile(&g, moved_right);
                    keepscore(&g);
                    printf("SCORE: %d \n", keepscore(&g));
                }
                printboard(&g);
                break;
            }
            default:
                printf("Please used 'w' 'a' 's' 'd' keys. \n");
        }
    }
}

