#include "game.h"

//2048 math function for up.
void mathup(game *c, int* change) {

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
                        i = k; 
                        *change = 1;
                    }
                    else if(above_value == b) {
                        c->tiles[k][j].value = b * 2;
                        c->tiles[i][j].value = 0;
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

//2048 math function for left.
void mathleft(game *c, int *change) {
    //iterate through every tile to find a tile with value (not 0)
    for(int i = 0; i < SIZE; i++) {
        for(int j = 1; j < SIZE; j++) { 
            int b = c->tiles[i][j].value;
            if(b != 0) {
                //check tile to the left 
                int k = j - 1;
                //move left while left tile value remains 0
                while(k >= 0) {
                    int left_value = c->tiles[i][k].value;
                    //update tile values
                    if(left_value == 0) {
                        c->tiles[i][k].value = b;
                        c->tiles[i][j].value = 0;
                        j = k; 
                        *change = 1;
                    }
                    //if left tile value is equal combine tiles (multiply value by 2 and delete previous location)
                    else if(left_value == b) {
                        c->tiles[i][k].value = b * 2;
                        c->tiles[i][j].value = 0;
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
    //if a change was made to the board (motion or combination) add a random tile to the board and set change variable back to 0
    if(*change == 1){
    randtile(c);
    *change = 0;
    }
}
//*the comments on function mathleft apply to the remaining math functions*

//2048 math function for right.
void mathright(game *c, int *change) {
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
                        j = k; 
                        *change = 1;
                    }
                    else if(right_value == b) { 
                        c->tiles[i][k].value = b * 2;
                        c->tiles[i][j].value = 0;
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
