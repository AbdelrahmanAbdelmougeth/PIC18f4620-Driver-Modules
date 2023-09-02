/* 
 * File:   hal_ccp1.h
 * Author: hp
 *
 * Created on 02 ??????, 2023, 08:53 ?
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/* Section : Includes */
#include "ccp1_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../include/proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */
#define CCP1_MODULE_DISABLED                (uint8)0x00
#define CCP1_CAPTURE_MODE_1_FALLING_EDGE    (uint8)0x04
#define CCP1_CAPTURE_MODE_1_RISING_EDGE     (uint8)0x05
#define CCP1_CAPTURE_MODE_4_RISING_EDGE     (uint8)0x06
#define CCP1_CAPTURE_MODE_16_RISING_EDGE    (uint8)0x07

#define CCP1_COMPARE_MODE_TOGGLE_ON_MATCH   (uint8)0x02
#define CCP1_COMPARE_MODE_SET_PIN_LOW       (uint8)0x08
#define CCP1_COMPARE_MODE_SET_PIN_HIGH      (uint8)0x09
#define CCP1_COMPARE_MODE_GEN_SW_INTERRUPT  (uint8)0x0A
#define CCP1_COMPARE_MODE_GEN_SPECIAL_EVENT (uint8)0x0B

#define CCP1_PWM_MODE                       (uint8)0x0C

/* CCP1 Capture Mode State */
#define CCP1_CAPTURE_TRIGGERED        0x01
#define CCP1_CAPTURE_IDLE             0x00

/* CCP1 Compare Mode State */
#define CCP1_COMPARE_TRIGGERED        0x01
#define CCP1_COMPARE_IDLE             0x00


/* Section : Macro Functions Declarations */
#define CCP1_SET_MODE(_config) (CCP1CONbits.CCP1M = _config)

/* Section : Data-Type Declarations */
typedef enum{
    CCP1_CAPTURE_MODE_SELECTED = 0,
    CCP1_COMPARE_MODE_SELECTED,
    CCP1_PWM_MODE_SELECTED,
}ccp1_mode_t;

/*
 * @Summary      Defines the values to convert from 16-bit to 8-bit and vice versa
 * @Description  Used to get 8-bit values from 16-bit value also two 8-bit values are combined to get 16-bit value
 */
typedef union{
    struct{
        uint8 ccpr1_low;
        uint8 ccpr1_high;
    };
    struct{
        uint16 ccpr1_16_bit;
    };

}CCP1_PERIOD_REG_T;

typedef struct{
    ccp1_mode_t ccp1_mode;
    uint8 ccp1_mode_varient;
    pin_config_t ccp_pin;
    #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void (* CCP1_InterruptHandler)(void);
        interrupt_periority_cfg priority;
    #endif 
    #if CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED
        uint32 PWM_frequency;
        uint8 timer2_postscaler_value : 4;
        uint8 timer2_prescaler_value : 2;
    #endif
}ccp1_t;

/* Section : Function Declarations */
Std_ReturnType CCP1_Init(const ccp1_t* _ccp_obj);
Std_ReturnType CCP1_DeInit(const ccp1_t* _ccp_obj);

#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED
    Std_ReturnType CCP1_IsCapturedDataReady(uint8 *_capture_status);
    Std_ReturnType CCP1_Capture_Mode_Read_Value(uint16 *_captured_value);
#endif

#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELECTED
    Std_ReturnType CCP1_IsCompareTriggered(uint8 *_compare_status);
    Std_ReturnType CCP1_Compare_Mode_Write_Value(uint16 _compare_value);
#endif

#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED
    Std_ReturnType CCP1_PWM1_Set_Duty(const uint8 _duty);
    Std_ReturnType CCP1_PWM1_Start(void);
    Std_ReturnType CCP1_PWM1_Stop(void);
#endif


#endif	/* HAL_CCP1_H */

