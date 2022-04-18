#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "setup.h"
#include "gameplay.h"
#include "output.h"

const int SETUP=0;
const int CHOOSING=1;
const int DROPPING=2;
const int ENDGAME=3;
const int LEADERBOARD=4;


int main() {
    
    int state = SETUP;
    
    char all_players[10][11] = {0};   // all players ever
    int all_scores[10] = {0};         // corresponding scores (in same order)

    int player_arr[2];          // index of current players (from all_players)
    int current_player;     // index of current player (from player_arr)

    int winner;                 // index of winner (from player_arr)
    int showboard;

    int selection;
    int current_column;

    // board
    int board[6][7];

    for(;;) {

        if (state == SETUP) {
            clear_board(board);

            int i;
            for (i = 0; i < 2; i ++) {
                printf("Enter player %d's name: ", i + 1);

                char new_player[11] = {0};
                get_player(new_player);

                int index = find_player(new_player, all_players);
                strcpy(all_players[index], new_player);

                player_arr[i] = index;
            }
            printf("\n");

            current_player = 0;
            selection = 4;

            state = CHOOSING;

        } else if (state == CHOOSING) {

            int new_selection = 0;

            if (selection == 0) {
                printf("Invalid move.\n");
                new_selection = 1;

            } else if (selection == 8) state = DROPPING;

            else if (selection == 9) {
                int confirmation = early_exit();
                if (confirmation == 1) {
                    state = LEADERBOARD;
                    showboard = 1;
                } else selection = current_column;

            } else {
                current_column = selection;
                printboard(board, current_column, current_player + 1);
                new_selection = 1;
            }
            printf("\n");

            if (new_selection == 1) {
                selection = get_input(all_players[player_arr[current_player]]);
            }

        } else if (state == DROPPING) {

            int column_index = current_column - 1;
            int row = find_row(board, column_index);

            if (row == 6) {
                printf("Column is full.\n");
                selection = 4;
                state = CHOOSING;
            } else {
                board[row][column_index] = current_player + 1;
                printboard(board, 0, current_player + 1);
                printf("\n");

                winner = check_winner(board);
                if (winner > 0) {
                    state = ENDGAME;

                } else {
                    current_player = (current_player + 1) % 2;
                    selection = 4;
                    
                    state = CHOOSING;
                }
            }

        } else if (state == ENDGAME) {
            
                all_scores[player_arr[winner - 1]]++;
                printf("%s won!\n", all_players[player_arr[winner - 1]]);

                state = LEADERBOARD;
            

        } else if (state == LEADERBOARD) {

            printf("\nLEADERBOARD\n");
            for (int i = 0; i < 10; i=i+1) {
                char player[11] = {0};
                strcpy(player, all_players[i]); // get player at index

                if (player[0] != '\0') {        // if empty
                    printf("%s: %d\n", player, all_scores[i]);
                }
            }
            
            printf("Press enter to start a new game: ");
            char buffer[3];
            fgets(buffer, 3, stdin);

            state = SETUP;
        }
    }
}
