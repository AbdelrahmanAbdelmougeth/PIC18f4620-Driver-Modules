/* 
 * File:   ecu_layer_init.h
 * Author: abdo9
 *
 * Created on June 24, 2023, 2:54 PM
 */


#include "ecu_layer_init.h"

keypad_t keypad_1 = {
    .keypad_row_pins[0].port = PORTB_INDEX,
    .keypad_row_pins[0].pin = GPIO_PIN0,
    .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[0].logic = GPIO_LOW,
    
    .keypad_row_pins[1].port = PORTB_INDEX,
    .keypad_row_pins[1].pin = GPIO_PIN1,
    .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].logic = GPIO_LOW,
    
    .keypad_row_pins[2].port = PORTB_INDEX,
    .keypad_row_pins[2].pin = GPIO_PIN2,
    .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].logic = GPIO_LOW,
    
    .keypad_row_pins[3].port = PORTB_INDEX,
    .keypad_row_pins[3].pin = GPIO_PIN3,
    .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].logic = GPIO_LOW,
    
    /*########################################################################*/
    
    .keypad_col_pins[0].port = PORTB_INDEX,
    .keypad_col_pins[0].pin = GPIO_PIN4,
    .keypad_col_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_col_pins[0].logic = GPIO_LOW,
    
    .keypad_col_pins[1].port = PORTB_INDEX,
    .keypad_col_pins[1].pin = GPIO_PIN5,
    .keypad_col_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_col_pins[1].logic = GPIO_LOW,
    
    .keypad_col_pins[2].port = PORTB_INDEX,
    .keypad_col_pins[2].pin = GPIO_PIN6,
    .keypad_col_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_col_pins[2].logic = GPIO_LOW,
    
    .keypad_col_pins[3].port = PORTB_INDEX,
    .keypad_col_pins[3].pin = GPIO_PIN7,
    .keypad_col_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_col_pins[3].logic = GPIO_LOW,
    
    
 
};

Std_ReturnType ecu_layer_initialize(){
    Std_ReturnType ret = E_NOT_OK;
    ret = keypad_initialize(&keypad_1);
    return ret;
}

