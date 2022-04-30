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

#ifndef max_players
    #define max_players 9
#endif
#ifndef name_length
    #define name_length 11
#endif


void tft_clear_bottom();

void tft_show_players(char all_players[max_players][name_length], int next);

void tft_reassign(int player_arr[2]);

void tft_show_options();



/* [] END OF FILE */
