/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

dc_motor_t dc_motor_1 = {
    .dc_motor_pins[DC_MOTOR_PIN_1].port = PORTC_INDEX,
    .dc_motor_pins[DC_MOTOR_PIN_1].pin = GPIO_PIN0,
    .dc_motor_pins[DC_MOTOR_PIN_1].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pins[DC_MOTOR_PIN_1].logic = DC_MOTOR_OFF_STATUS,
    
    .dc_motor_pins[DC_MOTOR_PIN_2].port = PORTC_INDEX,
    .dc_motor_pins[DC_MOTOR_PIN_2].pin = GPIO_PIN1,
    .dc_motor_pins[DC_MOTOR_PIN_2].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pins[DC_MOTOR_PIN_2].logic = DC_MOTOR_OFF_STATUS,
};

dc_motor_t dc_motor_2 = {
    .dc_motor_pins[DC_MOTOR_PIN_1].port = PORTC_INDEX,
    .dc_motor_pins[DC_MOTOR_PIN_1].pin = GPIO_PIN2,
    .dc_motor_pins[DC_MOTOR_PIN_1].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pins[DC_MOTOR_PIN_1].logic = DC_MOTOR_OFF_STATUS,
    
    .dc_motor_pins[DC_MOTOR_PIN_2].port = PORTC_INDEX,
    .dc_motor_pins[DC_MOTOR_PIN_2].pin = GPIO_PIN3,
    .dc_motor_pins[DC_MOTOR_PIN_2].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pins[DC_MOTOR_PIN_2].logic = DC_MOTOR_OFF_STATUS,
};

int main() {
    Std_ReturnType ret = E_NOT_OK;

    application_initialize();

    while (1) {
        ret = dc_motor_move_right(&dc_motor_1);
        ret = dc_motor_move_right(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_stop(&dc_motor_1);
        ret = dc_motor_stop(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_move_left(&dc_motor_1);
        ret = dc_motor_move_left(&dc_motor_2);
        __delay_ms(3000);
    }
     
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = dc_motor_initialize(&dc_motor_1);
    ret = dc_motor_initialize(&dc_motor_2);
}