/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

ccpx_t compare_obj;
timer3_t timer_obj;

volatile uint8 signal_high_flag = 0;

void Timer3_DefaultInterruptHandler(void){
}

void CCP1_DefaultInterruptHandler(void){
    Std_ReturnType ret = E_NOT_OK;
    
    ret = Timer3_Write_Value(&timer_obj, 0);
    
    if(signal_high_flag == 1){
        signal_high_flag = 0;
        ret = CCPx_Compare_Mode_Write_Value(&compare_obj, (uint16)12500);
        CCP1_SET_MODE(CCPx_COMPARE_MODE_SET_PIN_HIGH);
    }else if(signal_high_flag == 0){
        signal_high_flag = 1;
        ret = CCPx_Compare_Mode_Write_Value(&compare_obj, (uint16)37500);
        CCP1_SET_MODE(CCPx_COMPARE_MODE_SET_PIN_LOW);
    }
}

void CCP2_DefaultInterruptHandler(void){
}

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    compare_obj.CCPx_InterruptHandler = CCP1_DefaultInterruptHandler;
    compare_obj.ccpx_inst = CCP1_INST;
    compare_obj.ccpx_mode = CCPx_COMPARE_MODE_SELECTED;
    compare_obj.ccpx_mode_varient = CCPx_COMPARE_MODE_SET_PIN_LOW;
    compare_obj.ccp_capture_timer = CCP1_CCP2_TIMER3;
    compare_obj.ccpx_pin.port = PORTC_INDEX;
    compare_obj.ccpx_pin.pin = GPIO_PIN2;
    compare_obj.ccpx_pin.direction = GPIO_DIRECTION_OUTPUT;
    
    ret = CCPx_Compare_Mode_Write_Value(&compare_obj, (uint16)37500);
    ret = CCPx_Init(&compare_obj);
    
    timer_obj.TMR3_InterruptHandler = NULL;
    timer_obj.timer3_mode = TIMER3_TIMER_MODE;
    timer_obj.priority = INTERRUPT_LOW_PRIORITY;
    timer_obj.timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_1;
    timer_obj.timer3_preload_value = 0;
    timer_obj.timer3_reg_rw_mode = TIMER3_REG_RW_16BIT_MODE_ENABLED;
    Timer3_Init(&timer_obj);
    
    while(1){
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
