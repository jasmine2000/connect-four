/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<project.h>

#include "tft_setup.h"
#include "GUI.h"

const int list_x = 20;
const int list_y = 35;
const int row_h = 20;
const int row_w = 150;
const int options_w = 220;
const int options_x = 10;
const int options_y = 235;
const int option_num_w = 10;


void tft_clear_bottom() {
    GUI_SetColor(GUI_WHITE);
    GUI_FillRect(0, options_y, 240, 320);
    GUI_SetColor(GUI_BLACK);
}

void tft_show_players(char all_players[max_players][name_length], int next) {
    int writeX = list_x;
    int writeY = list_y - row_h / 2 - 3;
    
    if (next == 0) { // next available index
        GUI_DispStringAt("No players yet", writeX, writeY);
        return;
    } else {
        GUI_DispStringAt("Here are the current players", writeX, writeY);
    }
    
    GUI_COLOR background = GUI_LIGHTGREEN;
    
    GUI_SetColor(background);
    GUI_FillRect(list_x, list_y, list_x + row_w, list_y + max_players * row_h);
    GUI_SetColor(GUI_BLACK);
    GUI_DrawRect(list_x, list_y, list_x + row_w, list_y + max_players * row_h);
    
    GUI_SetBkColor(background);
    
    char player[name_length + 5];
    int i;
    
    writeX = list_x + 5;
    for (i = 0; i < max_players; i ++) {
        memset(player, 0, sizeof player);
        sprintf(player, "%d. %s", i + 1, all_players[i]);
        
        writeY = list_y + row_h / 2 + i * row_h - 3;
        GUI_DispStringAt(player, writeX, writeY);
        GUI_DrawLine(list_x, list_y + i * row_h, list_x + row_w, list_y + i * row_h);
    }
}

void tft_reassign(int player_arr[2]) {
    GUI_COLOR player_highlight = GUI_LIGHTCYAN;
    
    int i, j;
    int writeX, writeY;
    writeX = list_x + row_w + 5;
    for (i = 0; i < max_players; i ++) {
        writeY = list_y + row_h / 2 + i * row_h - 3;
        GUI_DispStringAt("   ", writeX + row_w, writeY); // clear previous
        
        for (j = 0; j < 2; j++) {
            if (player_arr[j] == i) {
                char p_num[5];
                sprintf(p_num, "P%d", j + 1);
                GUI_SetBkColor(player_highlight);
                GUI_DispStringAt(p_num, writeX, writeY);
                GUI_SetBkColor(GUI_WHITE);
            }
        }
    }

}

void tft_show_options(int game_type) {
    GUI_COLOR background = GUI_LIGHTMAGENTA;
    GUI_SetColor(background);
    GUI_FillRect(options_x, options_y, options_x + options_w, options_y + 3 * row_h);
    GUI_SetColor(GUI_BLACK);
    GUI_DrawRect(options_x, options_y, options_x + options_w, options_y + 3 * row_h);
    
    GUI_SetBkColor(background);
    
    int i;
    for (i = 1; i < 3; i++) {
        GUI_DrawLine(options_x, options_y + i * row_h, options_x + options_w, options_y + i * row_h);
    }
    
    GUI_DrawLine(options_x + options_w / 2, options_y, options_x + options_w / 2, options_y + 3 * row_h);
    for (i = 0; i < 2; i++) {
        int xVal = options_x + i * options_w / 2 + option_num_w;
        GUI_DrawLine(xVal, options_y, xVal, options_y + 3 * row_h);
    }
    
    char option_nums[] = "012ABC";
    char option_msg[6][20] = {{"Help"}, {"Assign P1"}, {"Assign P2"}, {"Add Player"}, {"Delete Player"}, {"Confirm Players"}};
    
    int j;
    int writeX, writeY;
    for (i = 0; i < 2; i++) {
        writeX = options_x + i * options_w / 2 + 3;
        for (j = 0; j < 3; j++) {
            writeY = options_y + row_h / 2 + j * row_h - 3;
            GUI_DispCharAt(option_nums[i * 3 + j], writeX, writeY);
            GUI_DispStringAt(option_msg[i * 3 + j], writeX + option_num_w, writeY);
        }
    }
    GUI_SetBkColor(GUI_WHITE);

    if (game_type == 1) {
        GUI_SetColor(GUI_WHITE);
        GUI_FillRect(options_x, options_y + 2 * row_h, options_x + optioons_w / 2, options_y + 3 * row_h);
        GUI_SetColor(GUI_BLACK);
    }
}



/* [] END OF FILE */
