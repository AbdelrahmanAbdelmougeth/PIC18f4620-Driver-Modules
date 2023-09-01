/* 
 * File:   hal_timer3.h
 * Author: hp
 *
 * Created on 31 ?????, 2023, 10:30 ?
 */

#include "hal_timer3.h"

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void(* TMR3_InterruptHandler)(void) = NULL;       
#endif 
static uint16 Timer3_preload = ZERO_INIT;

static inline void Timer3_Mode_select(const timer3_t* _timer3);

Std_ReturnType Timer3_Init(const timer3_t* _timer3){
    Std_ReturnType ret = E_OK;
    if(_timer3 == NULL){
        ret = E_NOT_OK;
    }else{
        
        /* Configure timer 3 */
       
        /* 1. Disable timer 3 */
        TIMER3_MODULE_DISABLE();
        
        /* 2. Timer3 Operation (Timer Mode) 
           3. Select timer 3 clock source to be (Internal instruction cycle clock (T13CKI)) ? TMR3CS = 0 */
        Timer3_Mode_select(_timer3);
 
        /* 4. Enable timer 3 pre-scaler if needed ? PSA = 0
           ? Configure the pre-scaler value using (T3CKPS1:T3CKPS0) */
        TIMER3_PRESCALER_SET(_timer3->timer3_prescaler_value);
        
        /* 5. Initialize the Timer3L and Timer3H if needed. */
        TMR3H = (uint8)((_timer3->timer3_preload_value) >> 8);
        TMR3L = (uint8)(_timer3->timer3_preload_value);
        Timer3_preload = _timer3->timer3_preload_value;

        
        /* 6. Enable the interrupt on overflow if needed (INTCON) and implement the timer 3 ISR
            ? Disable the interrupt on overflow for timer 3 (pooling mode)  */   
        #if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER3_IterruptEnable();
            TMR3_InterruptHandler = _timer3->TMR3_InterruptHandler;
            TIMER3_IterruptFlagClear();
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                if(_timer3->priority == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_GobalInterruptLowEnable();
                    TIMER3_INTERRUPT_LowPrioritySet();
                }else if(_timer3->priority == INTERRUPT_HIGH_PRIORITY){
                    INTERRUPT_GobalInterruptHighEnable();
                    TIMER3_INTERRUPT_HighPrioritySet();
                }    
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable(); 
            #endif
        #endif

        /*  7. Enable timer 3 */
        TIMER3_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType Timer3_DeInit(const timer3_t* _timer3){
    Std_ReturnType ret = E_OK;
    if(_timer3 == NULL){
        ret = E_NOT_OK;
    }else{
        TIMER3_MODULE_DISABLE();
        #if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER3_IterruptDisable();
        #endif
    }
    return ret;
}

Std_ReturnType Timer3_Write_Value(const timer3_t* _timer3, uint16 _value){
    Std_ReturnType ret = E_OK;
    if(_timer3 == NULL){
        ret = E_NOT_OK;
    }else{
       TMR3H = (uint8)((_value) >> 8);
       TMR3L = (uint8)(_value);
    }
    return ret;
    
}

Std_ReturnType Timer3_Read_Value(const timer3_t* _timer3, uint16 *_value){
    Std_ReturnType ret = E_OK;
    uint8 l_tmr3_l,l_tmr3_h;
    if(_timer3 == NULL || _value == NULL){
        ret = E_NOT_OK;
    }else{
        l_tmr3_l = TMR3L;
        l_tmr3_h = TMR3H;
        *_value = (uint16)((l_tmr3_h << 8) + l_tmr3_l);
    }
    return ret;
}

void TMR3_ISR(void){
    /* The Internal ADC Interrupt has been occurred (must be cleared in software) */ 
    TIMER3_IterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context*/
    TMR3H = (uint8)((Timer3_preload) >> 8);
    TMR3L = (uint8)(Timer3_preload);
    /* Callback function gets called every time this ISR executes*/
    if(TMR3_InterruptHandler){
        TMR3_InterruptHandler();
    }
}

static inline void Timer3_Mode_select(const timer3_t* _timer3){
    if(_timer3->timer3_mode == TIMER3_TIMER_MODE){
        TIMER3_TIMER_MODE_ENABLE();
    }else if (_timer3->timer3_mode == TIMER3_COUNTER_MODE){
        TIMER3_COUNTER_MODE_ENABLE();
        if(_timer3->timer3_counter_mode == TIMER3_SYNC_COUNTER_MODE){
           TIMER3_SYNC_COUNTER_MODE_ENABLE(); 
        }else if(_timer3->timer3_counter_mode == TIMER3_ASYNC_COUNTER_MODE){
           TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }else{/* nothing */}
    }else{/* nothing */}  
}