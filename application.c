/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"


int main() {
    Std_ReturnType ret = E_NOT_OK;

    application_initialize();
    
    while (1) {
    }
     
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}