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
    
    const uint8 customChar[] = {
        0x0E,
        0x08,
        0x1E,
        0x00,
        0x08,
        0x08,
        0x08,
        0x08
    };
  
    ret = lcd_8bit_custom_char(&_lcd_2, 1, 1, customChar, 0);
    ret = lcd_4bit_custom_char(&_lcd_1, 1, 1, customChar, 0);
    while (1) {
       
    } 
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}