/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

uint8 received_data, sent_data;
uint32 rx_counter, tx_counter;


led_t led1 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
led_t led2 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};

void EUSART_TxDefaultInterruptHandler(void){
    tx_counter++;
}

void EUSART_RxDefaultInterruptHandler(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = EUSART_ASYNC_RecieveByteNonBlocking(&received_data);
    rx_counter++;
    switch (received_data){
        case 'a' : 
            led_turn_on(&led1);
            EUSART_ASYNC_SendStringBlocking("Led1 On\r", 8);
        break;
        case 'b' : 
            led_turn_off(&led1);
            EUSART_ASYNC_SendStringBlocking("Led1 Off\r", 9);
        break;
        case 'c' : 
            led_turn_on(&led2);
            EUSART_ASYNC_SendStringBlocking("Led2 On\r", 8);
        break;
        case 'd' :
            led_turn_off(&led2);
            EUSART_ASYNC_SendStringBlocking("Led2 Off\r", 9);
        break;
        default: 
            led_turn_off(&led1); 
            led_turn_off(&led2);
            EUSART_ASYNC_SendStringBlocking("Led1 Off\r", 9);
            EUSART_ASYNC_SendStringBlocking("Led2 Off\r", 9);
    }
}

void EUSART_FramingErrorHandler(void){
    if(RCSTAbits.FERR == 1){
        uint8 _data;
        EUSART_ASYNC_RecieveByteNonBlocking(&_data);
    } 
}

void EUSART_OverrunErrorHandler(void){
    if(RCSTAbits.OERR == 1){
        EUSART_ASYNC_RX_Restart();      
    } 
}

void eusart_module_init(void){
    Std_ReturnType ret = E_NOT_OK;
    eusart_t eusart_obj;
    eusart_obj.baudrate = 9600;
    eusart_obj.baudrate_config = BAUDRATE_ASYNC_8BIT_LOW_SPEED;
    
    eusart_obj.eusart_tx_cfg.eusart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE;
    eusart_obj.eusart_tx_cfg.eusart_tx_9bit_enable = EUSART_TX_9BIT_DISABLE;
    eusart_obj.eusart_tx_cfg.eusart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
    
    eusart_obj.eusart_rx_cfg.eusart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE;
    eusart_obj.eusart_rx_cfg.eusart_rx_9bit_enable = EUSART_RX_9BIT_DISABLE;
    eusart_obj.eusart_rx_cfg.eusart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
    
    eusart_obj.EUSART_TxDefaultInterruptHandler = EUSART_TxDefaultInterruptHandler;
    eusart_obj.EUSART_RxDefaultInterruptHandler = EUSART_RxDefaultInterruptHandler;
    eusart_obj.EUSART_FramingErrorHandler = EUSART_FramingErrorHandler;
    eusart_obj.EUSART_OverrunErrorHandler = EUSART_OverrunErrorHandler;
    
    ret = EUSART_ASYNC_Init(&eusart_obj);
}


int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    eusart_module_init();
    led_initialize(&led1);
    led_initialize(&led2);
    
    while(1){  
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
