/* 
 * File:   hal_gpio.h
 * Author: abdo9
 *
 * Created on May 15, 2023, 12:57 PM
 */

#include "hal_gpio.h"

/*Reference to the Data Direction Control Registers*/
volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/*Reference to the Data Latch Registers (Read and Write to Data Latch)*/ 
volatile uint8 *lat_registers[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
/*Reference to the Port Status Registers*/
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

Std_ReturnType gpio_pin_direction_initialize(const pin_config_t* _pin_config){
    Std_ReturnType ret= E_OK;
    
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }else{
        switch (_pin_config -> direction){
        case GPIO_DIRECTION_OUTPUT:
            CLEAR_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
            break;
        case GPIO_DIRECTION_INPUT:
            SET_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
            break; 
        default: ret = E_NOT_OK;  
        }    
    }
    
    return ret;
}

Std_ReturnType gpio_pin_get_direction_status(const pin_config_t* _pin_config, direction_t* direction_status){
    Std_ReturnType ret = E_OK;
    if(_pin_config == NULL || direction_status == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }else {
    
    }   
    return ret;
}
Std_ReturnType gpio_pin_write_logic(const pin_config_t* _pin_config, logic_t logic){
    Std_ReturnType ret= E_OK;
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }else {
    
    }  
    return ret;
}
Std_ReturnType gpio_pin_read_logic(const pin_config_t* _pin_config, logic_t* logic){
    Std_ReturnType ret= E_OK;
    if(_pin_config == NULL || logic == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }else {
    
    }  
    return ret;
}
Std_ReturnType gpio_toggle_logic(const pin_config_t* _pin_config){
    Std_ReturnType ret= E_OK;
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }else {
    
    }  
    return ret;
}

Std_ReturnType gpio_port_direction_initialize(const port_index_t port, uint8 direction){
    Std_ReturnType ret= E_OK;
 
    return ret;
}
Std_ReturnType gpio_port_get_direction_status(const port_index_t port, uint8* direction_status){
    Std_ReturnType ret= E_OK;
    if(direction_status == NULL)
    {
        ret = E_NOT_OK;
    }else {
    
    }  
    return ret;
}
Std_ReturnType gpio_port_write_logic(const port_index_t port, uint8 logic){
    Std_ReturnType ret= E_OK;
 
    return ret;
}
Std_ReturnType gpio_port_read_logic(const port_index_t port, uint8* logic){
    Std_ReturnType ret= E_OK;
     if(logic == NULL)
    {
        ret = E_NOT_OK;
    }else {
    
    }  
    return ret;
}
Std_ReturnType gpio_port_toggle_logic(const port_index_t port){
    Std_ReturnType ret= E_OK;
 
    return ret;
}
