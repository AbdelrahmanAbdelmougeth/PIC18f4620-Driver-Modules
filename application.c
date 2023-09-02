/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

timer2_t timer_obj;
ccpx_t ccp1_obj;
ccpx_t ccp2_obj;
uint8 PWM_DUTY_CYCLE = 0;

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    ccp1_obj.ccpx_inst = CCP1_INST;
    ccp1_obj.CCPx_InterruptHandler = NULL;
    ccp1_obj.ccpx_mode = CCPx_PWM_MODE_SELECTED;
    ccp1_obj.ccpx_mode_varient = CCPx_PWM_MODE;
    ccp1_obj.PWM_frequency = 20000;
    ccp1_obj.ccpx_pin.port = PORTC_INDEX;
    ccp1_obj.ccpx_pin.pin = GPIO_PIN2;
    ccp1_obj.ccpx_pin.direction = GPIO_DIRECTION_OUTPUT;
    ccp1_obj.timer2_postscaler_value = CCPx_TIMER2_POSTSCALER_DIV_BY_1;
    ccp1_obj.timer2_prescaler_value = CCPx_TIMER2_PRESCALER_DIV_BY_1;    
    ret = CCPx_Init(&ccp1_obj);
    
    ccp2_obj.ccpx_inst = CCP2_INST;
    ccp2_obj.CCPx_InterruptHandler = NULL;
    ccp2_obj.ccpx_mode = CCPx_PWM_MODE_SELECTED;
    ccp2_obj.ccpx_mode_varient = CCPx_PWM_MODE;
    ccp2_obj.PWM_frequency = 20000;
    ccp2_obj.ccpx_pin.port = PORTC_INDEX;
    ccp2_obj.ccpx_pin.pin = GPIO_PIN1;
    ccp2_obj.ccpx_pin.direction = GPIO_DIRECTION_OUTPUT;
    ccp2_obj.timer2_postscaler_value = CCPx_TIMER2_POSTSCALER_DIV_BY_1;
    ccp2_obj.timer2_prescaler_value = CCPx_TIMER2_PRESCALER_DIV_BY_1;    
    ret = CCPx_Init(&ccp2_obj);
    
    timer_obj.TMR2_InterruptHandler = NULL;
    timer_obj.timer2_postscaler_value = TIMER2_POSTSCALER_DIV_BY_1;
    timer_obj.timer2_prescaler_value = TIMER2_PRESCALER_DIV_BY_1;
    timer_obj.timer2_preload_value = 0;
    ret = Timer2_Init(&timer_obj);
    
    CCPx_PWM_Set_Duty(&ccp1_obj, 50);
    CCPx_PWM_Start(&ccp1_obj);
    
    CCPx_PWM_Set_Duty(&ccp2_obj, 70);
    CCPx_PWM_Start(&ccp2_obj);
     
    while(1){
//        for (PWM_DUTY_CYCLE = 0; PWM_DUTY_CYCLE < 100; PWM_DUTY_CYCLE += 5){
//            __delay_ms(5);
//            CCPx_PWM_Set_Duty(&ccp1_obj, PWM_DUTY_CYCLE);
//        } 
//        for (PWM_DUTY_CYCLE = 0; PWM_DUTY_CYCLE < 100; PWM_DUTY_CYCLE += 5){
//            __delay_ms(5);
//            CCPx_PWM_Set_Duty(&ccp2_obj, PWM_DUTY_CYCLE);
//        } 
    }
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
