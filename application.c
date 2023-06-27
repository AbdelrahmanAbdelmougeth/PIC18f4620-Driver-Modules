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
    
    uint8 number = 244;
    uint8 number_txt[4];
    
    ret = convert_byte_to_string(number, number_txt);
    ret = lcd_4bit_send_string_pos(&_lcd_1, 1, 1, "Counter: ");
    ret = lcd_4bit_send_string_pos(&_lcd_1, 1, 10, number_txt);
    while (1) {
       
    } 
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}