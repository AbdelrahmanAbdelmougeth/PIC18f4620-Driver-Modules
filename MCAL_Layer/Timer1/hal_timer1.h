/* 
 * File:   hal_timer1.h
 * Author: hp
 *
 * Created on 30 ?????, 2023, 12:00 ?
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H


/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../include/proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */
#define TIMER1_COUNTER_MODE     1
#define TIMER1_TIMER_MODE       0

#define TIMER1_ASYNC_COUNTER_MODE    1
#define TIMER1_SYNC_COUNTER_MODE     0

#define TIMER1_OSC_ENABLED     1
#define TIMER1_OSC_DISABLED    0

#define TIMER1_PRESCALER_DIV_BY_1  0
#define TIMER1_PRESCALER_DIV_BY_2  1
#define TIMER1_PRESCALER_DIV_BY_4  2
#define TIMER1_PRESCALER_DIV_BY_8  3

#define TIMER1_REG_RW_16BIT_MODE_ENABLED  1
#define TIMER1_REG_RW_8BIT_MODE_ENABLED   0



/* Section : Macro Functions Declarations */
#define TIMER1_MODULE_ENABLE()   (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()  (T1CONbits.TMR1ON = 0)

#define TIMER1_COUNTER_MODE_ENABLE()       (T1CONbits.TMR1CS = 1)
#define TIMER1_TIMER_MODE_ENABLE()         (T1CONbits.TMR1CS = 0)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE() (T1CONbits.T1SYNC = 1)  
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()  (T1CONbits.T1SYNC = 0)  

#define TIMER1_OSC_HW_ENABLE()             (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_HW_DISABLE()            (T1CONbits.T1OSCEN = 0)

#define TIMER1_PRESCALER_SET(_prescaler_val) (T1CONbits.T1CKPS = _prescaler_val)

#define TIMER1_SYSTEM_CLK_STATUS()           (T1CONbits.T1RUN)

#define TIMER1_REG_RW_16BIT_MODE_ENABLE()   (T1CONbits.RD16 = 1)
#define TIMER1_REG_RW_8BIT_MODE_ENABLE()    (T1CONbits.RD16 = 0)



/* Section : Data-Type Declarations */
typedef struct{
    #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void (* TMR1_InterruptHandler)(void);
        interrupt_periority_cfg priority;
    #endif   
    uint16 timer1_preload_value;
    uint8 timer1_prescaler_value : 2;
    uint8 timer1_mode : 1;
    uint8 timer1_counter_mode : 1;
    uint8 timer1_osc_cfg : 1;
    uint8 timer1_reg_rw_mode : 1;
    uint8 timer1_reserved : 2;
}timer1_t;

/* Section : Function Declarations */
Std_ReturnType Timer1_Init(const timer1_t* _timer1);
Std_ReturnType Timer1_DeInit(const timer1_t* _timer1);
Std_ReturnType Timer1_Write_Value(const timer1_t* _timer1, uint16 _value);
Std_ReturnType Timer1_Read_Value(const timer1_t* _timer1, uint16 *_value);


#endif	/* HAL_TIMER1_H */

