/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

volatile uint16 PushButtonCounter = 0;

void Timer0_DefaultInterruptHandler(void){
    
}

timer0_t timer0_counter_obj = {
    .TMR0_InterruptHandler = Timer0_DefaultInterruptHandler,
    .timer0_mode = TIMER0_COUNTER_MODE,
    .source_edge_select = TIMER0_INCREMENT_ON_FALLING_EDGE,
    .timer0_register_size = TIMER0_16BIT_REGISTER_ENABLED,
    .prescaler_enable = TIMER0_PRESCALER_DISABLED,
    .timer0_preload_value = 0
};

int main() {
    Std_ReturnType ret = E_NOT_OK;
    
    ret = Timer0_Init(&timer0_counter_obj);
    ret = led_initialize(&led1);
    
    while(1){
        ret = Timer0_Read_Value(&timer0_counter_obj, &PushButtonCounter);
        if(PushButtonCounter == 5){
            led_turn_on(&led1);
        }
        else{
            led_turn_off(&led1);
        }
    }
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
