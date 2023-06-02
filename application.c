/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"


pin_config_t led_1 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

pin_config_t led_2 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

pin_config_t led_3 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

Std_ReturnType ret = E_NOT_OK;
int main() {
 
    ret = gpio_pin_direction_initialize(&led_1);
    ret = gpio_pin_write_logic(&led_1, GPIO_HIGH);
    
    ret = gpio_pin_direction_initialize(&led_2);
    ret = gpio_pin_write_logic(&led_2, GPIO_HIGH);
    
    ret = gpio_pin_direction_initialize(&led_3);
    ret = gpio_pin_write_logic(&led_3, GPIO_HIGH);
    while(1)
    {
    }

    return (EXIT_SUCCESS);
}

