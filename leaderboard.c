#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "leaderboard.h"

void sort_names_scores(char all_players[max_players][11], int all_scores[max_players], int player_arr[2]) {
    // sorts all players and scores from 
    // highest to lowest
    int i, j, k;
    int sorted;
    char lastplayer[11];
    char player[11];

    for (i = 0; i < max_players - 1; i++) {
        sorted = 1;
        memset(lastplayer, 0, sizeof lastplayer);
        strcpy(lastplayer, all_players[0]); // first player

        for (j = 1; j < max_players; j++) {
            memset(player, 0, sizeof player);
            strcpy(player, all_players[j]); // get player at index
            if (player[0] == '\0') {        // if empty
                break;
            }
            if (all_scores[j] > all_scores[j - 1]) {
                strcpy(all_players[j], lastplayer); // swap players
                strcpy(all_players[j - 1], player);

                int temp = all_scores[j];           // swap scores
                all_scores[j] = all_scores[j - 1];
                all_scores[j - 1] = temp;

                sorted = 0;
                // lastplayer is same

                for (k = 0; k < 2; k ++) {
                    if (player_arr[k] == j) {
                        player_arr[k] = j - 1;
                    } else if (player_arr[k] == j - 1) {
                        player_arr[k] = j;
                    }
                }

            } else {
                memset(lastplayer, 0, sizeof lastplayer);
                strcpy(lastplayer, player);
            }
        }
        if (sorted == 1) break;
    }
}
