/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

volatile uint8 interrupt_flag_counter = 0;
volatile uint8 send_not_completed_flag = 0;

led_t SPI_SS1 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_HIGH};
led_t SPI_SS2 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_HIGH};

spi_t spi_master_obj;


void MSSP_SPI_DefaultInterruptHandler(){
    send_not_completed_flag = 0;
    interrupt_flag_counter++;
    if(interrupt_flag_counter == 4){
        interrupt_flag_counter = 0;
    }
    led_turn_on(&SPI_SS1);
    led_turn_on(&SPI_SS2);
}

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    spi_master_obj.spi_mode = SPI_MASTER_MODE_FOSC_DIV_4;
    spi_master_obj.spi_config.ClockPolarity = CLOCK_POLARITY_IDLE_IS_LOW;
    spi_master_obj.spi_config.ClockSelect = TRANSMIT_FROM_IDLE_TO_ACTIVE;
    spi_master_obj.spi_config.SampleSelect = SAMPLE_INPUT_DATA_AT_MID;
    #if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        spi_master_obj.MSSP_SPI_InterruptHandler = MSSP_SPI_DefaultInterruptHandler,
        spi_master_obj.priority = INTERRUPT_LOW_PRIORITY,
    #endif
    
    ret = SPI_Init(&spi_master_obj);
    ret = led_initialize(&SPI_SS1);
    ret = led_initialize(&SPI_SS2);
        
    while(1){       
        if(!send_not_completed_flag && interrupt_flag_counter == 0){         
            ret = led_turn_off(&SPI_SS1);
            ret = SPI_Send_Byte_NonBlocking(&spi_master_obj, 'a');
            send_not_completed_flag = 1;
        }
        else if(!send_not_completed_flag && interrupt_flag_counter == 1){
            ret = led_turn_off(&SPI_SS2);
            ret = SPI_Send_Byte_NonBlocking(&spi_master_obj, 'b');
            send_not_completed_flag = 1;
        }
        else if(!send_not_completed_flag && interrupt_flag_counter == 2){
            ret = led_turn_off(&SPI_SS1);
            ret = SPI_Send_Byte_NonBlocking(&spi_master_obj, 'c');
            send_not_completed_flag = 1;
        }
        else if(!send_not_completed_flag && interrupt_flag_counter == 3){
            ret = led_turn_off(&SPI_SS2);
            ret = SPI_Send_Byte_NonBlocking(&spi_master_obj, 'd');
            send_not_completed_flag = 1;
        }
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
