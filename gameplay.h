#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int get_input(char player[11]) {
    // gets input from player
    // returns number 1-7
    // 0 if invalid, 8 if "drop", 9 if "exit game"
    printf("Player %s enter a column: ", player);
    char buffer[3];
    fgets(buffer, 3, stdin);
    buffer[strcspn(buffer, "\n")] = 0;  // remove newline

    char input = buffer[0];

    if (input == 'd') return 8;         // drop

    else if (input == 'e') return 9;    // exit game

    else {
        int num = input - '0';
        if (num > 0 && num < 8) return num;         // valid col
        else return 0;
    }
}

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
    return 0;
}

int early_exit() {
    // asks user again if they want to exit
    // returns 0 to continue and 1 to exit game

    printf("Are you sure you want to exit (y/n): ");

    char buffer[3];
    fgets(buffer, 3, stdin);
    buffer[strcspn(buffer, "\n")] = 0;  // remove newline

    if (strcmp(buffer, "y") == 0) return 1;
    else return 0;
}

