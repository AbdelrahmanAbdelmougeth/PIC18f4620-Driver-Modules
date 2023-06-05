/* 
 * File:   ecu_led.h
 * Author: abdo9
 *
 * Created on May 15, 2023, 1:31 PM
 */

#include "ecu_led.h"

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_initialize(const led_t* led){
    Std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_obj ={
            .port = led->port_name, .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT, .logic = led->led_status
        };
        ret = gpio_pin_initialize(&pin_obj);
    }
    return ret;
}

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_turn_on(const led_t* led){
    Std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_obj ={
            .port = led->port_name, .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT, .logic = led->led_status
        };
        ret = gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;
}

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_turn_off(const led_t* led){
    Std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_obj ={
            .port = led->port_name, .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT, .logic = led->led_status
        };
        ret = gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_toggle(const led_t* led){
    Std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_obj ={
            .port = led->port_name, .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT, .logic = led->led_status
        };
        ret = gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}
