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

#include "tft_board.h"
#include "GUI.h"

const int BOARDX = 15;
const int BOARDY = 100;
const int BOARDW = 210;
const int BOARDH = 180;

const int SIDELENGTH = 30;

const int my_red = GUI_BLUE;
const int my_blue = GUI_RED;
const int my_yellow = GUI_GREEN + GUI_BLUE;


void tft_init_board() 
{   
    GUI_SetColor(my_blue);
    GUI_FillRect(BOARDX, BOARDY, BOARDX + BOARDW, BOARDY + BOARDH);
    
    GUI_SetColor(GUI_GRAY);
    int i, j;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            int centerX = BOARDX + SIDELENGTH / 2 + j * SIDELENGTH;
            int centerY = BOARDY + SIDELENGTH / 2 + i * SIDELENGTH;
            GUI_FillCircle(centerX, centerY, SIDELENGTH / 3);
        }
    }
    
    char columns[] = "1234567";
    int numbers_x;
    int numbers_y = BOARDY - (SIDELENGTH * 3 / 2);
    for (i = 0; i < 7; i++) {
        numbers_x = BOARDX + SIDELENGTH / 2 + i * SIDELENGTH - 2;
        GUI_DispCharAt(columns[i], numbers_x, numbers_y);
    }
    GUI_SetColor(GUI_BLACK);
    
    GUI_DispStringAt("Press A to confirm column", BOARDX, BOARDY + BOARDH + SIDELENGTH / 2);
}

void tft_player_turn(char player_name[11]) {
    char message[30];
    sprintf(message, "%s: choose column", player_name);
    GUI_DispStringAt(message, BOARDX, SIDELENGTH / 2);
}

void tft_preview_choice(int column, int player_num) {
    GUI_SetColor(GUI_WHITE);
    GUI_COLOR chip_color;
    if (player_num == 0) {
        chip_color = my_red;
    } else {
        chip_color = my_yellow;
    }
    int i;
    int preview_x;
    int preview_y =  BOARDY - SIDELENGTH / 2;
    for (i = 0; i < 7; i++) {
        preview_x = BOARDX + SIDELENGTH / 2 + i * SIDELENGTH;
        if (column == i + 1) {
            GUI_SetColor(chip_color);
        }
        GUI_FillCircle(preview_x, preview_y, SIDELENGTH / 3);
        if (column == i + 1) {
            GUI_SetColor(GUI_WHITE);
        }
    }
    GUI_SetColor(GUI_BLACK);
}

void tft_drop_chip(int row, int column, int player_num) {
    GUI_COLOR chip_color;
    if (player_num == 0) {
        chip_color = my_red;
    } else {
        chip_color = my_yellow;
    }
    int centerX = BOARDX + SIDELENGTH / 2 + column * SIDELENGTH;
    int centerY = BOARDY + SIDELENGTH / 2 + (5 - row) * SIDELENGTH;
    GUI_SetColor(chip_color);
    GUI_FillCircle(centerX, centerY, SIDELENGTH / 3);
    GUI_SetColor(GUI_BLACK);
}

/* [] END OF FILE */
