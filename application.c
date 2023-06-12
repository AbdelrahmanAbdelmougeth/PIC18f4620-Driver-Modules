/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

uint8 Seven_Segment_Patterns[10] = {0xC0, 0xF9, 0xA4, 
                                    0xB0, 0x99, 0x92, 
                                    0x82, 0xF8, 0x80, 
                                    0x90};

int main() {
    Std_ReturnType ret = E_NOT_OK;

    application_initialize();

    while (1) {
        for(uint8 i=0; i<99; i++){
            uint8 temp = i;
            gpio_port_write_logic(PORTD_INDEX, Seven_Segment_Patterns[temp % 10]);
            temp /= 10;
            gpio_port_write_logic(PORTC_INDEX, Seven_Segment_Patterns[temp]);
            __delay_ms(500);
        }  
    }
     
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = gpio_port_direction_initialize(PORTC_INDEX, GPIO_DIRECTION_OUTPUT);
    ret = gpio_port_direction_initialize(PORTD_INDEX, GPIO_DIRECTION_OUTPUT);
}