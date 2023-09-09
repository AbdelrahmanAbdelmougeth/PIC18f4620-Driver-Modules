/* 
 * File:   hal_adc.h
 * Author: hp
 *
 * Created on 18 ?????, 2023, 03:33 ?
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* Section : Includes */
#include "hal_adc_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../include/proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"


/* Section : Macro Declarations */

/*
 * @brief Analog-to-Digital Port configuration control
 * @note  When ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means
 *        AN0, AN1, AN2, AN3 and AN4 are configured analog       
 */
#define ADC_AN0_ANALOG_FUNCTIONALITY  0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY  0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY  0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY  0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY  0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY  0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY  0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY  0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY  0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY  0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY 0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY 0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY 0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY  0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY 0x0F

#define ADC_RESULT_RIGHT_FORMAT       0x01U
#define ADC_RESULT_LEFT_FORMAT        0x00U

#define ADC_VOLTAGE_REFERENCE_ENABLED        0x01U
#define ADC_VOLTAGE_REFERENCE_DISABLED       0x00U

#define ADC_CONVERSION_IS_COMPLETED          0x01U
#define ADC_CONVERSION_IS_NOT_COMPLETED      0x00U

/*
 * @brief ADC Conversion Status
 * @note 1 = A/D conversion in progress / 0 = A/D Idle
 */
#define ADC_GET_CONVERSION_STATUS() (ADCON0bits.GO_nDONE)

/*
 * @brief Start ADC Conversion
 */
#define ADC_START_CONVERSION()      (ADCON0bits.GO_nDONE = 1)


/*
 * @brief ADC Enable
 * @note 1 = A/D Converter module is enabled
 */
#define ADC_ENABLE()                (ADCON0bits.ADON = 1)

/*
 * @brief ADC Enable
 * @note 0 = A/D Converter module is disabled
 */
#define ADC_DISABLE()               (ADCON0bits.ADON = 0)


/*
 * @brief Enable and Disable the voltage reference
 * @note ADC_VOLTAGE_REFERENCE_ENABLE():  1 = VREF+ (AN3) / 1 = VREF- (AN2) 
 * @note ADC_VOLTAGE_REFERENCE_DISABLE(): 0 = VDD / 0 = VSS
 */
#define ADC_VOLTAGE_REFERENCE_DISABLE()  do{ADCON1bits.VCFG0 = 0;\
                                           ADCON1bits.VCFG1 = 0;\
                                        }while(0)
#define ADC_VOLTAGE_REFERENCE_ENABLE()  do{ADCON1bits.VCFG0 = 1;\
                                           ADCON1bits.VCFG1 = 1;\
                                        }while(0)

/*
 * @brief Analog-to-Digital Port configuration control
 * @note  This function like macro takes one macro configuration control
 *        and sets it in PCFG.
 *        When ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means
 *        AN0, AN1, AN2, AN3 and AN4 are configured analog
 *        @ref Analog-to-Digital Port configuration control      
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_config)   (ADCON1bits.PCFG = _config)

/*
 * @brief A/D Result Format Select bit
 * @note  1 = Right justified / 0 = Left justified
 */
#define ADC_RESULT_FORMAT_RIGHT_JUSTIFICATION()   (ADCON2bits.ADFM = 1)
#define ADC_RESULT_FORMAT_LEFT_JUSTIFICATION()    (ADCON2bits.ADFM = 0)

/*
 * @brief Sets the ADC Acquisition time
 */
#define ADC_SET_ACQUISITION_TIME(_acq_time)       (ADCON2bits.ACQT = _acq_time)

/*
 * @brief Sets the ADC Conversion clock
 */
#define ADC_SET_CONVERSION_CLOCK(_conv_clock)     (ADCON2bits.ADCS = _conv_clock)

/*
 * @brief Sets the ADC Conversion clock
 */
#define ADC_CHANNEL_SELECT(_channel)              (ADCON0bits.CHS = _channel)

/* Section : Data-Type Declarations */

/*
 * @brief Analog Channel Select 
 */
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,
}adc_channel_select_t;

/*
 * @brief  A/D Acquisition time select
 * @note   Acquisition time (sampling time): The time required by the (ADC) to capture
 *         the input voltage during sampling
 * @note   Acquisition time of (SAR) analog to digital converter is the time required
 *         for the (S/H) circuit to charge the capacitor 
 */
typedef enum{
    ADC_0_TAD = 0,            
    ADC_2_TAD,            
    ADC_4_TAD,            
    ADC_6_TAD,            
    ADC_8_TAD,            
    ADC_12_TAD,            
    ADC_16_TAD,            
    ADC_20_TAD,            
}adc_acquisition_time_t;

/*
 * @brief  A/D Conversion Clock select
 * @note   If the A/D FRC clock source is selected, a delay of one TCY (instruction cycle) is added before the A/D
 *         clock starts. This allows the SLEEP instruction to be executed before starting a conversion. 
 */
typedef enum{
    ADC_CLOCK_FOSC_DIV_2 = 0,
    ADC_CLOCK_FOSC_DIV_8,
    ADC_CLOCK_FOSC_DIV_32,
    ADC_CLOCK_FRC,
    ADC_CLOCK_FOSC_DIV_4,        
    ADC_CLOCK_FOSC_DIV_16,        
    ADC_CLOCK_FOSC_DIV_64,        
}adc_conversion_clock_t;


typedef struct{
    #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void (* ADC_InterruptHandler)(void);
        interrupt_periority_cfg priority;
    #endif    
    adc_acquisition_time_t acquisition_time;  /* @ref adc_acquisition_time_t */ 
    adc_conversion_clock_t conversion_clock;  /* @ref adc_conversion_clock_t */
    adc_channel_select_t adc_channel;         /* @ref adc_channel_select_t */
    uint8 voltage_reference : 1;              /* voltage reference configuration */
    uint8 result_format : 1;                  /* result format configuration */
    uint8 adc_reserved : 6;
}adc_config_t;

/* Section : Function Declarations */
Std_ReturnType ADC_Init(const adc_config_t* _adc);
Std_ReturnType ADC_DeInit(const adc_config_t* _adc);
Std_ReturnType ADC_SelectChannel(const adc_config_t* _adc, adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion(const adc_config_t* _adc);
Std_ReturnType ADC_IsConversionDone(const adc_config_t* _adc, uint8 *conversion_status);
Std_ReturnType ADC_GetConversionResult(const adc_config_t* _adc, uint16 *conversion_result);
Std_ReturnType ADC_GetConversion_Blocking(const adc_config_t* _adc, adc_channel_select_t channel,
                                          uint16 *conversion_result);
Std_ReturnType ADC_StartConversion_Interrupt(const adc_config_t* _adc, adc_channel_select_t channel);


#endif	/* HAL_ADC_H */

