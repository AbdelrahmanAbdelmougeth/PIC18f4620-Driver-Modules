/* 
 * File:   hal_timer2.h
 * Author: hp
 *
 * Created on 31 ?????, 2023, 10:30 ?
 */

#include "hal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void(* TMR2_InterruptHandler)(void) = NULL;       
#endif 
static uint8 Timer2_preload_val = ZERO_INIT;


Std_ReturnType Timer2_Init(const timer2_t* _timer2){
    Std_ReturnType ret = E_OK;
    if(_timer2 == NULL){
        ret = E_NOT_OK;
    }else{
        /* Configure timer 2 */
       
        /* 1. Disable timer 2 */
        TIMER2_MODULE_DISABLE();
        
        /* 2. set timer 2 pre-scaler
           ? Configure the pre-scaler value using (T2CKPS1:T2CKPS0) */
        TIMER2_PRESCALER_SELECT(_timer2->timer2_prescaler_value);
                
        /* 3. set timer 2 post-scaler
           ? Configure the pre-scaler value using (T2OUTPS3:T2OUTPS0) */
        TIMER2_POSTSCALER_SELECT(_timer2->timer2_postscaler_value);
           
        /* 4. Initialize the Timer2. */
        TMR2 = _timer2->timer2_preload_value;
        Timer2_preload_val = _timer2->timer2_preload_value;  

        /* 5. Enable the interrupt on overflow if needed (PIE1) and implement the timer 2 ISR
            ? Disable the interrupt on overflow for timer 2 (pooling mode)  */   
        #if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER2_IterruptEnable();
            TMR2_InterruptHandler = _timer2->TMR2_InterruptHandler;
            TIMER2_IterruptFlagClear();
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                if(_timer2->priority == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_GobalInterruptLowEnable();
                    TIMER2_INTERRUPT_LowPrioritySet();
                }else if(_timer2->priority == INTERRUPT_HIGH_PRIORITY){
                    INTERRUPT_GobalInterruptHighEnable();
                    TIMER2_INTERRUPT_HighPrioritySet();
                }    
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable(); 
            #endif
        #endif

        /*  6. Enable timer 1 */
        TIMER2_MODULE_ENABLE();       
    }
    return ret;
}

Std_ReturnType Timer2_DeInit(const timer2_t* _timer2){
    Std_ReturnType ret = E_OK;
    if(_timer2 == NULL){
        ret = E_NOT_OK;
    }else{
        TIMER2_MODULE_DISABLE();
        #if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER2_IterruptDisable();
        #endif
    }
    return ret;
}

Std_ReturnType Timer2_Write_Value(const timer2_t* _timer2, uint8 _value){
    Std_ReturnType ret = E_OK;
    if(_timer2 == NULL){
        ret = E_NOT_OK;
    }else{
       TMR2 = _value;  
    }
    return ret;
}

Std_ReturnType Timer2_Read_Value(const timer2_t* _timer2, uint8 *_value){
    Std_ReturnType ret = E_OK;
    if(_timer2 == NULL){
        ret = E_NOT_OK;
    }else{
       *_value = TMR2;
    }
    return ret;
}

void TMR2_ISR(void){
    /* The Internal TMR2 Interrupt has been occurred (must be cleared in software) */ 
    TIMER2_IterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context*/
    TMR2 = Timer2_preload_val;
    /* Callback function gets called every time this ISR executes*/
    if(TMR2_InterruptHandler){
        TMR2_InterruptHandler();
    }
}