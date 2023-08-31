/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

led_t led1 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

volatile uint16 timer2_val = 0;

void Timer2_DefaultInterruptHandler(void){
    timer2_val++;
    led_toggle(&led1);
}

 timer1_t  counter_obj;

void timer2_timer_init(void){
    timer2_t timer_obj;
    timer_obj.TMR2_InterruptHandler = Timer2_DefaultInterruptHandler;
    timer_obj.priority = INTERRUPT_LOW_PRIORITY;
    timer_obj.timer2_postscaler_value = TIMER2_POSTSCALER_DIV_BY_16;
    timer_obj.timer2_prescaler_value = TIMER2_PRESCALER_DIV_BY_1;
    timer_obj.timer2_preload_value = 249;
    Timer2_Init(&timer_obj);
}

int main() {
    Std_ReturnType ret = E_NOT_OK;
    
    led_initialize(&led1);
    timer2_timer_init();
      
    while(1){
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
