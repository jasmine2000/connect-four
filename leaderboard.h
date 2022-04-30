#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include<stdint.h>

#define max_players 9
#define name_length 11

void sort_names_scores(char all_players[max_players][11], int all_scores[max_players], int player_arr[2]);

#endif