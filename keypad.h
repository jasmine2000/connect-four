#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern const int max_players;

const int keypad_map[16] = {
    1,  2,  3,  10, 
    4,  5,  6,  11,
    7,  8,  9,  12,
    20, 0,  21, 13
};

int get_keypad(int next) {
    int data_available;
    int keypad_index;
    int keypad_number;

    for (;;) {   
        data_available = data_available_Read();
        if (data_available == 1) {
            keypad_index = A_Read() + (B_Read() << 1) + (C_Read() << 2) + (D_Read() << 3);
        }
    }

    keypad_number = keypad_map[keypad_index];

    if (keypad_number > 0 && keypad_number <= next) {
        return keypad_number;
    } else {
        return 0;
    }
}
