/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

timer2_t timer_obj;
ccp1_t ccp1_obj;
uint8 PWM_DUTY_CYCLE = 0;

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    ccp1_obj.CCP1_InterruptHandler = NULL;
    ccp1_obj.ccp1_mode = CCP1_PWM_MODE_SELECTED;
    ccp1_obj.ccp1_mode_varient = CCP1_PWM_MODE;
    ccp1_obj.PWM_frequency = 20000;
    ccp1_obj.ccp_pin.port = PORTC_INDEX;
    ccp1_obj.ccp_pin.pin = GPIO_PIN2;
    ccp1_obj.ccp_pin.direction = GPIO_DIRECTION_OUTPUT;
    ccp1_obj.timer2_postscaler_value = 1;
    ccp1_obj.timer2_prescaler_value = 1;    
    ret = CCP1_Init(&ccp1_obj);
    
    timer_obj.TMR2_InterruptHandler = NULL;
    timer_obj.timer2_postscaler_value = TIMER2_POSTSCALER_DIV_BY_1;
    timer_obj.timer2_prescaler_value = TIMER2_PRESCALER_DIV_BY_1;
    timer_obj.timer2_preload_value = 0;
    ret = Timer2_Init(&timer_obj);
    
    CCP1_PWM1_Set_Duty(PWM_DUTY_CYCLE);
    CCP1_PWM1_Start();
    
    while(1){
        for (PWM_DUTY_CYCLE = 0; PWM_DUTY_CYCLE < 100; PWM_DUTY_CYCLE += 5){
            __delay_ms(5);
            CCP1_PWM1_Set_Duty(PWM_DUTY_CYCLE);
        } 
    }
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
