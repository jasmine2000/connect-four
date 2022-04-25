#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include<stdint.h>

extern const int max_players;

void sort_names_scores(char all_players[max_players][11], int all_scores[max_players], int player_arr[2]);

#endif