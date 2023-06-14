/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

pin_config_t seg1_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW,
};
pin_config_t seg2_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN1,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW,
};
pin_config_t seg3_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN2,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW,
};
pin_config_t seg4_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN3,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW,
};
pin_config_t seg5_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN4,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW,
};
pin_config_t seg6_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN5,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW,
};
pin_config_t seg7_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN6,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW,
};
pin_config_t seg8_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN7,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW,
};

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
        uint8 number = 250;

        gpio_pin_write_logic(&seg8_enable, GPIO_HIGH);
        seven_segment_write_number(&segment_1, (uint8)number%10);
        __delay_ms(15);
        gpio_pin_write_logic(&seg8_enable, GPIO_LOW);
        number = number / 10;
        
        gpio_pin_write_logic(&seg7_enable, GPIO_HIGH);
        seven_segment_write_number(&segment_1, (uint8)number%10);
        __delay_ms(15);
        gpio_pin_write_logic(&seg7_enable, GPIO_LOW);
        number = number / 10;
        
        gpio_pin_write_logic(&seg6_enable, GPIO_HIGH);
        seven_segment_write_number(&segment_1, (uint8)number%10);
        __delay_ms(15);
        gpio_pin_write_logic(&seg6_enable, GPIO_LOW);
    }
     
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    
    ret = gpio_pin_initialize(&seg1_enable);
    ret = gpio_pin_initialize(&seg2_enable);
    ret = gpio_pin_initialize(&seg3_enable);
    ret = gpio_pin_initialize(&seg4_enable);
    ret = gpio_pin_initialize(&seg5_enable);
    ret = gpio_pin_initialize(&seg6_enable);
    ret = gpio_pin_initialize(&seg7_enable);
    ret = gpio_pin_initialize(&seg8_enable);
    
    ret = seven_segment_initialize(&segment_1);
}