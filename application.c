/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

uint8 keypad_val = ZERO_INIT;

int main() {
    Std_ReturnType ret = E_NOT_OK;

    application_initialize();
    
    while (1) {
        ret = keypad_get_value(&keypad_1, &keypad_val);
    }
     
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}