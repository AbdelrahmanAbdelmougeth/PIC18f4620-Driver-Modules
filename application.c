/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

led_t led0 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW
};
led_t led1 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .led_status = GPIO_LOW
};
led_t led2 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .led_status = GPIO_LOW
};
led_t led3 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN3,
    .led_status = GPIO_LOW
};

void RB4_HIGH_APP_ISR(void){
    led_toggle(&led0);
}
void RB4_LOW_APP_ISR(void){
    led_toggle(&led1);
}

void RB5_HIGH_APP_ISR(void){
    led_toggle(&led0);
}
void RB5_LOW_APP_ISR(void){
    led_toggle(&led1);
}

void RB6_HIGH_APP_ISR(void){
    led_toggle(&led2);
}
void RB6_LOW_APP_ISR(void){
    led_toggle(&led3);
}

void RB7_HIGH_APP_ISR(void){
    led_toggle(&led2);
}
void RB7_LOW_APP_ISR(void){
    led_toggle(&led3);
}


interrupt_RBx_t int_RB4_obj = {
    .EXT_InterruptHandler_HIGH = RB4_HIGH_APP_ISR,
    .EXT_InterruptHandler_LOW = RB4_LOW_APP_ISR,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN4,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};
interrupt_RBx_t int_RB5_obj = {
    .EXT_InterruptHandler_HIGH = RB5_HIGH_APP_ISR,
    .EXT_InterruptHandler_LOW = RB5_LOW_APP_ISR,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN5,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};
interrupt_RBx_t int_RB6_obj = {
    .EXT_InterruptHandler_HIGH = RB6_HIGH_APP_ISR,
    .EXT_InterruptHandler_LOW = RB6_LOW_APP_ISR,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN6,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};
interrupt_RBx_t int_RB7_obj = {
    .EXT_InterruptHandler_HIGH = RB7_HIGH_APP_ISR,
    .EXT_InterruptHandler_LOW = RB7_LOW_APP_ISR,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN7,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    ret = Interrupt_RBx_Init(&int_RB4_obj);
    ret = Interrupt_RBx_Init(&int_RB5_obj);
    ret = Interrupt_RBx_Init(&int_RB6_obj);
    ret = Interrupt_RBx_Init(&int_RB7_obj);
    ret = led_initialize(&led0);
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = led_initialize(&led3);
    
    while (1) {
    } 
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
