#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "gameplay.h"


int find_row(int board[6][7], int col) {
    // returns index of lowest unoccupied row
    // returns 6 if all rows are occupied
    int i;
    for (i = 0; i < 6; i++) {
        if (board[i][col] == 0) {
            return i;
        }
    }
    return 6;
}

int check_winner(int board[6][7]) {
    // returns 0 if no one won
    // 1 if player 1 or 2 if player 2 won
    int i, j, k;
    int right, left, vertical;      // if enough space in directions to have four
    int d_right, d_left;
    int player;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            player = board[i][j];
            if (player != 0) {
                if (j + 3 <= 6) right = 1;
                if (j - 3 >= 0) left = 1;
                if (i + 3 <= 5) vertical = 1;
            
                d_right = right && vertical;
                d_left = left && vertical;

                if (right) {
                    for (k = 1; k < 4; k++) {
                        if (board[i][j + k] != player) {
                            right = 0;
                            break;
                        }
                    }
                }
                if (right) return player;

                if (vertical) {
                    for (k = 1; k < 4; k++) {
                        if (board[i + k][j] != player) {
                            vertical = 0;
                            break;
                        }
                    }
                }
                if (vertical) return player;

                if (d_right) {
                    for (k = 1; k < 4; k++) {
                        if (board[i + k][j + k] != player) {
                            d_right = 0;
                            break;
                        }
                    }
                }
                if (d_right) return player;

                if (d_left) {
                    for (k = 1; k < 4; k++) {
                        if (board[i + k][j - k] != player) {
                            d_left = 0;
                            break;
                        }
                    }
                }
                if (d_left) return player;
            }
        }
    }
    return 0;
}

