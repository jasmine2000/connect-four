#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "setup.h"


void clear_board(int board[6][7]) {
    // makes board all zeros
    int i, j;
    for (i = 0; i < 6; i=i+1) {
        for (j = 0; j < 7; j++) {
            board[i][j] = 0;
        }
    }
}

void do_delete(char all_players[10][11], int all_scores[max_players], int player_arr[2], int player_index) {
    // delete player and shift all back
    int i, j;
    for (i = player_index + 1; i < max_players; i ++) {
        strcpy(all_players[i - 1], all_players[i]); // move everything one back
        all_scores[i - 1] = all_scores[i];
        for (j = 0; j < 2; j++) {
            if (player_arr[j] == i) {
                player_arr[j]--;
            }
        }
    }
    all_players[max_players - 1][0] = '\0';
    all_scores[max_players - 1] = 0;
    
    for (j = 0; j < 2; j++) {
        if (player_arr[j] == player_index) {
            player_arr[j] = max_players;
        }
    }
}

