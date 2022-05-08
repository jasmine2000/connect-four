#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern const int max_players;

extern const int COLUMN_SELECT; // gameplay
extern const int PLAYER_SELECT; // adding/deleting during setup
extern const int OPTION_SELECT; // choosing options during setup
extern const int CONFIRM_SELECT;    // confirming a choice
extern const int GAME_SELECT;       // game type

const int keypad_map[16] = {
    1,  2,  3,  10, 
    4,  5,  6,  11,
    7,  8,  9,  12,
    20, 0,  21, 13
};

int get_keypress(int mode, int next) {

    int data_available;
    int keypad_index;
    int key;

    for (;;) {   
        data_available = data_available_Read();
        if (data_available == 1) {
            keypad_index = A_Read() + (B_Read() << 1) + (C_Read() << 2) + (D_Read() << 3);
            break;
        }
    }

    key = keypad_map[keypad_index];
    
    if (mode == COLUMN_SELECT) {            // 1-7, D, *
        if ((key >= 1 && key <= 7) || key == 13 || key == 20) {
            return key;
        } else {
            return 0;
        }

    } else if (mode == PLAYER_SELECT) {     // 1-next
        if (key > 0 && key <= next) {
            return key;
        } else {
            return 0;
        }

    } else if (mode == OPTION_SELECT) {     // 0-2, A-C, *
        if (key == 1 || key == 2 || (key >= 10 && key <= 12) || key == 20 || key == 30) {
            return key;
        } else {
            return 0;
        }

    } else if (mode == CONFIRM_SELECT) {    // C only
        if (key == 12) {
            return 1;
        } else {
            return 0;
        }

    } else if (mode == GAME_SELECT) {       // 1 or 2
        if (key == 1 || key == 2) {
            return key;
        } else {
            return 0;
        }
    }
    return 0;
}
