#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern const int max_players;

const int keypad_map[16] = {
    1,  2,  3,  10, 
    4,  5,  6,  11,
    7,  8,  9,  12,
    20, 0,  21, 13
};
    
char keyboard[3][11] = {"qwertyuiop", "asdfghjkl<", " zxcvbnm  "};

int select_player_keypad(int next) {
    int data_a;
    int reading;
    int keypress;

    for (;;) {
        data_a = data_available_Read();
        if (data_a == 1) {
            reading = A_Read() + (B_Read() << 1) + (C_Read() << 2) + (D_Read() << 3);
            break;
        }
    }

    keypress = keypad_map[reading];

    if (keypress > 0 && keypress <= next) {
        return keypress;
    } else {
        return 0;
    }
}

int get_letter() {
    int v_index;
    int h_index;

    int old_button;
    int button;

    int adc_ready;
    
	unsigned char j = 50;				// milliseconds delay
	
	
	LCD_Char_1_Start();					// initialize lcd
	LCD_Char_1_ClearDisplay();
	LCD_Char_1_PrintString("ADC : ");
	
	ADC_DelSig_1_Start();				// start the ADC_DelSig_1
	ADC_DelSig_1_StartConvert();		// start the ADC_DelSig_1 conversion


    for(;;)
    {
        adc_ready = ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT);
        button = read_button();

        if (!button && old_button) { // button released
            v_index ++;
            v_index = v_index % 3;
        }
        
		if (adc_ready) {
			LCD_Char_1_Position(0, 6);
			LCD_Char_1_PrintString("     ");			// clean up the previous display
			LCD_Char_1_Position(0, 6);
			adcResult = ADC_DelSig_1_GetResult16();		// read the adc and assign the value adcResult 
            
            if (adcResult & 0x8000)
            {
                adcResult = 0;       // ignore negative ADC results
            }
            else if (adcResult >= 0xfff)
            {
                adcResult = 0xfff;      // ignore high ADC results
            }
            
            // LCD_Char_1_PrintNumber(adcResult);
            h_index = (int)(adcResult / 410);
            LCD_Char_1_PutChar(keyboard[v_index][h_index]);
            
            CyDelay(j);									// delay in milliseconds
		}
    }
}




    
    
