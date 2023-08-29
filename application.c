/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};

volatile uint8 timer0_250ms = 0, timer0_500ms = 0;

void Timer0_DefaultInterruptHandler(void){
    timer0_250ms = 1;
    timer0_500ms++;
}

timer0_t timer0_timer_obj = {
    .TMR0_InterruptHandler = Timer0_DefaultInterruptHandler,
    .timer0_mode = TIMER0_TIMER_MODE,
    .timer0_register_size = TIMER0_16BIT_REGISTER_ENABLED,
    .prescaler_enable = TIMER0_PRESCALER_ENABLED,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_4,
    .timer0_preload_value = 3036
};

int main() {
    Std_ReturnType ret = E_NOT_OK;
    
    ret = Timer0_Init(&timer0_timer_obj);
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    
    while(1){
        if(timer0_250ms == 1){
            timer0_250ms = 0;
            led_toggle(&led1);
        }
        else {/* Nothing */}
        
        if(timer0_500ms == 2){
            led_toggle(&led2);
            timer0_500ms = 0;
        }
        else {/* Nothing */}
    }
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
