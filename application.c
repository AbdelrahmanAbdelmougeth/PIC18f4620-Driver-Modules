/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

void loading_screen(void){
    lcd_8bit_send_string_pos(&_lcd_2, 1,1, "Loading");
    __delay_ms(150);
    while(1){
    lcd_8bit_send_string_pos(&_lcd_2, 1,8, ".  ");
    __delay_ms(150);
    lcd_8bit_send_string_pos(&_lcd_2, 1,8, ".. ");
    __delay_ms(150);
    lcd_8bit_send_string_pos(&_lcd_2, 1,8, "...");
    __delay_ms(150);
    }
}


int main() {
    Std_ReturnType ret = E_NOT_OK;

    application_initialize();
    
    while (1) {
        loading_screen();
    }
     
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}