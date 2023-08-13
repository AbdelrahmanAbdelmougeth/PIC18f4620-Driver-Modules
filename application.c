/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

led_t led1 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW
};

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
   
    led_initialize(&led1);
    uint8 write_val = 0;
    uint8 read_val = 0;
    
    while (1) {
        ret = Data_EEPROM_WriteByte(0x3ff, write_val++);
        __delay_ms(1000);
        ret = Data_EEPROM_ReadByte(0x3ff, &read_val);
        if(read_val == 5)
            led_turn_on(&led1);
        else
            led_turn_off(&led1);
    } 
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
