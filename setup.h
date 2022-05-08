#ifndef SETUP_H
#define SETUP_H

#include<stdint.h>

extern const int ASSIGN_1;
extern const int ASSIGN_2;
extern const int ADD_PLAYER;
extern const int DELETE_PLAYER;
extern const int CONFIRM_PLAYERS;
extern const int INVALID;

extern const int max_players;
extern const int name_length;

void clear_board(int board[6][7]);

void do_delete(char all_players[10][11], int all_scores[max_players], int player_arr[2], int player_index);


void temp_show_players(char all_players[max_players][name_length]);

int temp_select_player(int next);

void temp_get_new_player(char new_player[name_length]);

int temp_confirm();

#endif