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

const int ASSIGN_1 = 0;
const int ASSIGN_2 = 1;
const int ADD_PLAYER = 2;
const int DELETE_PLAYER = 3;
const int CONFIRM_PLAYERS = 4;
const int INVALID = 5;

// after keypad implement
// const int COLUMN_SELECT = 0; // gameplay
// const int PLAYER_SELECT = 1; // adding/deleting during setup
// const int OPTION_SELECT = 2; // choosing options during setup

const int max_players = 9;
const int name_length = 11;

// global vars
int state;
int board[6][7];
    
char all_players[max_players][name_length] = {0};   // all players ever
int all_scores[max_players] = {0};         // corresponding scores (in same order)

int player_arr[2] = {max_players, max_players};     // index of current players (from all_players). initialized to invalid indices on purpose
int current_player;     // index of current player (from player_arr)

// gameplay vars used in choosing + dropping
int selection;
int current_column;

// state functions
void setup_state();
void choosing_state();
void dropping_state();
void leaderboard_state();

void init() {
    // CyGlobalIntEnable;

    state = SETUP;
    current_player = 0;
    clear_board(board);
}

int main() {
    
    init();

    for(;;) {

        switch (state) {

            case SETUP: 
                setup_state();
                break;
            
            case CHOOSING: 
                choosing_state();
                break;

            case DROPPING: 
                dropping_state();
                break;

            case LEADERBOARD: 
                leaderboard_state();
                break;

        }
    }
}

void setup_state() {
    int next = next_available(all_players);
    int action = player_screen(all_players, player_arr, next);

    switch (action) {
        case ASSIGN_1:
        case ASSIGN_2:
        {
            temp_show_players(all_players);
            if (next > 0) {
                printf("Player %d choose from list: ", action + 1);
                int player_num = temp_select_player(next);
                switch (player_num) {
                    case 0:
                        printf("Can't select that player. \n\n");
                        break;
                    
                    default:
                    {
                        int player_index = player_num - 1;
                        player_arr[action] = player_index;
                    } break;
                }
            }
        } break;

        case ADD_PLAYER:
        {
            if (next == max_players) {
            printf("%s", "Can't add any more players. Delete one and try again. \n");
            } else {
                char new_player[name_length];
                temp_get_new_player(new_player);
                strcpy(all_players[next], new_player);
            }
        } break;

        case DELETE_PLAYER:
        {
            temp_show_players(all_players);
            if (next > 0) {
                printf("%s", "\nSelect player number to delete: ");
                int delete_number = temp_select_player(next);

                switch (delete_number) {
                    case 0:
                        printf("Can't delete that.\n");
                        break;
                    default:
                    {
                        int delete_index = delete_number - 1;
                        printf("Are you sure you want to delete %s? ", all_players[delete_index]);
                        
                        int c = temp_confirm();
                        if (c == 1) {
                            do_delete(all_players, delete_index);
                        };
                    } break;
                }
            }
        } break;

        case CONFIRM_PLAYERS:
        {
            if (player_arr[0] == max_players || player_arr[1] == max_players) {
                printf("Players are not both set.\n\n");
            } else if (player_arr[0] == player_arr[1]) {
                printf("Player 1 and 2 are the same. Reassign one of them.\n\n");
            } else {
                printf("Player 1 \t %s\n", all_players[player_arr[0]]);
                printf("Player 2 \t %s\n", all_players[player_arr[1]]);

                printf("Confirm selection? ");
                int c = temp_confirm();
                if (c == 1) {
                    current_player = 0;
                    selection = 4;

                    state = CHOOSING;
                };
            }
        } break;

        default:
            printf("Unrecognized action.\n");
            break;
    }
}

void choosing_state() {
    switch (selection) {
        case 0:
            printf("Invalid move.\n");
            selection = temp_get_input(all_players[player_arr[current_player]]);
            break;

        case 12:
            state = DROPPING;
            break;

        case 20:
        {
            printf("Are you sure you want to exit (y/n): ");
            int c = temp_confirm();
            switch (c) {
                case 1:
                    state = LEADERBOARD;
                    break;

                default:
                    selection = current_column;
                    break;
            }
        } break;

        default:
        {
            current_column = selection;
            temp_printboard(board, current_column, current_player + 1);
            selection = temp_get_input(all_players[player_arr[current_player]]);
        } break;
    }

    printf("\n");
}

void dropping_state() {
    int column_index = current_column - 1;
    int lowest_row = find_row(board, column_index);

    switch (lowest_row) {
        case 6:
        {
            printf("Column is full.\n");
            selection = 4;
            state = CHOOSING;
        } break;

        default:
        {
            board[lowest_row][column_index] = current_player + 1;
            temp_printboard(board, 0, current_player + 1);
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
        } break;
    }
}

void leaderboard_state() {
    printf("\n");
    sort_names_scores(all_players, all_scores, player_arr);
    temp_show_players(all_players);
    // show_stats(all_players, all_scores);
    
    // temp get input
    printf("\nPress enter to start a new game: ");
    char buffer[3];
    fgets(buffer, 3, stdin);

    clear_board(board);
    state = SETUP;
}