#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include<stdint.h>

extern const int name_length;

int find_row(int board[6][7], int col);

int check_winner(int board[6][7]);

int get_computer_column(int board[6][7]);

#endif