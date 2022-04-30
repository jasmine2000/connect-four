#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<tft.h>
#include<keyboard.h>

// flags
int confirm_flag;
int row_flag;

int h_index;
int v_index;

char keyboard[3][11] = {"qwertyuiop", "asdfghjkl<", "_zxcvbnm  "};

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

    // interrupt flags
    confirm_flag = 0;
    row_flag = 0;

    // init interrupts
    c_interrupt_StartEx(confirm_button_Handler);
    r_interrupt_StartEx(row_button_Handler);

    // init keyboard indices
    row_number = 0;
    h_index = 0;

    // for debugging only
    LCD_Char_1_Start();					// initialize lcd
	LCD_Char_1_ClearDisplay();

}

int keyboard_get_letter() {

    int letter_index;
    int prev_letter_index;

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

            letter_index = v_index * 10 + h_index;
            if (letter_index != prev_letter_index) {
                temp_update_keyboard(letter_index);
                prev_letter_index = letter_index;
            }
            
            CyDelay(50);									// delay in milliseconds
		}
    }
}

void keyboard_get_player(char player_name[11]) {
    keyboard_init();

    player_name[0] = '\0';
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

        temp_update_name(player_name);
    }
}


void temp_update_name(char player_name[11]) {
    UART_PutString(player_name);
    UART_PutCRLF(0);

}

void temp_update_keyboard() {
    char letter = keyboard[v_index][h_index];

    LCD_Position(0, 0);
    LCD_PrintString("     ");			// clean up the previous display
    LCD_Position(0, 0);
    LCD_PutChar(letter);

    // tft logic
    // draw keyboard
    // draw enter box
    // draw box around letter
}