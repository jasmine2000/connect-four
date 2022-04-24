#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char keyboard[3][11] = {"qwertyuiop", "asdfghjkl<", " zxcvbnm  "};

void get_player(char player_name[11]) {

    ADC_DelSig_1_Start();				// start the ADC_DelSig_1
	ADC_DelSig_1_StartConvert();		// start the ADC_DelSig_1 conversion

    player_name[0] = '\0';
    char next_letter;
    int index = 0;
    int letter_index;
    for (;;) {
        letter_index = get_letter();
        next_letter = keyboard[int(letter_index / 10)][letter_index % 10];

        if (next_letter == '<') {           // delete
            if (index > 0) {
                player_name[index] = '\0';
                index --;
            }
        } else if (next_letter == ' ') {    // finish
            return;
        } else {
            player_name[index] = next_letter;
            index ++;
        }

        show_name(player_name);
    }
}

void show_name(char player_name[11]) {
    // UART put name

    // tft logic
    // draw box with text at same index
}

int row_button_press() {
    return 0;
}

int confirm_button_press() {
    return 0;
}

int get_letter() {
    int v_index;
    int h_index;

    int letter_index;
    int prev_letter_index;

    int adc_ready;
    
	unsigned char j = 50;				// milliseconds delay

    for(;;) 
    {
        adc_ready = ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT);

        if (row_button_press()) {
            v_index ++;
            v_index = v_index % 3;
        }
        if (confirm_button_press()) {
            return letter_index;
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
                show_keyboard(letter_index);
                prev_letter_index = letter_index;
            }
            
            CyDelay(j);									// delay in milliseconds
		}
    }
}

void lcd_init() {
    LCD_Char_1_Start();					// initialize lcd
	LCD_Char_1_ClearDisplay();
}

void show_keyboard(int letter_index) {
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




    
    
