/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"
void ADC_DefaultInterruptHandler(void);

uint16 adc_result_1;
volatile uint8 flag;

adc_config_t adc_1 = {
    .ADC_InterruptHandler = ADC_DefaultInterruptHandler,
    .acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT_FORMAT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLED        
};

void ADC_DefaultInterruptHandler(void){
    Std_ReturnType ret = E_NOT_OK;
    ADC_GetConversionResult(&adc_1, &adc_result_1);
    flag++;
}



int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_ALL_ANALOG_FUNCTIONALITY);
   
    while (1) {
        ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN0);
    } 
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ADC_Init(&adc_1);
    ret = ecu_layer_initialize();
}
