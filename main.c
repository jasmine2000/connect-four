#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "setup.h"
#include "gameplay.h"
#include "leaderboard.h"

#include "fake_tft.h"
/*
#include "tft_setup.h"
#include "tft_board.h"
#include "keyboard.h"
*/

#define max_players 9
#define name_length 11

// gameplay constants
#define HOME        0
#define SETUP       1
#define CHOOSING    2
#define DROPPING    3
#define LEADERBOARD 4

#define HELP            30
#define ASSIGN_1        1
#define ASSIGN_2        2
#define ADD_PLAYER      10
#define DELETE_PLAYER   11
#define CONFIRM_PLAYERS 12
#define GO_BACK         20

const int COLUMN_SELECT = 0; // gameplay
const int PLAYER_SELECT = 1; // adding/deleting during setup
const int OPTION_SELECT = 2; // choosing options during setup
const int CONFIRM_SELECT = 3; // confirmation
const int GAME_SELECT = 4;      // select game type

// tft constants
const int list_x = 20;
const int bottom_x = 10;
const int bottom_y = 240;
const int bottom_row_h = 20;

const int my_red = GUI_BLUE;
const int my_yellow = GUI_GREEN + GUI_BLUE;
const int my_blue = GUI_RED;

// global vars
int state;
int board[6][7];
    
char all_players[max_players][name_length] = {0};   // all players ever
int all_scores[max_players] = {0};                  // corresponding scores (in same order)
int num_players;                                    // total number of players at any time

int player_arr[2] = {max_players, max_players};     // index of current players (from all_players). initialized to invalid indices on purpose
int current_player;                                 // index of current player (from player_arr)

int game_type;          // 1 or 2 depending on number of players

// gameplay vars used in choosing + dropping
int selection;
int current_column;

// tft constants
const int SCREENX = 240;
const int SCREENY = 320;
const int bottom_x = 10;
const int bottom_y = 240;
const int bottom_row_h = 20;

// state functions
void home_state();
void setup_state();
void choosing_state();
void dropping_state();
void leaderboard_state();

void init()
{   
    // CyGlobalIntEnable;
    
    // UART_Start();                       // initialize UART
    // UART_ClearRxBuffer();
    // UART_ClearTxBuffer();
    
    // // init tft
    // SPIM_1_Start();
    // //emwin
    // GUI_Init();                             // initilize graphics library
    // GUI_Clear();
    // GUI_SetBkColor(GUI_WHITE);
    // tft_clear_screen();
    
    // gameplay init
    num_players = 0;
    state = HOME;
    
}

