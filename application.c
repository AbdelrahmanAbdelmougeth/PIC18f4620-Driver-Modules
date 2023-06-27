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
        ret = lcd_8bit_send_char_data_pos(&_lcd_2, 1,5, 'A');
        ret = lcd_8bit_send_char_data_pos(&_lcd_2, 2,1, 'B');
        ret = lcd_8bit_send_char_data_pos(&_lcd_2, 3,5, 'C');
        ret = lcd_8bit_send_char_data_pos(&_lcd_2, 4,1, 'D');
    }
     
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}