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
    ret = lcd_8bit_send_string_pos(&_lcd_2, 2,1, "Abdelrahman Fathi");
    ret = lcd_4bit_send_string_pos(&_lcd_1, 2, 1, "Ahmed");
    
    uint8 lcd1_counter=3;
    while (1) {
        for(lcd1_counter; lcd1_counter<=10; lcd1_counter++){
            ret = lcd_4bit_send_string_pos(&_lcd_1, 1, lcd1_counter, "Hello All"); 
            __delay_ms(100);
            ret = lcd_4bit_send_char_data_pos(&_lcd_1, 1, lcd1_counter, ' ');
        }
        for(lcd1_counter=10; lcd1_counter>=5; lcd1_counter--){
            ret = lcd_4bit_send_string_pos(&_lcd_1, 1, lcd1_counter, "Hello All"); 
            __delay_ms(100);
            ret = lcd_4bit_send_char_data_pos(&_lcd_1, 1, lcd1_counter+8, ' ');
        }
    }
     
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}