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
        for(uint8 i=0; i<99; i++){
            uint8 BCD = (((uint8)(i % 10)) | ((uint8)(i / 10)) << 4);
            gpio_port_write_logic(PORTC_INDEX, BCD);
            __delay_ms(500);
        }  
    }
     
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = gpio_port_direction_initialize(PORTC_INDEX, GPIO_DIRECTION_OUTPUT);
}