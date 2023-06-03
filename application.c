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

pin_config_t btn_1 = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_DIRECTION_INPUT,
    .logic = GPIO_LOW
};

Std_ReturnType ret = E_NOT_OK;
logic_t btn_1_logic; 
uint8 portc_direction_status;
uint8 portc_logic_status;

int main() {
    application_initialize();
    while(1)
    {
        /*
        ret = gpio_pin_write_logic(&led_2, GPIO_HIGH);
        ret = gpio_pin_write_logic(&led_3, GPIO_HIGH);
        __delay_ms(150);
        ret = gpio_pin_write_logic(&led_2, GPIO_LOW);
        ret = gpio_pin_write_logic(&led_3, GPIO_LOW);
        __delay_ms(150);
         */
         
        /*ret = gpio_pin_toggle_logic(&led_2);
        ret = gpio_pin_toggle_logic(&led_3);
        __delay_ms(150);
        
        ret = gpio_pin_read_logic(&btn_1, &btn_1_logic);
        if(btn_1_logic == GPIO_HIGH)
        {
           ret = gpio_pin_write_logic(&led_1, GPIO_HIGH);
        }
        else
        {
           ret = gpio_pin_write_logic(&led_1, GPIO_LOW);
        }
         */
        ret = gpio_port_toggle_logic(PORTC_INDEX);
        __delay_ms(250);
    }

    return (EXIT_SUCCESS);
}

void application_initialize(){
    //ret = gpio_pin_initialize(&led_1);
    //ret = gpio_pin_initialize(&led_2);
    //ret = gpio_pin_initialize(&led_3);
    ret = gpio_port_direction_initialize(PORTC_INDEX, 0x00);
    ret = gpio_port_get_direction_status(PORTC_INDEX, &portc_direction_status);
    
    ret = gpio_port_write_logic(PORTC_INDEX, 0x55);
    ret = gpio_port_read_logic(PORTC_INDEX, &portc_logic_status);
    __delay_ms(5000);
    ret = gpio_port_write_logic(PORTC_INDEX, 0xAA);
    ret = gpio_port_read_logic(PORTC_INDEX, &portc_logic_status);
}