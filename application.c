/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

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

led_t led_3 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .led_status = GPIO_LOW
};

////////////////////////////////////
led_t clock_pin = {
    .port_name = PORTA_INDEX,
    .pin = GPIO_PIN2,
    .led_status = GPIO_LOW
};
led_t latch_enable_pin = {
    .port_name = PORTA_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW
};
led_t data_pin = {
    .port_name = PORTA_INDEX,
    .pin = GPIO_PIN1,
    .led_status = GPIO_LOW
};

int main() {
    application_initialize();  
    
    while(1)
    {
        led_turn_on(&led_1);
        __delay_ms(50);
        led_turn_off(&led_1);
        led_turn_on(&led_2);
        __delay_ms(50);
        led_turn_off(&led_2);
        led_turn_on(&led_3);
        __delay_ms(50);
        led_turn_off(&led_3);
    }

    return (EXIT_SUCCESS);
}

void application_initialize(){
    Std_ReturnType ret = E_NOT_OK;
    ret = led_initialize(&led_1);
    ret = led_initialize(&led_2);
    ret = led_initialize(&led_3);
}