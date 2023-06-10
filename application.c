/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

relay_t relay_1 = {
    .relay_port_name = PORTC_INDEX,
    .relay_pin = GPIO_PIN0,
    .relay_status = RELAY_OFF_STATUS
};

int main() {
    Std_ReturnType ret = E_NOT_OK;

    application_initialize();

    while (1) {
        relay_toggle(&relay_1);
        __delay_ms(5000);
    }
     
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = relay_initialize(&relay_1);
}