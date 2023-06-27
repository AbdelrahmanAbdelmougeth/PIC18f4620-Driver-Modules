/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"


int main() {
    Std_ReturnType ret = E_NOT_OK;

    application_initialize();
    
    
    while (1) {
        ret = lcd_8bit_send_string_pos(&_lcd_2,1,1, "Abdelrahman Fathi");
        ret = lcd_4bit_send_string_pos(&_lcd_1, 1, 1, "Ahmed");
        ret = lcd_4bit_send_command(&_lcd_1, _LCD_DISPLAY_SHIFT_RIGHT);
        __delay_ms(250);
        ret = lcd_4bit_send_command(&_lcd_1, _LCD_DISPLAY_SHIFT_RIGHT);
        __delay_ms(250);
        ret = lcd_4bit_send_command(&_lcd_1, _LCD_DISPLAY_SHIFT_LEFT);
        __delay_ms(250);
        ret = lcd_4bit_send_command(&_lcd_1, _LCD_DISPLAY_SHIFT_LEFT);
        __delay_ms(250);
    }
     
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}