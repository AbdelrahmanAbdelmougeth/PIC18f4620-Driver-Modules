/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

button_t btn_high = {
    .button_pin.port = PORTC_INDEX,
    .button_pin.pin = GPIO_PIN2,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

button_t btn_low = {
    .button_pin.port = PORTD_INDEX,
    .button_pin.pin = GPIO_PIN0,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_HIGH,
    .button_connection = BUTTON_ACTIVE_LOW,
    .button_state = BUTTON_RELEASED
};

led_t led_1 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW
};

led_t led_2 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .led_status = GPIO_LOW
};

button_state_t btn_high_status = BUTTON_RELEASED;
button_state_t btn_low_status = BUTTON_RELEASED;

int main() {
    Std_ReturnType ret = E_NOT_OK;

    application_initialize();  
    
    
    while(1)
    {
        ret = button_read_state(&btn_high, &btn_high_status);
        ret = button_read_state(&btn_low, &btn_low_status);
        
        if(btn_high_status == BUTTON_PRESSED){
            ret = led_turn_on(&led_1);
        }else{
            ret = led_turn_off(&led_1);
        }
        
        if(btn_low_status == BUTTON_PRESSED){
            ret = led_turn_on(&led_2);
        }else{
            ret = led_turn_off(&led_2);
        }
    }

    return (EXIT_SUCCESS);
}

void application_initialize(){
    Std_ReturnType ret = E_NOT_OK;
    ret = button_initialize(&btn_high);
    ret = button_initialize(&btn_low);
    ret = led_initialize(&led_1);
    ret = led_initialize(&led_2);
}