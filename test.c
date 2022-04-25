#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>

#include "setup.h"
#include "gameplay.h"
#include "output.h"
#include "leaderboard.h"

const int max_players = 9;

void winner_tests();
void sort_tests();
void setup_tests();


int main() {

    winner_tests();

    sort_tests();

    setup_tests();
    
    return 0;
}


void winner_tests() {
    // board
    int board[6][7];
    int winner;

    clear_board(board);
    winner = check_winner(board);
    assert(winner == 0);

    int board2[6][7] = { 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 1, 1, 1, 1 }
    }; 
    winner = check_winner(board2);
    assert(winner == 1);

    int board3[6][7] = { 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 1, 0, 0, 0, 0 }, 
        { 0, 0, 1, 0, 0, 0, 0 }, 
        { 0, 0, 1, 0, 0, 0, 0 }, 
        { 0, 0, 1, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }
    }; 
    winner = check_winner(board3);
    assert(winner == 1);

    int board4[6][7] = { 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 1, 0, 0, 0, 0 }, 
        { 0, 0, 0, 1, 0, 0, 0 }, 
        { 0, 0, 0, 0, 1, 0, 0 }, 
        { 0, 0, 0, 0, 0, 1, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }
    }; 
    winner = check_winner(board4);
    assert(winner == 1);

    int board5[6][7] = { 
        { 0, 0, 0, 0, 0, 0, 1 }, 
        { 0, 0, 0, 0, 0, 1, 0 }, 
        { 0, 0, 0, 0, 1, 0, 0 }, 
        { 0, 0, 0, 1, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }
    }; 
    winner = check_winner(board5);
    assert(winner == 1);

    int board6[6][7] = { 
        { 0, 0, 1, 1, 0, 0, 0 }, 
        { 0, 0, 1, 1, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }
    }; 
    winner = check_winner(board6);
    assert(winner == 0);

    printf("Passed all winner tests.\n");
}

void sort_tests() {
    char all_players1[10][11] = {{"last"}, {"middle"}, {"first"}};
    int all_scores[10] = {1, 2, 3};
    int player_arr[2] = {0, 1};
    sort_names_scores(all_players1, all_scores, player_arr);
    show_stats(all_players1, all_scores);

    printf("Leaderboard ^\n\n");
}


void setup_tests() {
    int action;
    int players_exist;
    int next;
    char player0[11];
    char all_players[10][11] = {{"p1"}, {"p2"}, {"p3"}};
    int p1_set = 0;
    int p2_set = 0;
    int player_arr[2] = {9, 9};

    for (;;) {
        int next = next_available(all_players);

        action = player_screen(all_players, player_arr, next);

        if (action == ASSIGN_1 || action == ASSIGN_2) {
            temp_show_players(all_players, next);
            if (next > 0) {
                printf("Player %d choose from list: ", action + 1);
                int player_num = temp_select_player(all_players, next);
                if (player_num == 0) {
                    printf("Can't select that player. \n");
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
                temp_get_new_player(new_player);
                strcpy(all_players[next], new_player);
            }

        } else if (action == DELETE_PLAYER) {
            temp_show_players(all_players, next);
            if (next > 0) {
                printf("%s", "\nSelect player number to delete: ");
                int delete_number = temp_select_player(all_players, next);

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
            if (player_arr[0] == max_players || player_arr[1] == max_players) {
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
                    // CONFIRMED

                    // current_player = 0;
                    // selection = 4;

                    // state = CHOOSING;
                }
            }

        } else { // invalid
            printf("Unrecognized action.\n");
        }
    }
}
