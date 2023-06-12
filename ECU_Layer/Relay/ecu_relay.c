/* 
 * File:   ecu_led.c
 * Author: abdo9
 *
 * Created on May 15, 2023, 1:31 PM
 */

#include "ecu_relay.h"

/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_initialize(const relay_t* relay){
    Std_ReturnType ret = E_OK;
    if(relay == NULL){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_obj ={
            .port = relay->relay_port_name, .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT, .logic = relay->relay_status
        };
        ret = gpio_pin_initialize(&pin_obj);
    }
    return ret;
}

Std_ReturnType relay_turn_on(const relay_t* relay){
    Std_ReturnType ret = E_OK;
    if(relay == NULL){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_obj ={
            .port = relay->relay_port_name, .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT, .logic = relay->relay_status
        };
        ret = gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;
}

Std_ReturnType relay_turn_off(const relay_t* relay){
    Std_ReturnType ret = E_OK;
    if(relay == NULL){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_obj ={
            .port = relay->relay_port_name, .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT, .logic = relay->relay_status
        };
        ret = gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}

Std_ReturnType relay_toggle(const relay_t* relay){
    Std_ReturnType ret = E_OK;
    if(relay == NULL){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_obj ={
            .port = relay->relay_port_name, .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT, .logic = relay->relay_status
        };
        ret = gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}