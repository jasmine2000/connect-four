#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "setup.h"
#include "gameplay.h"
#include "output.h"
#include "leaderboard.h"

const int SETUP=0;
const int CHOOSING=1;
const int DROPPING=2;
const int LEADERBOARD=3;


int main() {
    
    int state = SETUP;
    
    char all_players[10][11] = {0};   // all players ever
    int all_scores[10] = {0};         // corresponding scores (in same order)

    int player_arr[2] = {9, 9};     // index of current players (from all_players)
    int current_player;     // index of current player (from player_arr)

    int winner;                 // index of winner (from player_arr)

    int players_exist;
    int action;

    int selection;
    int current_column;
    int players_set[2] = {0, 0};

    // board
    int board[6][7];

    for(;;) {

        if (state == SETUP) {
            clear_board(board);

            int next = next_available(all_players);
            if (next == 0) {
                players_exist = 0;
            } else {
                players_exist = 1;
            }

            action = player_screen(all_players, player_arr, players_exist);

            if (action == ASSIGN_1 || action == ASSIGN_2) {
                int player_num = get_existing_player(all_players, action + 1, next);
                if (player_num == 0) {
                    printf("Can't select that player. \n");
                } else {
                    int player_index = player_num - 1;
                    player_arr[action] = player_index;
                    players_set[action] = 1;
                }

            } else if (action == ADD_PLAYER) {
                if (next == 10) {
                    printf("%s", "Can't add any more players. Delete one and try again. \n");
                } else {
                    char new_player[11];
                    get_new_player(new_player);
                    strcpy(all_players[next], new_player);
                }

            } else if (action == DELETE_PLAYER) {
                if (next == 0) {
                    printf("Nothing to delete.\n\n");
                } else {
                    int delete_number = select_delete(all_players);

                    if (delete_number == 0) {
                        printf("Can't delete that.\n");
                    } else {
                        int delete_index = delete_number - 1;
                        char delete_player[11];
                        strcpy(delete_player, all_players[delete_index]);
                        if (confirm_delete(delete_player) == 1) {
                            do_delete(all_players, delete_index);
                        };
                    }
                }
                
            } else if (action == CONFIRM_PLAYERS) {
                if (players_set[0] == 0 || players_set[1] == 0) {
                    printf("Players are not both set.\n\n");
                } else if (player_arr[0] == player_arr[1]) {
                    printf("Player 1 and 2 are the same. Reassign one of them.\n\n");
                } else {
                    printf("Player 1 \t %s\n", all_players[player_arr[0]]);
                    printf("Player 2 \t %s\n", all_players[player_arr[1]]);

                    printf("Confirm selection? (y/n) ");
                    char buffer[5];
                    fgets(buffer, 5, stdin);
                    if (buffer[0] == 'y') {
                        current_player = 0;
                        selection = 4;

                        state = CHOOSING;
                    }
                }

            } else { // invalid
                printf("Unrecognized action.\n");
            }
            

        } else if (state == CHOOSING) {

            int new_selection = 0;

            if (selection == 9) {
                int confirmation = early_exit();
                if (confirmation == 1) {
                    state = LEADERBOARD;

                } else {
                    selection = current_column;
                }

            } else if (selection == 8) {
                state = DROPPING;

            } else {
                if (selection == 0) {
                    printf("Invalid move.\n");
                    new_selection = 1;
                } else {
                    current_column = selection;
                    printboard(board, current_column, current_player + 1);
                    new_selection = 1;
                }
                selection = get_input(all_players[player_arr[current_player]]);
            }
            printf("\n");


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
                    all_scores[player_arr[winner - 1]]++;
                    printf("%s won!\n", all_players[player_arr[winner - 1]]);

                    state = LEADERBOARD;

                } else {
                    current_player = (current_player + 1) % 2;
                    selection = 4;
                    
                    state = CHOOSING;
                }
            }

        } else if (state == LEADERBOARD) {

            printf("\n");
            sort_names_scores(all_players, all_scores);
            show_stats(all_players, all_scores);
            
            printf("\nPress enter to start a new game: ");
            char buffer[3];
            fgets(buffer, 3, stdin);

            state = SETUP;
        }
    }
}
