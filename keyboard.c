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
#include<keyboard.h>
#include<tft_other.h>

#include "GUI.h"

// flags
int confirm_flag;
int row_flag;

int h_index;
int row_number;

const int keyboard_color = GUI_LIGHTRED;

const int KEYWIDTH = 20;
const int KEYHEIGHT = 30;
const int KEYBOARD_W = 200;
const int KEYBOARD_X = 20;
const int KEYBOARD_Y = 190;

GUI_RECT last_key;

char keyboard[3][11] = {"qwertyuiop", "asdfghjkl<", "_zxcvbnm  "};

void tft_init_keyboard();
void tft_update_name(char player[11]);
void tft_erase_last();
void tft_update_keyboard();

// INTERRUPTS
CY_ISR( confirm_button_Handler ) {
    confirm_flag = 1;
}

CY_ISR( row_button_Handler ) {
    row_flag = 1;
}


void keyboard_init() {
    // init ADC
    ADC_DelSig_1_Start();				// start the ADC_DelSig_1
	ADC_DelSig_1_StartConvert();		// start the ADC_DelSig_1 conversion

    // init interrupts
    c_interrupt_StartEx(confirm_button_Handler);
    r_interrupt_StartEx(row_button_Handler);
    
    // interrupt flags
    confirm_flag = 0;
    row_flag = 0;

    // init keyboard indices
    row_number = 0;
    h_index = 0;
    
    last_key = (LCD_RECT){
        .x0 = KEYBOARD_X, 
        .y0 = KEYBOARD_Y, 
        .x1 = KEYBOARD_X + KEYWIDTH, 
        .y1 = KEYBOARD_Y + KEYHEIGHT};
    
    tft_init_keyboard();
}

void keyboard_get_letter() {

    int letter_index;
    int prev_letter_index = 0;

    int adc_ready;
    int16 adcResult;
    
    for(;;) 
    {
        adc_ready = ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT);

        if (row_flag) {
            row_flag = 0;

            row_number ++;
            row_number = row_number % 3;
        }
        if (confirm_flag) {
            confirm_flag = 0;

            return;
        }

		if (adc_ready) {
			adcResult = ADC_DelSig_1_GetResult16();		// read the adc and assign the value adcResult 
            
            if (adcResult & 0x8000)
            {
                adcResult = 0;       // ignore negative ADC results
            }
            else if (adcResult >= 0xfff)
            {
                adcResult = 0xfff;      // ignore high ADC results
            }
            
            h_index = (int)(adcResult / 410);

            letter_index = row_number * 10 + h_index;
            if (letter_index != prev_letter_index) {
                tft_erase_last();
                tft_update_keyboard();
                prev_letter_index = letter_index;
            }
            
            CyDelay(50);									// delay in milliseconds
		}
    }
}

void keyboard_get_player(char player_name[11]) {
    keyboard_init();
    
    memset(player_name, 0, 11);
    char next_letter;
    int name_index = 0;
    for (;;) {
        keyboard_get_letter();
        next_letter = keyboard[row_number][h_index];

        if (next_letter == '<') {           // delete
            if (name_index > 0) {
                name_index --;
                player_name[name_index] = '\0';
            }

        } else if (next_letter == ' ') {    // finish
            tft_clear_screen();
            return;

        } else {
            if (next_letter == '_') {
                next_letter = ' ';
            }
            if (name_index < 10) {
                player_name[name_index] = next_letter;
                name_index ++;
            }
        }

        tft_update_name(player_name);
    }
}

void tft_init_keyboard() {
    GUI_SetColor(keyboard_color);
    GUI_FillRect(KEYBOARD_X, KEYBOARD_Y, KEYBOARD_X + KEYBOARD_W, KEYBOARD_Y + KEYHEIGHT * 3);
    
    GUI_SetBkColor(keyboard_color);
    GUI_SetColor(GUI_BLACK);
    int i, j;
    int charX, charY;
    for (i = 0; i < 3; i++) {
        charY = KEYBOARD_Y + KEYHEIGHT / 2 + KEYHEIGHT * i;
        for (j = 0; j < 10; j++) {
            charX = KEYBOARD_X + KEYWIDTH / 2 + j * KEYWIDTH - 2;
            if (i == 2 && j > 7) break;
            GUI_DispCharAt(keyboard[i][j], charX, charY);
        }
    }
    GUI_DispStringAt("enter", charX, charY);
    
    GUI_DrawRect(20, 145, 220, 175);
    GUI_SetBkColor(GUI_WHITE);
    GUI_DispStringAt("Enter new player:", KEYBOARD_X, KEYBOARD_Y / 2);
}

void tft_update_name(char player_name[11]) {
    GUI_RECT name_rect = (LCD_RECT){.x0 = 25, .y0 = 150, .x1 = 210, .y1 = 165};
    
    char displayed_name[21];
    sprintf(displayed_name, "%s          ", player_name);
    GUI_DispStringInRect(displayed_name, &name_rect, GUI_TA_LEFT | GUI_TA_VCENTER);
}

void tft_erase_last() {
    GUI_SetColor(keyboard_color);
    GUI_DrawRectEx(&last_key);
    GUI_SetColor(GUI_BLACK);
}

void tft_update_keyboard() {
    int rectX = KEYBOARD_X + h_index * KEYWIDTH;
    int rectY = KEYBOARD_Y + row_number * KEYHEIGHT;
    
    GUI_RECT new_key = (LCD_RECT){
            .x0 = rectX, 
            .y0 = rectY, 
            .x1 = rectX + KEYWIDTH, 
            .y1 = rectY + KEYHEIGHT};
    
    if (row_number == 2 && h_index > 7) {
        new_key.x0 = KEYBOARD_X + 8 * KEYWIDTH;
        new_key.x1 = KEYBOARD_X + 10 * KEYWIDTH;
    }
    
    GUI_DrawRectEx(&new_key);
    last_key = new_key;
    
}

/* [] END OF FILE */