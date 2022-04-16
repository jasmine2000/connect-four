#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void printboard(int board[6][7]) {
    int i, j;
    for (int i = 0; i < 6; i++) {
        char line[100] = {0};
        for (int j = 0; j < 7; j++) {
            char buffer[10];
            sprintf(buffer, "|%d", board[i][j]);
            strcat(line, buffer);
        }
        printf("%s|\n", line);
    }
}

