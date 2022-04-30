
#define max_players 9
#define name_length 11

void tft_clear_screen();
void tft_clear_bottom();

void tft_show_options();
void tft_reassign(int player_arr[2]);

void tft_show_players(char all_players[max_players][name_length], int num_players);

// gui
void GUI_DispStringAt();

// hardware
int get_keypress(int mode, int next);
void keyboard_get_player(char new_player[name_length]);

void error();

void tft_init_board();

void tft_player_turn(char player_name[11]);

void tft_preview_choice(int column, int player_num);

void tft_drop_chip(int row, int column, int player_num);

void tft_win_message(char player_name[11]);
