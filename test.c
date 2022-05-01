#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>

#include "setup.h"
#include "gameplay.h"
#include "leaderboard.h"
#include "fake_tft.h"

// gameplay constants
#define HOME        0
#define SETUP       1
#define CHOOSING    2
#define DROPPING    3
#define LEADERBOARD 4

#define ASSIGN_1        1
#define ASSIGN_2        2
#define ADD_PLAYER      10
#define DELETE_PLAYER   11
#define CONFIRM_PLAYERS 12
#define GO_BACK         20

const int COLUMN_SELECT = 0; // gameplay
const int PLAYER_SELECT = 1; // adding/deleting during setup
const int OPTION_SELECT = 2; // choosing options during setup
const int CONFIRM_SELECT = 3; // confirmation
const int GAME_SELECT = 4;      // select game type


void computer_column_tests();
void winner_tests();
void sort_tests();
void setup_tests();


int main() {
    computer_column_tests();

    winner_tests();

    sort_tests();
    
    return 0;
}

void computer_column_tests() {
    int column;
    int board[6][7] = { 
        { 0, 0, 0, 1, 0, 0, 0 }, 
        { 0, 0, 0, 1, 0, 0, 0 }, 
        { 0, 0, 0, 1, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }
    }; 
    column = get_computer_column(board);
    assert(column == 4);

    int board2[6][7] = { 
        { 0, 0, 2, 1, 1, 1, 0 }, 
        { 0, 0, 0, 2, 1, 1, 0 }, 
        { 0, 0, 0, 0, 2, 1, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }
    }; 
    column = get_computer_column(board);
    assert(column == 4);

    printf("Passed all computer tests.\n");
}


void winner_tests() {
    // board
    int board[6][7];
    int winner;

    clear_board(board);
    winner = check_winner(board);
    assert(winner == 0);

    int board2[6][7] = { 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 1, 1, 1, 1 }
    }; 
    winner = check_winner(board2);
    assert(winner == 1);

    int board3[6][7] = { 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 1, 0, 0, 0, 0 }, 
        { 0, 0, 1, 0, 0, 0, 0 }, 
        { 0, 0, 1, 0, 0, 0, 0 }, 
        { 0, 0, 1, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }
    }; 
    winner = check_winner(board3);
    assert(winner == 1);

    int board4[6][7] = { 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 1, 0, 0, 0, 0 }, 
        { 0, 0, 0, 1, 0, 0, 0 }, 
        { 0, 0, 0, 0, 1, 0, 0 }, 
        { 0, 0, 0, 0, 0, 1, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }
    }; 
    winner = check_winner(board4);
    assert(winner == 1);

    int board5[6][7] = { 
        { 0, 0, 0, 0, 0, 0, 1 }, 
        { 0, 0, 0, 0, 0, 1, 0 }, 
        { 0, 0, 0, 0, 1, 0, 0 }, 
        { 0, 0, 0, 1, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }
    }; 
    winner = check_winner(board5);
    assert(winner == 1);

    int board6[6][7] = { 
        { 0, 0, 1, 1, 0, 0, 0 }, 
        { 0, 0, 1, 1, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }, 
        { 0, 0, 0, 0, 0, 0, 0 }
    }; 
    winner = check_winner(board6);
    assert(winner == 0);

    printf("Passed all winner tests.\n");
}

void sort_tests() {
    char all_players1[10][11] = {{"last"}, {"middle"}, {"first"}};
    int all_scores1[10] = {1, 2, 3};
    int player_arr1[2] = {0, 1};
    sort_names_scores(all_players1, all_scores1, player_arr1);
    tft_show_players(all_players1, 3);

    char all_players2[10][11] = {
        {"player1"}, {"player2"}, {"player3"}, 
        {"player4"}, {"player5"}, {"player6"}, 
        {"player7"}, {"player8"}, {"player9"}};
    int all_scores2[10] = {0, 0, 0, 0, 0, 0, 0, 2, 3};
    int player_arr2[2] = {7, 8};
    sort_names_scores(all_players2, all_scores2, player_arr2);

    for (int i = 0; i < 9; i++) {
        printf("%s\t", all_players2[i]);
        printf("%d\n", all_scores2[i]);
    }
    printf("\nplayer_arr: {%d, %d}\n\n", player_arr2[0], player_arr2[1]);

    printf("Leaderboard Tests\n\n");
}
