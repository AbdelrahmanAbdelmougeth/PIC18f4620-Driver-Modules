/* 
 * File:   ecu_led.h
 * Author: abdo9
 *
 * Created on May 15, 2023, 1:31 PM
 */
#include "ecu_seven_seg.h"

Std_ReturnType seven_segment_initialize(const segment_t *segment){
    Std_ReturnType ret = E_OK;
    if(segment == NULL){
        ret = E_NOT_OK;
    }else{
        gpio_pin_initialize(&segment->segment_pins[SEGMENT_PIN0]);
        gpio_pin_initialize(&segment->segment_pins[SEGMENT_PIN1]);
        gpio_pin_initialize(&segment->segment_pins[SEGMENT_PIN2]);
        gpio_pin_initialize(&segment->segment_pins[SEGMENT_PIN3]);
    }
    return ret;
}

Std_ReturnType seven_segment_write_number(const segment_t *segment, uint8 number){
    Std_ReturnType ret = E_OK;
    if(segment == NULL || number > 9){
        ret = E_NOT_OK;
    }else{
        gpio_pin_write_logic(&segment->segment_pins[SEGMENT_PIN0], number & 0x01);
        gpio_pin_write_logic(&segment->segment_pins[SEGMENT_PIN1], (number >> 1) & 0x01);
        gpio_pin_write_logic(&segment->segment_pins[SEGMENT_PIN2], (number >> 2) & 0x01);
        gpio_pin_write_logic(&segment->segment_pins[SEGMENT_PIN3], (number >> 3) & 0x01);
    }
    return ret;
}