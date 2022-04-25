#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include<stdint.h>

extern const int name_length;

int temp_get_input(char player[11]);

int find_row(int board[6][7], int col);

int check_winner(int board[6][7]);

#endif