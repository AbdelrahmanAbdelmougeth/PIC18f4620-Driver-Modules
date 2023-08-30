/* 
 * File:   hal_timer1.h
 * Author: hp
 *
 * Created on 30 ?????, 2023, 12:00 ?
 */

#include "hal_timer1.h"

#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void(* TMR1_InterruptHandler)(void) = NULL;       
#endif 
static uint16 Timer1_preload = ZERO_INIT;

static inline void Timer1_Mode_select(const timer1_t* _timer1);



Std_ReturnType Timer1_Init(const timer1_t* _timer1){
    Std_ReturnType ret = E_OK;
    if(_timer1 == NULL){
        ret = E_NOT_OK;
    }else{
        
        /* Configure timer 1 */
       
        /* 1. Disable timer 1 */
        TIMER1_MODULE_DISABLE();
        
        /* 2. Timer1 Operation (Timer Mode) 
           3. Select timer 1 clock source to be (Internal instruction cycle clock (CLKO)) ? T0CS = 0 */
        Timer1_Mode_select(_timer1);
 
        /* 4. Enable timer 0 pre-scaler if needed ? PSA = 0
           ? Configure the pre-scaler value using (T0PS2:T0PS0) */
        TIMER1_PRESCALER_SET(_timer1->timer1_prescaler_value);
        
        /* 5. Initialize the Timer1L and Timer1H if needed. */
        TMR1H = (uint8)((_timer1->timer1_preload_value) >> 8);
        TMR1L = (uint8)(_timer1->timer1_preload_value);
        Timer1_preload = _timer1->timer1_preload_value;

        
        /* 6. Enable the interrupt on overflow if needed (INTCON) and implement the timer 1 ISR
            ? Disable the interrupt on overflow for timer 1 (pooling mode)  */   
        #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER1_IterruptEnable();
            TMR1_InterruptHandler = _timer1->TMR1_InterruptHandler;
            TIMER1_IterruptFlagClear();
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                if(_timer1->priority == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_GobalInterruptLowEnable();
                    TIMER1_INTERRUPT_LowPrioritySet();
                }else if(_timer1->priority == INTERRUPT_HIGH_PRIORITY){
                    INTERRUPT_GobalInterruptHighEnable();
                    TIMER1_INTERRUPT_HighPrioritySet();
                }    
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable(); 
            #endif
        #endif

        /*  7. Enable timer 1 */
        TIMER1_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType Timer1_DeInit(const timer1_t* _timer1){
    Std_ReturnType ret = E_OK;
    if(_timer1 == NULL){
        ret = E_NOT_OK;
    }else{
        TIMER1_MODULE_DISABLE();
        #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER1_IterruptDisable();
        #endif
    }
    return ret;
}

Std_ReturnType Timer1_Write_Value(const timer1_t* _timer1, uint16 _value){
    Std_ReturnType ret = E_OK;
    if(_timer1 == NULL){
        ret = E_NOT_OK;
    }else{
       TMR1H = (uint8)((_value) >> 8);
       TMR1L = (uint8)(_value);
    }
    return ret;
}

Std_ReturnType Timer1_Read_Value(const timer1_t* _timer1, uint16 *_value){
    Std_ReturnType ret = E_OK;
    uint8 l_tmr1_l,l_tmr1_h;
    if(_timer1 == NULL || _value == NULL){
        ret = E_NOT_OK;
    }else{
        l_tmr1_l = TMR1L;
        l_tmr1_h = TMR1H;
        *_value = (uint16)((l_tmr1_h << 8) + l_tmr1_l);
    }
    return ret;
}

void TMR1_ISR(void){
    /* The Internal ADC Interrupt has been occurred (must be cleared in software) */ 
    TIMER1_IterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context*/
    TMR1H = (uint8)((Timer1_preload) >> 8);
    TMR1L = (uint8)(Timer1_preload);
    /* Callback function gets called every time this ISR executes*/
    if(TMR1_InterruptHandler){
        TMR1_InterruptHandler();
    }
}



static inline void Timer1_Mode_select(const timer1_t* _timer1){
    if(_timer1->timer1_mode == TIMER1_TIMER_MODE){
        TIMER1_TIMER_MODE_ENABLE();
    }else if (_timer1->timer1_mode == TIMER1_COUNTER_MODE){
        TIMER1_COUNTER_MODE_ENABLE();
        if(_timer1->timer1_osc_cfg == TIMER1_SYNC_COUNTER_MODE){
           TIMER1_SYNC_COUNTER_MODE_ENABLE(); 
        }else if(_timer1->timer1_osc_cfg == TIMER1_ASYNC_COUNTER_MODE){
           TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }else{/* nothing */}
    }else{/* nothing */}  
}