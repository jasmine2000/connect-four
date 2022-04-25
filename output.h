#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern const int max_players;


void temp_printboard(int board[6][7], int preview, int player) {
    // prints out board
    int i, j;

    for (i = 1; i < 8; i++) {
        printf(" %d", i);
    }
    printf("\n");

    if (preview > 0 && preview < 8) {
        for (i = 1; i < preview; i ++) {
            printf("%s", "  ");
        }
        if (player == 1) {
            printf("%s", " R");
        } else if (player == 2) {
            printf("%s", " Y");
        }
    }
    printf("\n");
    
    for (i = 5; i >= 0; i--) {
        char line[100] = {0};
        for (j = 0; j < 7; j++) {
            if (board[i][j] == 0) {
                char buffer[10];
                sprintf(buffer, "|%c", ' ');
                strcat(line, buffer);

            } else if (board[i][j] == 1) {
                char buffer[10];
                sprintf(buffer, "|%c", 'R');
                strcat(line, buffer);

            } else if (board[i][j] == 2) {
                char buffer[10];
                sprintf(buffer, "|%c", 'Y');
                strcat(line, buffer);
            }
        }
        printf("%s|\n", line);
    }
}

