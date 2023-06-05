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
    
    gpio_port_direction_initialize(PORTA_INDEX, GPIO_DIRECTION_OUTPUT);
    
    
    while(1)
    {
        /*
        led_turn_on(&led_1);
        __delay_ms(50);
        led_turn_off(&led_1);
        led_turn_on(&led_2);
        __delay_ms(50);
        led_turn_off(&led_2);
        led_turn_on(&led_3);
        __delay_ms(50);
        led_turn_off(&led_3);
        
        */
        
        send_data(0b00000000);
        __delay_ms(200);
        send_data(0b10000000);
        __delay_ms(200);
        send_data(0b01000000);
        __delay_ms(200);
        send_data(0b00100000);
        __delay_ms(200);
        send_data(0b00010000);
        __delay_ms(200);
        send_data(0b00001000);
        __delay_ms(200);
        send_data(0b00000100);
        __delay_ms(200);
        send_data(0b00000010);
        __delay_ms(200);
        send_data(0b00000001);
        __delay_ms(200);
        
    }

    return (EXIT_SUCCESS);
}

void application_initialize(){
    Std_ReturnType ret = E_NOT_OK;
    ret = led_initialize(&led_1);
    ret = led_initialize(&led_2);
    ret = led_initialize(&led_3);
    
    ret = led_initialize(&clock_pin);
    ret = led_initialize(&latch_enable_pin);
    ret = led_initialize(&data_pin);
}

void clock_signal(void){
   led_turn_on(&clock_pin);
   __delay_us(500);
   led_turn_off(&clock_pin);
   __delay_us(500);
}

void latch_enable(void){
   led_turn_on(&latch_enable_pin);
   __delay_us(500);
   led_turn_off(&latch_enable_pin);
}

void send_data(uint8 data_out){
    for (uint8 i=0 ; i<8 ; i++)
    {
        if(((data_out >> i) & (0x01)) == 0x01){
            led_turn_on(&data_pin);
            clock_signal();
        }else{
            led_turn_off(&data_pin);
            clock_signal();
        }
    }
    latch_enable(); // Data finally submitted
}