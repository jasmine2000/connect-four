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
    // 3 for draw
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
                        if (board[i][j + k] != player && board[i][j + k] != 3) {
                            right = 0;
                            break;
                        }
                    }
                }
                if (right) return player;

                if (vertical) {
                    for (k = 1; k < 4; k++) {
                        if (board[i + k][j] != player && board[i + k][j] != 3) {
                            vertical = 0;
                            break;
                        }
                    }
                }
                if (vertical) return player;

                if (d_right) {
                    for (k = 1; k < 4; k++) {
                        if (board[i + k][j + k] != player && board[i + k][j + k] != 3) {
                            d_right = 0;
                            break;
                        }
                    }
                }
                if (d_right) return player;

                if (d_left) {
                    for (k = 1; k < 4; k++) {
                        if (board[i + k][j - k] != player && board[i + k][j - k] != 3) {
                            d_left = 0;
                            break;
                        }
                    }
                }
                if (d_left) return player;
            }
        }
    }

    // no winner, looking for full board
    for (i = 0; i < 7; i++) {
        if (board[5][i] == 0) return 0;
    }
    return 3;       // draw
}

int get_computer_column(int board[6][7]) {
    // will return a column that would result in anyone winning
    // if one doesn't exist, returns random column in range 7

    int row, col, winner_result;
    for (col = 0; col < 7; col++) {
        row = find_row(board, col);
        if (row == 6) continue;

        board[row][col] = 3;
        winner_result = check_winner(board);
        board[row][col] = 0;
        if (winner_result > 0) return col;
    }

    int random_num = rand();
    int random_col = (random_num % 7) + 1;
    return random_col;
}
