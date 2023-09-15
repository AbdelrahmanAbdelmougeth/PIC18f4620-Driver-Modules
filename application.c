/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

void MSSP_SPI_DefaultInterruptHandler(){
}

spi_t spi_master_obj = {
    .spi_mode = SPI_MASTER_MODE_FOSC_DIV_4,
    .spi_config.ClockPolarity = CLOCK_POLARITY_IDLE_IS_LOW,
    .spi_config.ClockSelect = TRANSMIT_FROM_IDLE_TO_ACTIVE,
    .spi_config.SampleSelect = SAMPLE_INPUT_DATA_AT_MID,
    #if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        .MSSP_SPI_InterruptHandler = MSSP_SPI_DefaultInterruptHandler,
        .priority = INTERRUPT_LOW_PRIORITY,
    #endif
};

led_t SPI_SS1 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_HIGH};
led_t SPI_SS2 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_HIGH};

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    ret = SPI_Init(&spi_master_obj);
    ret = led_initialize(&SPI_SS1);
    ret = led_initialize(&SPI_SS2);
    
    while(1){
        ret = led_turn_off(&SPI_SS1);
        ret = SPI_Send_Byte_Blocking(&spi_master_obj, 'a');   
        ret = led_turn_on(&SPI_SS1);
        __delay_ms(500);
        
        ret = led_turn_off(&SPI_SS2);
        ret = SPI_Send_Byte_Blocking(&spi_master_obj, 'b');
        ret = led_turn_on(&SPI_SS2);
        __delay_ms(500);
        
        ret = led_turn_off(&SPI_SS1);
        ret = SPI_Send_Byte_Blocking(&spi_master_obj, 'c');   
        ret = led_turn_on(&SPI_SS1);
        __delay_ms(500);
        
        ret = led_turn_off(&SPI_SS2);
        ret = SPI_Send_Byte_Blocking(&spi_master_obj, 'd');
        ret = led_turn_on(&SPI_SS2);
        __delay_ms(500);
        
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
