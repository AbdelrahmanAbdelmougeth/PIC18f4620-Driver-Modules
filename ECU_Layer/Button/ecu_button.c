/* 
 * File:   ecu_button.c
 * Author: abdo9
 *
 * Created on May 15, 2023, 1:31 PM
 */

#include "ecu_button.h"

Std_ReturnType button_initialize(const button_t *btn){
    Std_ReturnType ret = E_OK;
    if(btn == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_direction_initialize(&btn->button_pin);
    }
    return ret;
}
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state){
    Std_ReturnType ret = E_OK;
    button_state_t Btn_Status = BUTTON_RELEASED;
    logic_t Pin_Logic_Status = GPIO_LOW;
    if(btn == NULL || btn_state == NULL){
        ret = E_NOT_OK;
    }else{
        ret =  gpio_pin_read_logic(&btn->button_pin, &Pin_Logic_Status);
        if(btn->button_connection == BUTTON_ACTIVE_HIGH){
            if(Pin_Logic_Status == GPIO_HIGH){
                *btn_state = BUTTON_PRESSED;
            }else{
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(btn->button_connection == BUTTON_ACTIVE_LOW){
            if(Pin_Logic_Status == GPIO_HIGH){
                *btn_state = BUTTON_RELEASED;
            }else{
                *btn_state = BUTTON_PRESSED;
            }
        }
        else{/*nothing*/}
        ret = E_OK;
    }
    return ret;
}
