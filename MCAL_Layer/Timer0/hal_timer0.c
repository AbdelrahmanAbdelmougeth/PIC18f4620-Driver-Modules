/* 
 * File:   hal_timer0.h
 * Author: hp
 *
 * Created on 26 ?????, 2023, 05:22 ?
 */

#include "hal_timer0.h"

static inline void Timer0_prescaler_config(const timer0_t* _timer0);
static inline void Timer0_resolution_config(const timer0_t* _timer0);
static inline void Timer0_Mode_select(const timer0_t* _timer0);

static uint16 Timer0_preload = ZERO_INIT;

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void(* TMR0_InterruptHandler)(void) = NULL;       
#endif 

Std_ReturnType Timer0_Init(const timer0_t* _timer0){
    Std_ReturnType ret = E_OK;
    if(_timer0 == NULL){
        ret = E_NOT_OK;
    }else{
        /* Configure timer 0 */
        
        /* 1. Disable timer 0 */
        TIMER0_MODULE_DISABLE();
        
        /* 2. Timer0 Operation (Timer Mode) 
           3. Select timer 0 clock source to be (Internal instruction cycle clock (CLKO)) ? T0CS = 0 */
        Timer0_Mode_select(_timer0);
        
        /* 4. Select timer 0 resolution : 8-bit / 16-bit (T08BIT) ? T08BIT = 1 (8-Bit) / 0 (16-Bit) */
        Timer0_resolution_config(_timer0);
           
        /* 5. Enable timer 0 pre-scaler if needed ? PSA = 0
           ? Configure the pre-scaler value using (T0PS2:T0PS0) */
        Timer0_prescaler_config(_timer0);
        
        /* 6. Initialize the Timer0L and Timer0H if needed. */
        TMR0H = (uint8)((_timer0->timer0_preload_value) >> 8);
        TMR0L = (uint8)(_timer0->timer0_preload_value);
        Timer0_preload = _timer0->timer0_preload_value;
                
        /* 7. Enable the interrupt on overflow if needed (INTCON) and implement the timer 0 ISR
            ? Disable the interrupt on overflow for timer 0 (pooling mode)  */   
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER0_IterruptEnable();
            TMR0_InterruptHandler = _timer0->TMR0_InterruptHandler;
            TIMER0_IterruptFlagClear();
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                if(_timer0->priority == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_GobalInterruptLowEnable();
                    TIMER0_INTERRUPT_LowPrioritySet();
                }else if(_timer0->priority == INTERRUPT_HIGH_PRIORITY){
                    INTERRUPT_GobalInterruptHighEnable();
                    TIMER0_INTERRUPT_HighPrioritySet();
                }    
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable(); 
            #endif
        #endif

        /*  8. Enable timer 0 */
        TIMER0_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType Timer0_DeInit(const timer0_t* _timer0){
    Std_ReturnType ret = E_OK;
    if(_timer0 == NULL){
        ret = E_NOT_OK;
    }else{
        TIMER0_MODULE_DISABLE();
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER0_IterruptDisable();
        #endif
    }
    return ret;
}

Std_ReturnType Timer0_Write_Value(const timer0_t* _timer0, uint16 _value){
    Std_ReturnType ret = E_OK;
    if(_timer0 == NULL){
        ret = E_NOT_OK;
    }else{
       TMR0H = (uint8)((_value) >> 8);
       TMR0L = (uint8)(_value);
    }
    return ret;
}

Std_ReturnType Timer0_Read_Value(const timer0_t* _timer0, uint16 *_value){
    Std_ReturnType ret = E_OK;
    uint8 l_tmr0_l,l_tmr0_h;
    if(_timer0 == NULL || _value == NULL){
        ret = E_NOT_OK;
    }else{
        l_tmr0_l = TMR0L;
        l_tmr0_h = TMR0H;
        *_value = (uint16)((l_tmr0_h << 8) + l_tmr0_l);
    }
    return ret;
}


void TMR0_ISR(void){
    /* The Internal ADC Interrupt has been occurred (must be cleared in software) */ 
    TIMER0_IterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context*/
    TMR0H = (uint8)((Timer0_preload) >> 8);
    TMR0L = (uint8)(Timer0_preload);
    /* Callback function gets called every time this ISR executes*/
    if(TMR0_InterruptHandler){
        TMR0_InterruptHandler();
    }
}

static inline void Timer0_prescaler_config(const timer0_t* _timer0){
    if(_timer0->prescaler_enable == TIMER0_PRESCALER_ENABLED){
        TIMER0_PRESCALER_ENABLE();
        TIMER0_PRESCALER_SET(_timer0->prescaler_value);
    }else if (_timer0->prescaler_enable == TIMER0_PRESCALER_DISABLED){
        TIMER0_PRESCALER_DISABLE();
    }else{/*nothing*/}   
}

static inline void Timer0_resolution_config(const timer0_t* _timer0){
    if(_timer0->timer0_register_size == TIMER0_16BIT_REGISTER_ENABLED){
        TIMER0_16BIT_REGISTER_ENABLE();
    }else if (_timer0->timer0_register_size == TIMER0_8BIT_REGISTER_ENABLED){
        TIMER0_8BIT_REGISTER_ENABLE();
    }else{/*nothing*/}  
}

static inline void Timer0_Mode_select(const timer0_t* _timer0){
    if(_timer0->timer0_mode == TIMER0_COUNTER_MODE){
        TIMER0_COUNTER_MODE_ENABLE();
    }else if (_timer0->timer0_mode == TIMER0_TIMER_MODE){
        TIMER0_TIMER_MODE_ENABLE();
        if(_timer0->source_edge_select == TIMER0_INCREMENT_ON_FALLING_EDGE){
            TIMER0_FALLING_EDGE_ENABLE();
        }else if(_timer0->source_edge_select == TIMER0_INCREMENT_ON_RISING_EDGE){
            TIMER0_RISING_EDGE_ENABLE();
        }else{/* nothing */}
    }else{/*nothing*/}  
}