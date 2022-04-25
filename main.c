#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "setup.h"
#include "gameplay.h"
#include "output.h"
#include "leaderboard.h"

// #include "keypad.h"
// #include "keyboard.h"
// #include "tft.h"

// constants
const int SETUP=0;
const int CHOOSING=1;
const int DROPPING=2;
const int LEADERBOARD=3;
const int max_players = 9;

// global vars
int state;
int board[6][7];
    
char all_players[max_players][11] = {0};   // all players ever
int all_scores[max_players] = {0};         // corresponding scores (in same order)

int player_arr[2] = {max_players, max_players};     // index of current players (from all_players). initialized to invalid indices on purpose
int current_player;     // index of current player (from player_arr)

// gameplay vars used in choosing + dropping
int selection;
int current_column;



void init() {
    // CyGlobalIntEnable;

    state = SETUP;
    current_player = 0;
    clear_board(board);
}

int main() {
    
    init();

    for(;;) {

        if (state == SETUP) {

            int next = next_available(all_players);
            int action = player_screen(all_players, player_arr, next);

            if (action == ASSIGN_1 || action == ASSIGN_2) {
                show_players(all_players, next);
                if (next > 0) {
                    printf("Player %d choose from list: ", action + 1);
                    int player_num = select_player(next);
                    if (player_num == 0) {
                        printf("Can't select that player. \n\n");
                    } else {
                        int player_index = player_num - 1;
                        player_arr[action] = player_index;
                    }
                }

            } else if (action == ADD_PLAYER) {
                if (next == max_players) {
                    printf("%s", "Can't add any more players. Delete one and try again. \n");
                } else {
                    char new_player[11];
                    get_new_player(new_player);
                    strcpy(all_players[next], new_player);
                }

            } else if (action == DELETE_PLAYER) {
                show_players(all_players, next);
                if (next > 0) {
                    printf("%s", "\nSelect player number to delete: ");
                    int delete_number = select_player(next);

                    if (delete_number == 0) {
                        printf("Can't delete that.\n");
                    } else {
                        int delete_index = delete_number - 1;
                        printf("Are you sure you want to delete %s? ", all_players[delete_index]);
                        
                        int c = confirm();
                        if (c == 1) {
                            do_delete(all_players, delete_index);
                        };
                    }
                }
                
            } else if (action == CONFIRM_PLAYERS) {
                if (player_arr[0] == max_players || player_arr[1] == max_players) {
                    printf("Players are not both set.\n\n");
                } else if (player_arr[0] == player_arr[1]) {
                    printf("Player 1 and 2 are the same. Reassign one of them.\n\n");
                } else {
                    printf("Player 1 \t %s\n", all_players[player_arr[0]]);
                    printf("Player 2 \t %s\n", all_players[player_arr[1]]);

                    printf("Confirm selection? ");
                    int c = confirm();
                    if (c == 1) {
                        current_player = 0;
                        selection = 4;

                        state = CHOOSING;
                    };
                }

            } else { // invalid
                printf("Unrecognized action.\n");
            }
            

        } else if (state == CHOOSING) {


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
                } else {
                    current_column = selection;
                    printboard(board, current_column, current_player + 1);
                }
                selection = get_input(all_players[player_arr[current_player]]);
            }
            printf("\n");


        } else if (state == DROPPING) {

            int column_index = current_column - 1;
            int lowest_row = find_row(board, column_index);

            if (lowest_row == 6) {
                printf("Column is full.\n");
                selection = 4;
                state = CHOOSING;
            } else {
                board[lowest_row][column_index] = current_player + 1;
                printboard(board, 0, current_player + 1);
                printf("\n");

                int winner = check_winner(board);
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
            sort_names_scores(all_players, all_scores, player_arr);
            show_stats(all_players, all_scores);
            
            printf("\nPress enter to start a new game: ");
            char buffer[3];
            fgets(buffer, 3, stdin);

            clear_board(board);
            state = SETUP;
        }
    }
}
