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

#include "tft_other.h"
#include "GUI.h"

#ifndef max_players
    #define max_players 9
#endif
#ifndef name_length
    #define name_length 11
#endif

const int SCREENX = 240;
const int SCREENY = 320;

extern const int my_red;
extern const int my_yellow;
extern const int my_blue;


void tft_clear_screen() {
    GUI_SetColor(GUI_WHITE);
    GUI_FillRect(0, 0, SCREENX, SCREENY);
    GUI_SetColor(GUI_BLACK);
}

void tft_win_message(int winner, char winner_name[11]) {
    GUI_RECT win_rect = (LCD_RECT){.x0 = 40, .y0 = 50, .x1 = 200, .y1 = 220};
    GUI_COLOR win_color;
    if (winner == 0) {
        win_color = my_red;
    } else if (winner == 1) {
        win_color = my_yellow;
    } else {
        win_color = my_blue;
    }
    
    GUI_SetColor(win_color);
    GUI_SetBkColor(win_color);
    GUI_FillRectEx(&win_rect);
    GUI_SetColor(GUI_BLACK);
    
    char win_msg[20];
    if (strlen(winner_name) == 0) {
        strcpy(win_msg, "DRAW");
    } else {
        sprintf(win_msg, "%s won!", winner_name);
    }
    GUI_SetFont(&GUI_Font8x16);
    GUI_DispStringInRect(win_msg, &win_rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    GUI_SetBkColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font6x8);
}

void tft_show_home() {
    int radius = 20;
    int logo_x = 60;
    int logo_y = 80;
    int logo_w = 120;

    int text_width = 8;
    int text_height = 16;
    int text_y = logo_y + radius - text_height / 2;
    
    int instruction_y = logo_y + 3 * radius;

    GUI_SetColor(my_red);
    GUI_FillRoundedRect(logo_x, logo_y, logo_x + logo_w, logo_y + 2 * radius, radius);
    
    GUI_SetFont(&GUI_Font8x16);
    GUI_SetColor(my_yellow);
    GUI_SetBkColor(my_red);
    GUI_DispStringAt("Connect", logo_x + radius, text_y);

    GUI_FillCircle(logo_x + logo_w - radius, logo_y + radius, radius - 3);
    
    GUI_SetColor(my_red);
    GUI_SetBkColor(my_yellow);
    GUI_DispCharAt('4', logo_x + logo_w - radius - text_width / 2, text_y);
    
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);

    GUI_SetFont(&GUI_Font6x8);
    GUI_DrawRoundedRect(logo_x, instruction_y, logo_x + logo_w, instruction_y + 3 * radius, 3);
    
    int writeX = logo_x + 6;
    int writeY = instruction_y + 6;
    GUI_DispStringAt("Press", writeX, writeY);
    
    writeY = writeY + radius;
    GUI_DispStringAt("1\tSingle Player", writeX, writeY);
    GUI_DrawCircle(writeX + 2, writeY + 4, 6);
    
    writeY = writeY + radius;
    GUI_DispStringAt("2\tTwo Player", writeX, instruction_y + 2 * radius + 6);
    GUI_DrawCircle(writeX + 2, writeY + 4, 6);
    
    GUI_SetFont(&GUI_Font6x8);
}



/* [] END OF FILE */
