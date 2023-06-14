/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

segment_t segment_1 = {
    .segment_pins[SEGMENT_PIN0].port = PORTC_INDEX,
    .segment_pins[SEGMENT_PIN0].pin = GPIO_PIN0,
    .segment_pins[SEGMENT_PIN0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[SEGMENT_PIN0].logic = GPIO_LOW,
    
    .segment_pins[SEGMENT_PIN1].port = PORTC_INDEX,
    .segment_pins[SEGMENT_PIN1].pin = GPIO_PIN1,
    .segment_pins[SEGMENT_PIN1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[SEGMENT_PIN1].logic = GPIO_LOW,
    
    .segment_pins[SEGMENT_PIN2].port = PORTC_INDEX,
    .segment_pins[SEGMENT_PIN2].pin = GPIO_PIN2,
    .segment_pins[SEGMENT_PIN2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[SEGMENT_PIN2].logic = GPIO_LOW,
    
    .segment_pins[SEGMENT_PIN3].port = PORTC_INDEX,
    .segment_pins[SEGMENT_PIN3].pin = GPIO_PIN3,
    .segment_pins[SEGMENT_PIN3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[SEGMENT_PIN3].logic = GPIO_LOW,
    
    .segment_type = COMMON_ANODE_SEGMENT
};

int main() {
    Std_ReturnType ret = E_NOT_OK;

    application_initialize();

    while (1) {
        for(uint8 i=0; i<10; i++){
            seven_segment_write_number(&segment_1, i);
            __delay_ms(220);
        }     
    }
     
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = seven_segment_initialize(&segment_1);
}