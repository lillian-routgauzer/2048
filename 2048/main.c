#include "game.h"

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
                case '\033': //Escape sequence
                    input = getch(); //Get the next character
                    if (input == '[') { //Check if it's '[' (indicating arrow key)
                        input = getch(); //Get the specific arrow key character
                        switch (input) {
                            case 'A': //Up arrow key
                                mathup(&g, &change);//make moves
                                keepscore(&g);//count up points
                                maxtile(&g);//find max tile
                                //print found values
                                printf("xSCORE: %d\n", keepscore(&g));
                                printf("MAX TILE: %d \n", maxtile(&g));
                                printboard(&g);
                                break;
                            case 'B': //Down arrow key
                                mathdown(&g, &change);
                                keepscore(&g);
                                maxtile(&g);
                                printf("xSCORE: %d\n", keepscore(&g));
                                printf("MAX TILE: %d \n", maxtile(&g));
                                printboard(&g);
                                break;
                            case 'C': //Right arrow key
                                mathright(&g, &change);
                                keepscore(&g);
                                maxtile(&g);
                                printf("xSCORE: %d\n", keepscore(&g));
                                printf("MAX TILE: %d \n", maxtile(&g));
                                printboard(&g);
                                break;
                            case 'D': //Left arrow key
                                mathleft(&g, &change);
                                keepscore(&g);
                                maxtile(&g);
                                printf("xSCORE: %d\n", keepscore(&g));
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
            //check if the game is over after every move (is the board full and no moves can be made)
            if (check_game_over(&g)) {
                printf("GAME OVER\n");
                printf("You lose\n");
                break;
            }
            //check of the highest value is 2048 and allow user to continue playing to achieve 4096
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
