/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

volatile uint8 receveid_data;
void MSSP_SPI_DefaultInterruptHandler();

spi_t spi_slave1_obj = {
    .spi_mode = SPI_SLAVE_MODE_SS_ENABLED,
    .spi_config.ClockPolarity = CLOCK_POLARITY_IDLE_IS_LOW,
    .spi_config.ClockSelect = TRANSMIT_FROM_IDLE_TO_ACTIVE,
    .spi_config.SampleSelect = SAMPLE_INPUT_DATA_AT_MID,
    #if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        .MSSP_SPI_InterruptHandler = MSSP_SPI_DefaultInterruptHandler,
        .priority = INTERRUPT_LOW_PRIORITY,
    #endif
};

void MSSP_SPI_DefaultInterruptHandler(){
    SPI_Send_Byte_NonBlocking(&spi_slave1_obj, &receveid_data);
}

led_t led1 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    ret = SPI_Init(&spi_slave1_obj);
    ret = led_initialize(&led1);
    
    while(1){
        if(receveid_data == 'a'){
            led_turn_on(&led1);
        }else if(receveid_data == 'c'){
            led_turn_off(&led1);
        }
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
