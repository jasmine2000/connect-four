#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern const int max_players;

// SETUP
void tft_show_players(char all_players[max_players][11]) {
    // show player list
}

void tft_setup_screen(char all_players[max_players][11], int player_arr[2], int next) {

    tft_show_players(all_players);
    // if p1/p2 is not max_players, print on right

    // print instructions on bottom
}

void tft_choose_player() {
    // print instructions
    // call tft_show_players() in main.c
}

// SETUP / KEYBOARD
void tft_update_name(char player_name[11]) {
    // UART put name

    // tft logic
    // draw box with text
}

void tft_update_keyboard(int letter_index) {
    char letter = keyboard[int(letter_index / 10)][letter_index % 10];

    LCD_Char_1_Position(0, 6);
    LCD_Char_1_PrintString("     ");			// clean up the previous display
    LCD_Char_1_Position(0, 6);
    LCD_Char_1_PutChar(letter);

    // tft logic
    // draw keyboard
    // draw enter box
    // draw box around letter
}

// GAMEPLAY
void tft_init_board() {
    // blue box
    // 6 x 7 grey circles
    // show text above and below
}

void tft_update_preview(int column, int current_player) {
    // draw box above board
    // draw piece color above column
}

void tft_drop_piece(int row, int column, int current_player) {
    // draw circle at spot

    // update_current player
    // change name at top of screen
    // change some colors? - text in rectangle, diff color
}

// LEADERBOARD
void tft_leaderboard() {
    // text about leaderboard
    // call tft_show_players() in main.c
}