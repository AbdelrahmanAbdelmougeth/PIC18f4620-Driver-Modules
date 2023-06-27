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
    ret = lcd_8bit_send_string(&_lcd_2, "Ahmed");
    ret = lcd_4bit_send_string(&_lcd_1, "Ahmed");
    while (1) {
        ret = lcd_8bit_send_string_pos(&_lcd_2, 2, 3, "ABDO");
        ret = lcd_4bit_send_string_pos(&_lcd_1, 2, 3, "ABDO");
    }
     
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}