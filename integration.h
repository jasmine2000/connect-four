#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern const int max_players;

const int keypad_map[16] = {
    1,  2,  3,  10, 
    4,  5,  6,  11,
    7,  8,  9,  12,
    20, 0,  21, 13
}

int select_player_keypad(int next) {
    int data_a;
    int reading;
    int keypress;

    for (;;) {
        data_a = data_available_Read();
        if (data_a == 1) {
            reading = A_Read() + (B_Read() << 1) + (C_Read() << 2) + (D_Read() << 3);
            break;
        }
    }

    keypress = keypad_map[reading];

    if (keypress > 0 && keypress <= next) {
        return keypress;
    } else {
        return 0;
    }
}
