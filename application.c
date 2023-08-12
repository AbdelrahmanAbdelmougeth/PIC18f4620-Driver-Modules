/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

led_t led1 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW
};
led_t led2 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .led_status = GPIO_LOW
};
led_t led3 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .led_status = GPIO_LOW
};

void Int0_APP_ISR(void){
    led_toggle(&led1);
    __delay_ms(250);
}
void Int1_APP_ISR(void){
    led_toggle(&led2);
    __delay_ms(250);
}
void Int2_APP_ISR(void){
    led_toggle(&led3);
    __delay_ms(250);    
}

interrupt_INTx_t int0_obj = {
    .EXT_InterruptHandler = Int0_APP_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT0,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN0,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};
interrupt_INTx_t int1_obj = {
    .EXT_InterruptHandler = Int1_APP_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_LOW_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT1,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN1,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};
interrupt_INTx_t int2_obj = {
    .EXT_InterruptHandler = Int2_APP_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT2,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN2,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    ret = Interrupt_INTx_Init(&int0_obj);
    ret = Interrupt_INTx_Init(&int1_obj);
    ret = Interrupt_INTx_Init(&int2_obj);
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
