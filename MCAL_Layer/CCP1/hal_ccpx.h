/* 
 * File:   hal_ccp1.h
 * Author: hp
 *
 * Created on 02 ??????, 2023, 08:53 ?
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/* Section : Includes */
#include "ccpx_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../include/proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */
#define CCPx_MODULE_DISABLED                (uint8)0x00
#define CCPx_CAPTURE_MODE_1_FALLING_EDGE    (uint8)0x04
#define CCPx_CAPTURE_MODE_1_RISING_EDGE     (uint8)0x05
#define CCPx_CAPTURE_MODE_4_RISING_EDGE     (uint8)0x06
#define CCPx_CAPTURE_MODE_16_RISING_EDGE    (uint8)0x07

#define CCPx_COMPARE_MODE_TOGGLE_ON_MATCH   (uint8)0x02
#define CCPx_COMPARE_MODE_SET_PIN_LOW       (uint8)0x08
#define CCPx_COMPARE_MODE_SET_PIN_HIGH      (uint8)0x09
#define CCPx_COMPARE_MODE_GEN_SW_INTERRUPT  (uint8)0x0A
#define CCPx_COMPARE_MODE_GEN_SPECIAL_EVENT (uint8)0x0B

#define CCPx_PWM_MODE                       (uint8)0x0C

#define CCPx_TIMER2_PRESCALER_DIV_BY_1   1
#define CCPx_TIMER2_PRESCALER_DIV_BY_4   2
#define CCPx_TIMER2_PRESCALER_DIV_BY_16  3

#define CCPx_TIMER2_POSTSCALER_DIV_BY_1   1
#define CCPx_TIMER2_POSTSCALER_DIV_BY_2   2
#define CCPx_TIMER2_POSTSCALER_DIV_BY_3   3
#define CCPx_TIMER2_POSTSCALER_DIV_BY_4   4
#define CCPx_TIMER2_POSTSCALER_DIV_BY_5   5
#define CCPx_TIMER2_POSTSCALER_DIV_BY_6   6
#define CCPx_TIMER2_POSTSCALER_DIV_BY_7   7
#define CCPx_TIMER2_POSTSCALER_DIV_BY_8   8
#define CCPx_TIMER2_POSTSCALER_DIV_BY_9   9
#define CCPx_TIMER2_POSTSCALER_DIV_BY_10  10
#define CCPx_TIMER2_POSTSCALER_DIV_BY_11  11
#define CCPx_TIMER2_POSTSCALER_DIV_BY_12  12
#define CCPx_TIMER2_POSTSCALER_DIV_BY_13  13
#define CCPx_TIMER2_POSTSCALER_DIV_BY_14  14
#define CCPx_TIMER2_POSTSCALER_DIV_BY_15  15           
#define CCPx_TIMER2_POSTSCALER_DIV_BY_16  16

/* CCPx Capture Mode State */
#define CCPx_CAPTURE_TRIGGERED        0x01
#define CCPx_CAPTURE_IDLE             0x00

/* CCPx Compare Mode State */
#define CCPx_COMPARE_TRIGGERED        0x01
#define CCPx_COMPARE_IDLE             0x00


/* Section : Macro Functions Declarations */
#define CCP1_SET_MODE(_config) (CCP1CONbits.CCP1M = _config)
#define CCP2_SET_MODE(_config) (CCP2CONbits.CCP2M = _config)

/* Section : Data-Type Declarations */
typedef enum{
    CCPx_CAPTURE_MODE_SELECTED = 0,
    CCPx_COMPARE_MODE_SELECTED,
    CCPx_PWM_MODE_SELECTED,
}ccpx_mode_t;

typedef enum{
    CCP1_INST = 0,
    CCP2_INST        
}ccpx_inst_t;

typedef enum{
    CCP1_CCP2_TIMER1 = 0,
    CCP1_TIMER1_CCP2_TIMER2,
    CCP1_CCP2_TIMER3        
}ccp_capture_timer_t;

/*
 * @Summary      Defines the values to convert from 16-bit to 8-bit and vice versa
 * @Description  Used to get 8-bit values from 16-bit value also two 8-bit values are combined to get 16-bit value
 */
typedef union{
    struct{
        uint8 ccprx_low;
        uint8 ccprx_high;
    };
    struct{
        uint16 ccprx_16_bit;
    };

}CCPx_PERIOD_REG_T;

typedef struct{
    ccpx_inst_t ccpx_inst;
    ccpx_mode_t ccpx_mode;
    uint8 ccpx_mode_varient;
    pin_config_t ccpx_pin;
    #if CCPx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void (* CCPx_InterruptHandler)(void);
        interrupt_periority_cfg priority;
    #endif
    #if CCPx_CFG_SELECTED_MODE == CCPx_CFG_CAPTURE_MODE_SELECTED
        ccp_capture_timer_t ccp_capture_timer;
    #endif    
    #if CCPx_CFG_SELECTED_MODE == CCPx_CFG_PWM_MODE_SELECTED
        uint32 PWM_frequency;
        uint8 timer2_postscaler_value : 4;
        uint8 timer2_prescaler_value : 2;
    #endif   
}ccpx_t;

/* Section : Function Declarations */
Std_ReturnType CCPx_Init(const ccpx_t* _ccp_obj);
Std_ReturnType CCPx_DeInit(const ccpx_t* _ccp_obj);

#if CCPx_CFG_SELECTED_MODE == CCPx_CFG_CAPTURE_MODE_SELECTED
    Std_ReturnType CCPx_IsCapturedDataReady(const ccpx_t* _ccp_obj, uint8 *_capture_status);
    Std_ReturnType CCPx_Capture_Mode_Read_Value(const ccpx_t* _ccp_obj, uint16 *_captured_value);
#endif

#if CCPx_CFG_SELECTED_MODE == CCPx_CFG_COMPARE_MODE_SELECTED
    Std_ReturnType CCP1_IsCompareTriggered(uint8 *_compare_status);
    Std_ReturnType CCP1_Compare_Mode_Write_Value(uint16 _compare_value);
#endif

#if CCPx_CFG_SELECTED_MODE == CCPx_CFG_PWM_MODE_SELECTED
    Std_ReturnType CCPx_PWM_Set_Duty(const ccpx_t* _ccp_obj, const uint8 _duty);
    Std_ReturnType CCPx_PWM_Start(const ccpx_t* _ccp_obj);
    Std_ReturnType CCPx_PWM_Stop(const ccpx_t* _ccp_obj);
#endif


#endif	/* HAL_CCP1_H */

