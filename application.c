/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

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
    
    eusart_obj.EUSART_TxDefaultInterruptHandler = NULL;
    eusart_obj.EUSART_RxDefaultInterruptHandler = NULL;
    eusart_obj.EUSART_FramingErrorHandler = NULL;
    eusart_obj.EUSART_OverrunErrorHandler = NULL;
    
    ret = EUSART_ASYNC_Init(&eusart_obj);
}

led_t led1 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

uint8 received_data;

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    eusart_module_init();
    led_initialize(&led1);
    
    while(1){
        ret = EUSART_ASYNC_RecieveByteBlocking(&received_data);
        if(received_data == 'o'){
            led_turn_on(&led1);
        }else if(received_data == 'f'){
            led_turn_off(&led1);        
        }else{/* nothing */}
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
