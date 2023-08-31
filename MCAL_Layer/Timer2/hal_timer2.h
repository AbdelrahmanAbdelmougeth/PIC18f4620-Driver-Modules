/* 
 * File:   hal_timer2.h
 * Author: hp
 *
 * Created on 31 ?????, 2023, 10:30 ?
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../include/proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */
#define TIMER2_PRESCALER_DIV_BY_1   0
#define TIMER2_PRESCALER_DIV_BY_4   1
#define TIMER2_PRESCALER_DIV_BY_16  2

/* Section : Macro Functions Declarations */
#define TIMER2_MODULE_ENABLE()   (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()  (T2CONbits.TMR2ON = 0)

#define TIMER2_PRESCALER_SELECT(_prescaler_val)   (T2CONbits.T2CKPS = _prescaler_val)
#define TIMER2_POSTSCALER_SELECT(_postscaler_val) (T2CONbits.TOUTPS = _postscaler_val)

/* Section : Data-Type Declarations */
typedef enum{
    TIMER2_POSTSCALER_DIV_BY_1 = 0,
    TIMER2_POSTSCALER_DIV_BY_2,
    TIMER2_POSTSCALER_DIV_BY_3,
    TIMER2_POSTSCALER_DIV_BY_4,
    TIMER2_POSTSCALER_DIV_BY_5,
    TIMER2_POSTSCALER_DIV_BY_6,
    TIMER2_POSTSCALER_DIV_BY_7,
    TIMER2_POSTSCALER_DIV_BY_8,
    TIMER2_POSTSCALER_DIV_BY_9,
    TIMER2_POSTSCALER_DIV_BY_10,
    TIMER2_POSTSCALER_DIV_BY_11,
    TIMER2_POSTSCALER_DIV_BY_12,
    TIMER2_POSTSCALER_DIV_BY_13,
    TIMER2_POSTSCALER_DIV_BY_14,
    TIMER2_POSTSCALER_DIV_BY_15,            
    TIMER2_POSTSCALER_DIV_BY_16,            
}timer2_prescaler_select_t;

typedef struct{
    #if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void (* TMR2_InterruptHandler)(void);
        interrupt_periority_cfg priority;
    #endif   
    uint8 timer2_preload_value;
    uint8 timer2_postscaler_value : 4;
    uint8 timer2_prescaler_value : 2;
    uint8 timer2_reserved : 2;
}timer2_t;

/* Section : Function Declarations */
Std_ReturnType Timer2_Init(const timer2_t* _timer2);
Std_ReturnType Timer2_DeInit(const timer2_t* _timer2);
Std_ReturnType Timer2_Write_Value(const timer2_t* _timer2, uint8 _value);
Std_ReturnType Timer2_Read_Value(const timer2_t* _timer2, uint8 *_value);

#endif	/* HAL_TIMER2_H */

