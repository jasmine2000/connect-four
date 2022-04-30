#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "fake_tft.h"


extern const int COLUMN_SELECT;
extern const int PLAYER_SELECT;
extern const int OPTION_SELECT;
extern const int CONFIRM_SELECT;


void tft_clear_screen() {}

void tft_show_options() {
    printf("%s", "Press\n1 \t Assign player 1\n2 \t Assign player 2\n");
    printf("%s", "a \t Add a new player\n");
    printf("%s", "b \t Delete an existing player\n");
    printf("%s", "c \t Begin gameplay!\n");
    
    printf("\n");
}

void tft_clear_bottom() {}

void GUI_DispStringAt(char dispString[50], int x, int y) {
    printf("%s\n\n", dispString);
}

void tft_reassign(int player_arr[2]) {
    printf("%s", "Current Assignments:\n");
    char player1[name_length];
    char player2[name_length];
    if (player_arr[0] < max_players) {
        sprintf(player1, "%d", player_arr[0]);
    } else {
        strcpy(player1, "");
    }
    if (player_arr[1] < max_players) {
        sprintf(player2, "%d", player_arr[1]);
    } else {
        strcpy(player2, "");
    }
    printf("Player 1: %s\n", player1);
    printf("Player 2: %s\n\n", player2);
}

void tft_show_players(char all_players[max_players][name_length], int num_players) {
    // display player screen
    // allow user to choose next step
    if (num_players == 0) { // next available index
        printf("%s", "No players yet. \n\n");
    } else {
        printf("%s", "Here are the current players. \n");
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
}


int get_keypress(int mode, int next) {

    char buffer[3];
    fgets(buffer, 3, stdin);
    printf("\n");
    buffer[strcspn(buffer, "\n")] = 0;  // remove newline

    int key;

    if (strcmp(buffer, "a") == 0) key = 10;
    else if (strcmp(buffer, "b") == 0) key = 11;
    else if (strcmp(buffer, "c") == 0) key = 12;
    else if (strcmp(buffer, "d") == 0) key = 13;
    else {
        key = buffer[0] - '0';
    }
    
    if (mode == COLUMN_SELECT) {
        if (key >= 1 && key <= 7 || key == 13) {
            return key;
        } else {
            return 0;
        }

    } else if (mode == PLAYER_SELECT) {
        if (key > 0 && key <= next) {
            return key;
        } else {
            return 0;
        }

    } else if (mode == OPTION_SELECT) {
        if (key == 1 || key == 2 || (key >= 10 && key <= 12)) {
            return key;
        } else {
            return 0;
        }

    } else if (mode == CONFIRM_SELECT) {
        if (key == 12) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

void keyboard_get_player(char new_player[name_length]) {
    // gets a player name, puts in new_player
    printf("%s", "Enter new player's name: ");
    char buffer[name_length];

    fgets(buffer, 10, stdin);
    printf("\n");
    buffer[strcspn(buffer, "\n")] = 0;  // remove newline
    buffer[10] = '\0';

    strcpy(new_player, buffer);
}

void error() {
    printf("You can't do that\n\n");
}

void tft_init_board() {};

void tft_player_turn(char player_name[11]) {
    printf("%s turn:\n", player_name);
}

void tft_preview_choice(int column, int player_num) {
    printf("%d\n", column);
};

void tft_drop_chip(int row, int column, int player_num) {};

void tft_win_message(char player_name[11]) {
    printf("%s won!\n", player_name);
}

