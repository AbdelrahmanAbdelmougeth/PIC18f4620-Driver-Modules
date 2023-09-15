/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

uint8 received_data;

void MSSP_SPI_DefaultInterruptHandler(){
}

spi_t spi_slave2_obj = {
    .spi_mode = SPI_SLAVE_MODE_SS_ENABLED,
    .spi_config.ClockPolarity = CLOCK_POLARITY_IDLE_IS_LOW,
    .spi_config.ClockSelect = TRANSMIT_FROM_IDLE_TO_ACTIVE,
    .spi_config.SampleSelect = SAMPLE_INPUT_DATA_AT_MID,
    #if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        .MSSP_SPI_InterruptHandler = MSSP_SPI_DefaultInterruptHandler,
        .priority = INTERRUPT_LOW_PRIORITY,
    #endif
};

led_t led1 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    ret = SPI_Init(&spi_slave2_obj);
    ret = led_initialize(&led1);
    
    while(1){
        ret = SPI_Read_Byte_Blocking(&spi_slave2_obj, &received_data);
        if(received_data == 'b'){
            led_turn_on(&led1);
        }else if(received_data == 'd'){
            led_turn_off(&led1);
        }
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
