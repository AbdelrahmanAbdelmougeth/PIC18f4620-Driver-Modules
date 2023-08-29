/* 
 * File:   hal_timer0.h
 * Author: hp
 *
 * Created on 26 ?????, 2023, 05:22 ?
 */

#ifndef HAL_TIMER_H
#define	HAL_TIMER_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../include/proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */
#define TIMER0_16BIT_REGISTER_ENABLED  0
#define TIMER0_8BIT_REGISTER_ENABLED   1

#define TIMER0_PRESCALER_ENABLED  1
#define TIMER0_PRESCALER_DISABLED 0

#define TIMER0_INCREMENT_ON_FALLING_EDGE  1
#define TIMER0_INCREMENT_ON_RISING_EDGE   0

#define TIMER0_TIMER_MODE     1
#define TIMER0_COUNTER_MODE   0


/* Section : Macro Functions Declarations */
#define TIMER0_PRESCALER_ENABLE()   (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()  (T0CONbits.PSA = 1)

#define TIMER0_PRESCALER_SET(_prescaler_val) (T0CONbits.T0PS = _prescaler_val)

#define TIMER0_RISING_EDGE_ENABLE()        (T0CONbits.T0SE = 1)
#define TIMER0_FALLING_EDGE_ENABLE()       (T0CONbits.T0SE = 0)

#define TIMER0_TIMER_MODE_ENABLE()         (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()       (T0CONbits.T0CS = 1)

#define TIMER0_16BIT_REGISTER_ENABLE()     (T0CONbits.T08BIT = 0)
#define TIMER0_8BIT_REGISTER_ENABLE()      (T0CONbits.T08BIT = 1)

#define TIMER0_MODULE_ENABLE()   (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()  (T0CONbits.TMR0ON = 0)

/* Section : Data-Type Declarations */
typedef enum{
    TIMER0_PRESCALER_DIV_BY_2 = 0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256,         
}timer0_prescaler_select_t;

typedef struct{
    #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void (* TMR0_InterruptHandler)(void);
        interrupt_periority_cfg priority;
    #endif   
    timer0_prescaler_select_t  prescaler_value;
    uint16 timer0_preload_value;
    uint8 timer0_mode : 1;
    uint8 timer0_register_size : 1;
    uint8 source_edge_select : 1; 
    uint8 prescaler_enable : 1;
    uint8 timer0_reserved : 4;
}timer0_t;

/* Section : Function Declarations */
Std_ReturnType Timer0_Init(const timer0_t* _timer0);
Std_ReturnType Timer0_DeInit(const timer0_t* _timer0);
Std_ReturnType Timer0_Write_Value(const timer0_t* _timer0, uint16 _value);
Std_ReturnType Timer0_Read_Value(const timer0_t* _timer0, uint16 *_value);


#endif	/* HAL_TIMER_H */

