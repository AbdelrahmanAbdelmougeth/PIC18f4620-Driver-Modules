/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

led_t led1 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

volatile uint16 timer1_val = 0;
volatile uint16 counter_val = 0;

void Timer1_DefaultInterruptHandler(void){
    timer1_val++;
    led_toggle(&led1);
}

 timer1_t  counter_obj;

void timer1_timer_init(void){
    timer1_t  timer_obj;
    timer_obj.TMR1_InterruptHandler = Timer1_DefaultInterruptHandler;
    timer_obj.priority = INTERRUPT_LOW_PRIORITY;
    timer_obj.timer1_mode = TIMER1_TIMER_MODE;
    timer_obj.timer1_prescaler_value = TIMER1_PRESCALER_DIV_BY_8;
    timer_obj.timer1_preload_value = 15536;
    timer_obj.timer1_reg_rw_mode = TIMER1_REG_RW_16BIT_MODE_ENABLED;
    Timer1_Init(&timer_obj);
}

void timer1_counter_init(void){
   
   
}


int main() {
    Std_ReturnType ret = E_NOT_OK;
    
    led_initialize(&led1);
    //timer1_timer_init();
    timer1_counter_init();
    
    counter_obj.TMR1_InterruptHandler = Timer1_DefaultInterruptHandler;
    counter_obj.priority = INTERRUPT_LOW_PRIORITY;
    counter_obj.timer1_mode = TIMER1_COUNTER_MODE;
    counter_obj.timer1_counter_mode = TIMER1_SYNC_COUNTER_MODE;
    counter_obj.timer1_prescaler_value = TIMER1_PRESCALER_DIV_BY_1;
    counter_obj.timer1_preload_value = 0;
    counter_obj.timer1_reg_rw_mode = TIMER1_REG_RW_16BIT_MODE_ENABLED;
    Timer1_Init(&counter_obj);
    
    while(1){
        Timer1_Read_Value(&counter_obj, &counter_val);
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
