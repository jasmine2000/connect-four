#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>

#include "setup.h"
#include "gameplay.h"
#include "output.h"
#include "leaderboard.h"



int main() {
    
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

    char all_players1[10][11] = {{"last"}, {"middle"}, {"first"}};
    int all_scores[10] = {1, 2, 3};
    sort_names_scores(all_players1, all_scores);
    show_stats(all_players1, all_scores);

    printf("Leaderboard ^\n\n");

    int action;
    int players_exist;
    int next;
    char player0[11];
    char all_players[10][11] = {{"p1"}, {"p2"}, {"p3"}};
    int p1_set = 0;
    int p2_set = 0;

    for (;;) {
        int next = next_available(all_players);
        if (next == 0) {
            players_exist = 0;
        } else {
            players_exist = 1;
        }

        action = player_screen(all_players, players_exist);

        if (action == 0 || action == 1) {
            int player_num = get_existing_player(all_players, action + 1, next);
            if (player_num == 0) {
                printf("Can't select that player. \n");
            } else {
                int player_index = player_num - 1;
                // PLAYER_ARR GETS SET HERE
                printf("player %d got set to %s", action + 1, all_players[player_index]);
            }

        } else if (action == 2) {
            if (next == 10) {
                printf("%s", "Can't add any more players. Delete one and try again. \n");
            } else {
                char new_player[11];
                get_new_player(new_player);
                strcpy(all_players[next], new_player);
            }

        } else if (action == 3) {
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
        } else if (action == 4) {


        } else {
            printf("Unrecognized action.\n");
        }
    }
}
