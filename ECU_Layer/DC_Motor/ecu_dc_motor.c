/* 
 * File:   ecu_led.c
 * Author: abdo9
 *
 * Created on May 15, 2023, 1:31 PM
 */

#include "ecu_dc_motor.h"


Std_ReturnType dc_motor_initialize(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    if(dc_motor == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_initialize(&dc_motor->dc_motor_pins[DC_MOTOR_PIN_1]);
        ret = gpio_pin_initialize(&dc_motor->dc_motor_pins[DC_MOTOR_PIN_2]);
    }
    return ret;
}


Std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    if(dc_motor == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&dc_motor->dc_motor_pins[DC_MOTOR_PIN_1], GPIO_HIGH);
        ret = gpio_pin_write_logic(&dc_motor->dc_motor_pins[DC_MOTOR_PIN_2], GPIO_LOW);
    }
    return ret;
}


Std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    if(dc_motor == NULL){
        ret = E_NOT_OK;
    }else{
       ret = gpio_pin_write_logic(&dc_motor->dc_motor_pins[DC_MOTOR_PIN_1], GPIO_LOW);
       ret = gpio_pin_write_logic(&dc_motor->dc_motor_pins[DC_MOTOR_PIN_2], GPIO_HIGH);
    }
    return ret;
}


Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    if(dc_motor == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&dc_motor->dc_motor_pins[DC_MOTOR_PIN_1], GPIO_LOW);
        ret = gpio_pin_write_logic(&dc_motor->dc_motor_pins[DC_MOTOR_PIN_2], GPIO_LOW);
    }
    return ret;
}