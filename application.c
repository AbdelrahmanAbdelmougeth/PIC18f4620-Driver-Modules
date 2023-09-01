/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

volatile uint16 timer_counter_val;
timer3_t counter_obj;

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    counter_obj.TMR3_InterruptHandler = NULL;
    counter_obj.priority = INTERRUPT_LOW_PRIORITY;
    counter_obj.timer3_mode = TIMER3_COUNTER_MODE;
    counter_obj.timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_1;
    counter_obj.timer3_preload_value = 0;
    counter_obj.timer3_reg_rw_mode = TIMER3_REG_RW_16BIT_MODE_ENABLED;
    counter_obj.timer3_counter_mode = TIMER3_SYNC_COUNTER_MODE;
    ret = Timer3_Init(&counter_obj);
    
    while(1){
        ret = Timer3_Read_Value(&counter_obj, &timer_counter_val);
    }
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
