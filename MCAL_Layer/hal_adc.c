/* 
 * File:   hal_adc.h
 * Author: hp
 *
 * Created on 18 ?????, 2023, 03:33 ?
 */

#include "hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void(* ADC_InterruptHandler)(void) = NULL;       
#endif 

static inline void adc_input_channel_port_configuration(const adc_channel_select_t channel);
static inline void adc_set_result_format(const adc_config_t* _adc);
static inline void adc_set_voltage_reference(const adc_config_t* _adc);

/**
 * @summary      Initialize the ADC
 * @Description  This Routine Initializes the ADC
 *               This Routine Must be called before any other ADC routines is called
 *               This Routine Should be called only once during system initialization  
 * @Precondition None
 * @param       _adc Pointer to the ADC configuration
 * @return      Status of the function
 *              (E_OK) : The Function done successfully
 *              (E_NOT_OK) : The Function has an issue to perform this action
 */
Std_ReturnType ADC_Init(const adc_config_t* _adc){
    Std_ReturnType ret = E_OK;
    if(_adc == NULL){
        ret = E_NOT_OK;
    }else{
        /* Disable the ADC */
        ADC_DISABLE();
        
        /* Configure the acquisition time */
        ADC_SET_ACQUISITION_TIME(_adc->acquisition_time);
        
        /* Configure the conversion clock */
        ADC_SET_CONVERSION_CLOCK(_adc->conversion_clock);
        
        /* Configure the default channel */
        ADC_CHANNEL_SELECT(_adc->adc_channel);
        adc_input_channel_port_configuration(_adc->adc_channel);
        
        /* Configure the interrupt */
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            ADC_IterruptEnable();
            ADC_InterruptHandler = _adc->ADC_InterruptHandler;
            ADC_IterruptFlagClear();
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                if(_adc->priority == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_GobalInterruptLowEnable();
                    ADC_INTERRUPT_LowPrioritySet();
                }else if(_adc->priority == INTERRUPT_HIGH_PRIORITY){
                    INTERRUPT_GobalInterruptHighEnable();
                    ADC_INTERRUPT_HighPrioritySet();
                }    
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable(); 
            #endif
        #endif 
        /* Configure the result format */
        adc_set_result_format(_adc);
        
        /* Configure the voltage reference */
        adc_set_voltage_reference(_adc);
        /* Enable the ADC */ 
        ADC_ENABLE();
    }
    return ret;
}

/**
 * @summary     De-initialize the ADC
 * @param       _adc : Pointer to the ADC configuration
 * @return      Status of the function
 *              (E_OK) : The Function done successfully
 *              (E_NOT_OK) : The Function has an issue to perform this action
 */
Std_ReturnType ADC_DeInit(const adc_config_t* _adc){
    Std_ReturnType ret = E_OK;
    if(_adc == NULL){
        ret = E_NOT_OK;
    }else{
        /* Disable the ADC */
        ADC_DISABLE();
        /* Configure the interrupt */
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            ADC_IterruptDisable();
        #endif 
    }
    return ret;
}

Std_ReturnType ADC_SelectChannel(const adc_config_t* _adc, adc_channel_select_t channel){
    Std_ReturnType ret = E_OK;
    if(_adc == NULL){
        ret = E_NOT_OK;
    }else{
        /* Configure the selected channel */
        ADC_CHANNEL_SELECT(channel);
        adc_input_channel_port_configuration(channel);
    }
    return ret;
}

Std_ReturnType ADC_StartConversion(const adc_config_t* _adc){
    Std_ReturnType ret = E_OK;
    if(_adc == NULL){
        ret = E_NOT_OK;
    }else{
        ADC_START_CONVERSION();
    }
    return ret;
}

Std_ReturnType ADC_IsConversionDone(const adc_config_t* _adc, uint8 *conversion_status){
    Std_ReturnType ret = E_OK;
    if(_adc == NULL || conversion_status == NULL){
        ret = E_NOT_OK;
    }else{
        *conversion_status = (uint8)( !ADCON0bits.GO_nDONE);  
    }
    return ret;
}

