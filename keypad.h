#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern const int COLUMN_SELECT; // gameplay
extern const int PLAYER_SELECT; // adding/deleting during setup
extern const int OPTION_SELECT; // choosing options during setup

int get_keypress(int mode, int next);