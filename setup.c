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

void do_delete(char all_players[10][11], int player_arr[2], int player_index) {
    // delete player and shift all back
    for (int i = player_index + 1; i < 10; i ++) {
        strcpy(all_players[i - 1], all_players[i]); // move everything one back
    }
    all_players[9][0] = '\0';
}

