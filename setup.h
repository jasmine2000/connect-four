#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void clear_board(int board[6][7]) {
    // makes board all zeros
    int i, j;
    for (i = 0; i < 6; i=i+1) {
        for (j = 0; j < 7; j++) {
            board[i][j] = 0;
        }
    }
}

void get_player(char new_player[11]) {
    // gets a player name, puts in new_player
    char buffer[11];

    fgets(buffer, 11, stdin);
    buffer[strcspn(buffer, "\n")] = 0;  // remove newline

    strcpy(new_player, buffer);
}

int find_player(char new_player[11], char all_players[10][11]) {
    // if new_player in all_players return index
    // else return next available index
    for (int i = 0; i < 10; i=i+1) {
        char player[11] = {0};
        strcpy(player, all_players[i]); // get player at index

        if (player[0] == '\0') {        // if empty
            return i;
        } else if (strcmp(player, new_player) == 0) {   // if same
            return i;
        }
    }
    return 0; // change this later
}
        