Std_ReturnType ADC_GetConversionResult(const adc_config_t* _adc, uint16 *conversion_result){
    Std_ReturnType ret = E_OK;
    if(_adc == NULL || conversion_result == NULL){
        ret = E_NOT_OK;
    }else{
        if(_adc->result_format == ADC_RESULT_RIGHT_FORMAT){
            *conversion_result = (uint16)((ADRESH << 8) + ADRESL);
        }else if(_adc->result_format == ADC_RESULT_LEFT_FORMAT){
            *conversion_result = (uint16)(((ADRESH << 8) + ADRESL) >> 6);
        }else{
            *conversion_result = (uint16)((ADRESH << 8) + ADRESL);
        }
    }
    return ret;
}

Std_ReturnType ADC_GetConversion_Blocking(const adc_config_t* _adc, adc_channel_select_t channel,
                                 uint16 *conversion_result){
    Std_ReturnType ret = E_OK;
    if(_adc == NULL || conversion_result == NULL){
        ret = E_NOT_OK;
    }else{
        /* Select the A/D channel */
        ret = ADC_SelectChannel(_adc, channel);
        /* Start the conversion */
        ret = ADC_StartConversion(_adc);
        /* Check if the conversion is completed */
        while(ADCON0bits.GO_nDONE);
        ret = ADC_GetConversionResult(_adc, conversion_result);
    }
    return ret;
}

Std_ReturnType ADC_StartConversion_Interrupt(const adc_config_t* _adc, adc_channel_select_t channel){
    Std_ReturnType ret = E_OK;
    if(_adc == NULL){
        ret = E_NOT_OK;
    }else{
        /* Select the A/D channel */
        ret = ADC_SelectChannel(_adc, channel);
        /* Start the conversion */
        ret = ADC_StartConversion(_adc);
    }
    return ret;
}


static inline void adc_input_channel_port_configuration(const adc_channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0 : SET_BIT(TRISA, GPIO_PIN0); break; /* sets the bit as input */
        case ADC_CHANNEL_AN1 : SET_BIT(TRISA, GPIO_PIN1); break; /* sets the bit as input */
        case ADC_CHANNEL_AN2 : SET_BIT(TRISA, GPIO_PIN2); break; /* sets the bit as input */
        case ADC_CHANNEL_AN3 : SET_BIT(TRISA, GPIO_PIN3); break; /* sets the bit as input */
        case ADC_CHANNEL_AN4 : SET_BIT(TRISA, GPIO_PIN5); break; /* sets the bit as input */
        case ADC_CHANNEL_AN5 : SET_BIT(TRISE, GPIO_PIN0); break; /* sets the bit as input */
        case ADC_CHANNEL_AN6 : SET_BIT(TRISE, GPIO_PIN1); break; /* sets the bit as input */
        case ADC_CHANNEL_AN7 : SET_BIT(TRISE, GPIO_PIN2); break; /* sets the bit as input */
        case ADC_CHANNEL_AN8 : SET_BIT(TRISB, GPIO_PIN2); break; /* sets the bit as input */
        case ADC_CHANNEL_AN9 : SET_BIT(TRISB, GPIO_PIN3); break; /* sets the bit as input */
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB, GPIO_PIN1); break; /* sets the bit as input */
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB, GPIO_PIN4); break; /* sets the bit as input */
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB, GPIO_PIN0); break; /* sets the bit as input */
        
    }
}

static inline void adc_set_result_format(const adc_config_t* _adc){
    if(_adc->result_format == ADC_RESULT_RIGHT_FORMAT)
        ADC_RESULT_FORMAT_RIGHT_JUSTIFICATION();
    else if (_adc->result_format == ADC_RESULT_LEFT_FORMAT)
        ADC_RESULT_FORMAT_LEFT_JUSTIFICATION();
    else
        ADC_RESULT_FORMAT_RIGHT_JUSTIFICATION();
}

static inline void adc_set_voltage_reference(const adc_config_t* _adc){
    if(_adc->voltage_reference == ADC_VOLTAGE_REFERENCE_ENABLED)
        ADC_VOLTAGE_REFERENCE_ENABLE();
    else if(_adc->voltage_reference == ADC_VOLTAGE_REFERENCE_DISABLED)
        ADC_VOLTAGE_REFERENCE_DISABLE();
    else
        ADC_VOLTAGE_REFERENCE_DISABLE();
}

void ADC_ISR(void){
    /* The Internal ADC Interrupt has been occurred (must be cleared in software) */ 
    ADC_IterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context*/
    
    /* Callback function gets called every time this ISR executes*/
    if(ADC_InterruptHandler){
        ADC_InterruptHandler();
    }
}
