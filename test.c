#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>

#include "setup.h"
#include "gameplay.h"
#include "output.h"



int main() {
    
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

    printf("Passed all tests!\n");
}