int main() {
    
    init();

    for(;;) {

        switch (state) {
            case HOME:
                home_state();
                break;

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

void home_state() {
    tft_clear_screen();
    tft_show_home();
        
    for (;;) {  // while not inputting 1 or 2, stay in loop
        int action = get_keypress(GAME_SELECT, 0);
        if (action > 0) { // game init
            if (action == 1) {
                player_arr[1] = max_players; // unassign second player if previously assigned
            }
            
            game_type = action;
            current_player = 0;
            clear_board(board);
            
            tft_clear_screen();
            tft_show_players_and_scores(all_players, all_scores, num_players, 0);
            tft_reassign(player_arr);
            
            state = SETUP;
            break;
        }
    }
}


void setup_state() {
    tft_show_options(game_type);
    int action = get_keypress(OPTION_SELECT, 0);

    switch (action) {
        case ASSIGN_2:
            if (game_type == 1) {
                error();        // can't select second player in single player mode
                break;
            }   // else, go into regular assign player flow
        case ASSIGN_1:
        {
            if (num_players > 0) {
                tft_clear_bottom();
                GUI_DispStringAt("Choose player to assign with keypad", list_x, bottom_y);
                
                CyDelay(250);
                int player_num = get_keypress(PLAYER_SELECT, num_players);
                switch (player_num) {
                    case 0:
                        error(); // Can't select that player
                        break;
                    
                    default:
                    {
                        int player_index = player_num - 1;
                        int arr_index = action - 1;
                        player_arr[arr_index] = player_index;
                        if (player_arr[!arr_index] == player_index) {   // if player was previously set to other player
                            player_arr[!arr_index] = max_players;
                        }
                        tft_reassign(player_arr);
                    } break;
                }
            } else {
                error();
            }
        } break;

        case ADD_PLAYER:
        {
            if (num_players == max_players) {
                error(); // Can't add any more players
            } else {
                char new_player[name_length];
                tft_clear_screen();
                keyboard_get_player(new_player);
                
                strcpy(all_players[num_players], new_player);
                num_players ++;
                
                tft_show_players_and_scores(all_players, all_scores, num_players, 0);
                tft_reassign(player_arr);
            }
        } break;

        case DELETE_PLAYER:
        {
            if (num_players > 0) {
                
                tft_clear_bottom();
                GUI_DispStringAt("Choose player to delete with keypad", list_x, bottom_y);
                
                CyDelay(250);
                int delete_number = get_keypress(PLAYER_SELECT, num_players);
                switch (delete_number) {
                    case 0:
                        error(); // Can't delete that");
                        break;
                    default:
                    {
                        int delete_index = delete_number - 1;
                      
                        GUI_DispStringAt("Deleting: ", list_x, bottom_y + 1.5 * bottom_row_h);
                        GUI_DispStringAt(all_players[delete_index], list_x + 100, bottom_y + 1.5 * bottom_row_h);
                        
                        GUI_DispStringAt("Press C to confirm delete", list_x, bottom_y + 2.5 * bottom_row_h);
                        GUI_DispStringAt("Press any other key to cancel", list_x, bottom_y + 3 * bottom_row_h);
                        
                        CyDelay(250);
                        int c = get_keypress(CONFIRM_SELECT, 0);
                        if (c == 1) {
                            do_delete(all_players, all_scores, player_arr, delete_index);
                            num_players --;
                        
                            tft_clear_screen();
                            tft_show_players_and_scores(all_players, all_scores, num_players, 0);
                            tft_reassign(player_arr);
                        } else {
                            tft_clear_bottom();
                        };
                        
                    } break;
                }
            } else {
                error();
        } break;

        case CONFIRM_PLAYERS:
        {
            if (player_arr[0] == max_players) {
                error(); // P1 must be set always
            } else if (player_arr[1] == max_players && game_type == 2) {
                error(); // P2 must be set for 2 player
            } else if (player_arr[0] == player_arr[1]) {
                error(); // Player 1 and 2 are the same. Reassign one of them
            } else {
                tft_clear_bottom();
                
                GUI_DispStringAt("Player 1: ", list_x, 240);
                GUI_DispStringAt(all_players[player_arr[0]], 100, 240);
                
                if (game_type == 2) {
                    GUI_DispStringAt("Player 2: ", list_x, 260);
                    GUI_DispStringAt(all_players[player_arr[1]], 100, 260);
                }
                
                GUI_DispStringAt("Press C to confirm players", list_x, 280);
                GUI_DispStringAt("Press any other key to cancel", list_x, 300);
                
                CyDelay(250);
                int c = get_keypress(CONFIRM_SELECT, 0);
                if (c == 1) {
                    current_player = 0;
                    selection = 4;
                    state = CHOOSING;
                    
                    tft_clear_screen();
                    tft_init_board();
                    player_lights(current_player);
                } else {
                    tft_clear_bottom();
                };
            }
        } break;
        
        case GO_BACK:
        {
            memset(player_arr, max_players, sizeof player_arr); // empty player assignments
            state = HOME;
        } break;
        
        case HELP:
        {
            tft_clear_screen();
            tft_help_screen();
            get_keypress(CONFIRM_SELECT, 0);    // just waiting for keypress
            
            tft_clear_screen();
            tft_show_players_and_scores(all_players, all_scores, num_players, 0);
            tft_reassign(player_arr);
        }

        default:
            error(); // printf("Unrecognized action.\n");
            break;
        }
    }
}

void choosing_state() {
    
    if (game_type == 1 && current_player == 1) {        // single player and its the computers turn
        current_column = get_computer_column(board);    // set column
        CyDelay(500);
        selection = 13;                                 // drop piece
    }

    tft_player_turn(all_players[player_arr[current_player]]);   // show whos turn
    
    switch (selection) {

        case 13:                // D on keypad
            state = DROPPING;
            break;

        case 20:                // * on keypad (exit)
        {
            CyDelay(250);
            GUI_SetColor(GUI_WHITE);
            GUI_FillRect(10, 290, 240, 320);
            GUI_SetColor(GUI_BLACK);
            GUI_SetBkColor(my_yellow);
            GUI_DispStringAt("Press C to confirm exit: ", 15, 295);
            GUI_SetBkColor(GUI_WHITE);
            int c = get_keypress(CONFIRM_SELECT, 0);
            switch (c) {
                case 1:
                    state = LEADERBOARD;
                    player_lights(2);
                    tft_clear_screen();
                    break;

                default:
                    GUI_SetColor(GUI_WHITE);
                    GUI_FillRect(10, 290, 240, 320);
                    GUI_SetColor(GUI_BLACK);
                    GUI_DispStringAt("Press D to drop", 15, 295);
                    selection = current_column; // set back to last valid entry
                    break;
            }
        } break;

        default:
        {
            if (selection == 0) {
                error(); // Invalid move
            } else {
                current_column = selection;     // set current column if valid column entry

                // update display
                // temp_printboard(board, current_column, current_player + 1);
                tft_preview_choice(current_column, current_player);  // update preview
            }
            CyDelay(250);
            selection = get_keypress(COLUMN_SELECT, 0); // get next user input
        } break;
    }
}

void dropping_state() {
    int column_index = current_column - 1;          // map column value to index
    int lowest_row = find_row(board, column_index); // get row it would fall into

    switch (lowest_row) {
        case 6:
        {
            error();        // column is full
            selection = 4;
            state = CHOOSING;
        } break;

        default:
        {
            // assign value and show on display
            board[lowest_row][column_index] = current_player + 1;
            tft_drop_chip(lowest_row, column_index, current_player);

            int winner = check_winner(board);   // check if someone won
            int winner_index = winner - 1;
            if (winner == 3) {          // 3 == draw
                tft_win_message(winner, "");
                player_lights(2);

            } else if (winner > 0) {   // 1 or 2 = winner
                all_scores[player_arr[winner_index]] ++;
                tft_win_message(winner_index, all_players[player_arr[winner_index]]);   // TODO
                CyDelay(2000);
                tft_clear_screen();
                
                player_lights(winner_index);
                state = LEADERBOARD;

            } else {
                current_player = (current_player + 1) % 2;      // increment and mod for player index
                selection = 4;
                
                player_lights(current_player);
                state = CHOOSING;
            }
        } break;
    }
}

void leaderboard_state() {
    
    sort_names_scores(all_players, all_scores, player_arr); // sort so in order

    tft_show_players_and_scores(all_players, all_scores, num_players, 1);
    
    GUI_DispStringAt("Press any key to go to home screen", list_x, bottom_y);
    get_keypress(CONFIRM_SELECT, 0);
    player_lights(2);
    state = HOME;
}

