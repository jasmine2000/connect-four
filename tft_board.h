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

#include "GUI.h"

const int BOARDX = 15;
const int BOARDY = 100;
const int BOARDW = 210;
const int BOARDH = 180;

const int SIDELENGTH = 30;

const int my_red = GUI_BLUE;
const int my_blue = GUI_RED;
const int my_yellow = GUI_GREEN + GUI_BLUE;


void tft_init_board();

void tft_player_turn(char player_name[11]);

void tft_preview_choice(int column, int player_num);

void tft_drop_chip(int row, int column, int player_num);

/* [] END OF FILE */
