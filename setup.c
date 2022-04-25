#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "setup.h"

extern const int max_players;


void clear_board(int board[6][7]) {
    // makes board all zeros
    int i, j;
    for (i = 0; i < 6; i=i+1) {
        for (j = 0; j < 7; j++) {
            board[i][j] = 0;
        }
    }
}

int next_available(char all_players[max_players][name_length]) {
    // returns next available index
    int i;
    char player[name_length];
    for (i = 0; i < max_players; i++) {
        memset(player, 0, sizeof player);
        strcpy(player, all_players[i]);
        if (player[0] == '\0') {
            return i;
        }
    }
    return max_players; 
}

void temp_show_players(char all_players[max_players][name_length]) {
    char player[name_length];
    int i;
    for (i = 0; i < max_players; i ++) {
        memset(player, 0, sizeof player);
        strcpy(player, all_players[i]); // get player at index

        if (player[0] == '\0') {        // if empty
            break;
        }
        printf("%d. %s\n", i + 1, player);
    }
    printf("\n");
}

int player_screen(char all_players[max_players][name_length], int player_arr[2], int next) {
    // display player screen
    // allow user to choose next step
    if (next == 0) { // next available index
        printf("%s", "No players yet. \n\n");
    } else {
        printf("%s", "Here are the current players. \n");
        temp_show_players(all_players);
    }
    
    printf("%s", "Current Assignments:\n");
    char player1[name_length];
    char player2[name_length];
    if (player_arr[0] < max_players) {
        strcpy(player1, all_players[player_arr[0]]);
    } else {
        strcpy(player1, "");
    }
    if (player_arr[1] < max_players) {
        strcpy(player2, all_players[player_arr[1]]);
    } else {
        strcpy(player2, "");
    }
    printf("Player 1: %s\n", player1);
    printf("Player 2: %s\n\n", player2);

    
    printf("%s", "Press\n1 \t Assign player 1\n2 \t Assign player 2\n");
    printf("%s", "a \t Add a new player\n");
    printf("%s", "b \t Delete an existing player\n");
    printf("%s", "c \t Begin gameplay!\n");
    
    printf("\n");

    char buffer[3];
    fgets(buffer, 3, stdin);
    printf("\n");
    char input = buffer[0];

    if (input == '1') return ASSIGN_1;
    else if (input == '2') return ASSIGN_2;
    else if (input == 'a') return ADD_PLAYER;
    else if (input == 'b') return DELETE_PLAYER;
    else if (input == 'c') return CONFIRM_PLAYERS;
    else return INVALID;
}

int temp_select_player(int next) {
    // selects existing player

    char buffer[3];
    fgets(buffer, 3, stdin);
    int num = buffer[0] - '0';

    if (num > 0 && num <= next) {
        return num;
    } else {
        return 0;
    }
}

void temp_get_new_player(char new_player[name_length]) {
    // gets a player name, puts in new_player
    printf("%s", "Enter new player's name: ");
    char buffer[name_length];

    fgets(buffer, 10, stdin);
    printf("\n");
    buffer[strcspn(buffer, "\n")] = 0;  // remove newline
    buffer[10] = '\0';

    strcpy(new_player, buffer);
}

int temp_confirm() {
    // reused function to confirm something from user
    // returns 1 to confirm choice and 0 otherwise

    printf("(y/n) ");

    char buffer[3];
    fgets(buffer, 3, stdin);
    printf("\n");
    buffer[strcspn(buffer, "\n")] = 0;  // remove newline

    if (strcmp(buffer, "y") == 0) return 1;
    else return 0;
}

void do_delete(char all_players[10][11], int player_index) {
    // delete player and shift all back
    for (int i = player_index + 1; i < 10; i ++) {
        strcpy(all_players[i - 1], all_players[i]); // move everything one back
    }
    all_players[9][0] = '\0';
}

