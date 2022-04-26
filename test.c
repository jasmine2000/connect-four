#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>

#include "setup.h"
#include "gameplay.h"
#include "output.h"
#include "leaderboard.h"

// constants
const int SETUP=0;
const int CHOOSING=1;
const int DROPPING=2;
const int LEADERBOARD=3;

const int ASSIGN_1 = 0;
const int ASSIGN_2 = 1;
const int ADD_PLAYER = 2;
const int DELETE_PLAYER = 3;
const int CONFIRM_PLAYERS = 4;
const int INVALID = 5;

// after keypad implement
// const int COLUMN_SELECT = 0; // gameplay
// const int PLAYER_SELECT = 1; // adding/deleting during setup
// const int OPTION_SELECT = 2; // choosing options during setup

const int max_players = 9;
const int name_length = 11;


void winner_tests();
void sort_tests();
void setup_tests();


int main() {

    winner_tests();

    sort_tests();
    
    return 0;
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
    temp_show_players(all_players1);

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
