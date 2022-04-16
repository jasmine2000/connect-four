#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "setup.h"
#include "output.h"

const int SETUP=0;
const int GAMEPLAY=1;
const int LEADERBOARD=2;


int main() {
    
    int state = SETUP;
    
    char all_players[10][11] = {0};   // all players ever
    int all_scores[10] = {0};         // corresponding scores (in same order)

    int player_arr[2];          // index of current players (from all_players)
    int current_player = 0;     // index of current player (from player_arr)

    int winner;                 // index of winner (from player_arr)

    // board
    int board[6][7];

    for(;;) {
        if (state == SETUP) {
            clear_board(board);

            int i;
            for (i = 0; i < 5; i ++) {

                char new_player[11] = {0};
                get_player(new_player);

                int index = find_player(new_player, all_players);
                strcpy(all_players[index], new_player);
                
            }
                        
            // state = GAMEPLAY;

        } else if (state == GAMEPLAY) {

            printboard(board);

        } else if (state == LEADERBOARD) {

        }
    }
}
