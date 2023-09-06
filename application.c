/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

volatile uint32 CCP1_Interrupt_flag;
volatile uint32 CCP2_Interrupt_flag;

timer3_t timer_obj;
ccpx_t capture1_obj;
ccpx_t capture2_obj;

void Timer3_DefaultInterruptHandler(void){
}
void CCP1_DefaultInterruptHandler(void){
    CCP1_Interrupt_flag++;
}
void CCP2_DefaultInterruptHandler(void){
    CCP2_Interrupt_flag++;
}

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    capture1_obj.CCPx_InterruptHandler = CCP1_DefaultInterruptHandler;
    capture1_obj.ccpx_inst = CCP1_INST;
    capture1_obj.ccp_capture_timer = CCP1_CCP2_TIMER3;
    capture1_obj.ccpx_mode = CCPx_CAPTURE_MODE_SELECTED;
    capture1_obj.ccpx_mode_varient = CCPx_CAPTURE_MODE_4_RISING_EDGE;
    capture1_obj.ccpx_pin.port = PORTC_INDEX;
    capture1_obj.ccpx_pin.pin = GPIO_PIN2;
    capture1_obj.ccpx_pin.direction = GPIO_DIRECTION_INPUT;
    ret = CCPx_Init(&capture1_obj);
    
    capture2_obj.CCPx_InterruptHandler = CCP2_DefaultInterruptHandler;
    capture2_obj.ccpx_inst = CCP2_INST;
    capture2_obj.ccp_capture_timer = CCP1_CCP2_TIMER3;
    capture2_obj.ccpx_mode = CCPx_CAPTURE_MODE_SELECTED;
    capture2_obj.ccpx_mode_varient = CCPx_CAPTURE_MODE_16_RISING_EDGE;
    capture2_obj.ccpx_pin.port = PORTC_INDEX;
    capture2_obj.ccpx_pin.pin = GPIO_PIN1;
    capture2_obj.ccpx_pin.direction = GPIO_DIRECTION_INPUT;
    ret = CCPx_Init(&capture2_obj);
    
    timer_obj.TMR3_InterruptHandler = Timer3_DefaultInterruptHandler;
    timer_obj.timer3_mode = TIMER3_TIMER_MODE;
    timer_obj.priority = INTERRUPT_LOW_PRIORITY;
    timer_obj.timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_1;
    timer_obj.timer3_preload_value = 0;
    timer_obj.timer3_reg_rw_mode = TIMER3_REG_RW_8BIT_MODE_ENABLED;
    Timer3_Init(&timer_obj);
    
    while(1){
    }
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
