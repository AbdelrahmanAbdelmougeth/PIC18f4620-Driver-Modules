/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

volatile uint32 timer3_on;

led_t led1 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

void Timer3_DefaultInterruptHandler(void){
    timer3_on++;
    led_toggle(&led1);
}

void timer3_timer_init(void){
    timer3_t timer_obj;
    timer_obj.TMR3_InterruptHandler = Timer3_DefaultInterruptHandler;
    timer_obj.priority = INTERRUPT_LOW_PRIORITY;
    timer_obj.timer3_mode = TIMER3_TIMER_MODE;
    timer_obj.timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_8;
    timer_obj.timer3_preload_value = 15536;
    timer_obj.timer3_reg_rw_mode = TIMER3_REG_RW_16BIT_MODE_ENABLED;
    Timer3_Init(&timer_obj);
}



int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    timer3_timer_init();
    ret = led_initialize(&led1);
    
    while(1){
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
