#include "game.h"

//initialize board      
void init_board(game *g) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            g->tiles[i][j].value = 0;
            g->tiles[i][j].locationx = i;
            g->tiles[i][j].locationy = j;
        }
    }
}

//print board with emojis instead of numbers
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
        "🤓 ",   // Emoji for 4096 
    };
 //use log base 2 to determine the tile hierarchy as it corresponds to the emojis (multiplication by 2 increases the value of log2 by 1)
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


