/* 
 * File:   hal_ccp1.c
 * Author: hp
 *
 * Created on 02 ??????, 2023, 08:53 ?
 */

#include "hal_ccpx.h"
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void(* CCP1_InterruptHandler)(void) = NULL;       
#endif 
    
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void(* CCP2_InterruptHandler)(void) = NULL;       
#endif 

static inline Std_ReturnType CCP1_Init(const ccpx_t* _ccp_obj);    
static inline Std_ReturnType CCP2_Init(const ccpx_t* _ccp_obj);    
    
    
Std_ReturnType CCPx_Init(const ccpx_t* _ccp_obj){
    Std_ReturnType ret = E_OK;
    if(_ccp_obj == NULL){
        ret = E_NOT_OK;
    }else{
        if(_ccp_obj->ccpx_inst == CCP1_INST){            
            ret = CCP1_Init(_ccp_obj);
        }else if(_ccp_obj->ccpx_inst == CCP2_INST){
            ret = CCP2_Init(_ccp_obj);
        }else{
            ret = E_NOT_OK;
        }     
    }
    return ret;
}

static inline Std_ReturnType CCP1_Init(const ccpx_t* _ccp_obj){
    Std_ReturnType ret = E_OK;
    if(_ccp_obj == NULL){
        ret = E_NOT_OK;
    }else{        
        /* CCPx Module Disable */
        CCP1_SET_MODE(CCPx_MODULE_DISABLED);

        if(_ccp_obj->ccpx_mode == CCPx_CAPTURE_MODE_SELECTED){
            switch(_ccp_obj->ccpx_mode_varient){
                case CCPx_CAPTURE_MODE_1_FALLING_EDGE: CCP1_SET_MODE(CCPx_CAPTURE_MODE_1_FALLING_EDGE); break;
                case CCPx_CAPTURE_MODE_1_RISING_EDGE : CCP1_SET_MODE(CCPx_CAPTURE_MODE_1_RISING_EDGE);  break;
                case CCPx_CAPTURE_MODE_4_RISING_EDGE : CCP1_SET_MODE(CCPx_CAPTURE_MODE_4_RISING_EDGE);  break;
                case CCPx_CAPTURE_MODE_16_RISING_EDGE: CCP1_SET_MODE(CCPx_CAPTURE_MODE_16_RISING_EDGE); break;
                default: ret = E_NOT_OK;
            }  
        }else if(_ccp_obj->ccpx_mode == CCPx_COMPARE_MODE_SELECTED){
            switch(_ccp_obj->ccpx_mode_varient){
                case CCPx_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP1_SET_MODE(CCPx_COMPARE_MODE_TOGGLE_ON_MATCH);   break;
                case CCPx_COMPARE_MODE_SET_PIN_LOW      : CCP1_SET_MODE(CCPx_COMPARE_MODE_SET_PIN_LOW);       break;
                case CCPx_COMPARE_MODE_SET_PIN_HIGH     : CCP1_SET_MODE(CCPx_COMPARE_MODE_SET_PIN_HIGH);      break;
                case CCPx_COMPARE_MODE_GEN_SW_INTERRUPT : CCP1_SET_MODE(CCPx_COMPARE_MODE_GEN_SW_INTERRUPT);  break;
                case CCPx_COMPARE_MODE_GEN_SPECIAL_EVENT: CCP1_SET_MODE(CCPx_COMPARE_MODE_GEN_SPECIAL_EVENT); break;
                default: ret = E_NOT_OK;
            }  
        }else if(_ccp_obj->ccpx_mode == CCPx_PWM_MODE_SELECTED){
            #if CCPx_CFG_SELECTED_MODE == CCPx_CFG_PWM_MODE_SELECTED
                switch(_ccp_obj->ccpx_mode_varient){
                    case CCPx_PWM_MODE: CCP1_SET_MODE(CCPx_PWM_MODE); break;
                    default: ret = E_NOT_OK;
                }
                PR2 = (uint8)((_XTAL_FREQ / (_ccp_obj->PWM_frequency * 4.0 * _ccp_obj->timer2_postscaler_value * 
                        _ccp_obj->timer2_prescaler_value)) - 1);
            #endif
        }else{/* nothing */} 

        /* pin configuration */
        gpio_pin_initialize(&(_ccp_obj->ccpx_pin));

        /* Interrupt Configuration */
        #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP1_IterruptEnable();
            CCP1_InterruptHandler = _ccp_obj->CCPx_InterruptHandler;
            CCP1_IterruptFlagClear();
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                if(_ccp_obj->priority == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_GobalInterruptLowEnable();
                    CCP1_INTERRUPT_LowPrioritySet();
                }else if(_ccp_obj->priority == INTERRUPT_HIGH_PRIORITY){
                    INTERRUPT_GobalInterruptHighEnable();
                    CCP1_INTERRUPT_HighPrioritySet();
                }    
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable(); 
            #endif
        #endif
    }
    return ret;
}    

static inline Std_ReturnType CCP2_Init(const ccpx_t* _ccp_obj){
    Std_ReturnType ret = E_OK;
    if(_ccp_obj == NULL){
        ret = E_NOT_OK;
    }else{
        /* CCPx Module Disable */
        CCP2_SET_MODE(CCPx_MODULE_DISABLED);

        if(_ccp_obj->ccpx_mode == CCPx_CAPTURE_MODE_SELECTED){
            switch(_ccp_obj->ccpx_mode_varient){
                case CCPx_CAPTURE_MODE_1_FALLING_EDGE: CCP2_SET_MODE(CCPx_CAPTURE_MODE_1_FALLING_EDGE); break;
                case CCPx_CAPTURE_MODE_1_RISING_EDGE : CCP2_SET_MODE(CCPx_CAPTURE_MODE_1_RISING_EDGE);  break;
                case CCPx_CAPTURE_MODE_4_RISING_EDGE : CCP2_SET_MODE(CCPx_CAPTURE_MODE_4_RISING_EDGE);  break;
                case CCPx_CAPTURE_MODE_16_RISING_EDGE: CCP2_SET_MODE(CCPx_CAPTURE_MODE_16_RISING_EDGE); break;
                default: ret = E_NOT_OK;
            }  
        }else if(_ccp_obj->ccpx_mode == CCPx_COMPARE_MODE_SELECTED){
            switch(_ccp_obj->ccpx_mode_varient){
                case CCPx_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP2_SET_MODE(CCPx_COMPARE_MODE_TOGGLE_ON_MATCH);   break;
                case CCPx_COMPARE_MODE_SET_PIN_LOW      : CCP2_SET_MODE(CCPx_COMPARE_MODE_SET_PIN_LOW);       break;
                case CCPx_COMPARE_MODE_SET_PIN_HIGH     : CCP2_SET_MODE(CCPx_COMPARE_MODE_SET_PIN_HIGH);      break;
                case CCPx_COMPARE_MODE_GEN_SW_INTERRUPT : CCP2_SET_MODE(CCPx_COMPARE_MODE_GEN_SW_INTERRUPT);  break;
                case CCPx_COMPARE_MODE_GEN_SPECIAL_EVENT: CCP2_SET_MODE(CCPx_COMPARE_MODE_GEN_SPECIAL_EVENT); break;
                default: ret = E_NOT_OK;
            }  
        }else if(_ccp_obj->ccpx_mode == CCPx_PWM_MODE_SELECTED){
            #if CCPx_CFG_SELECTED_MODE == CCPx_CFG_PWM_MODE_SELECTED
                switch(_ccp_obj->ccpx_mode_varient){
                    case CCPx_PWM_MODE: CCP2_SET_MODE(CCPx_PWM_MODE); break;
                    default: ret = E_NOT_OK;
                }
                PR2 = (uint8)((_XTAL_FREQ / (_ccp_obj->PWM_frequency * 4.0 * _ccp_obj->timer2_postscaler_value * 
                        _ccp_obj->timer2_prescaler_value)) - 1);
            #endif
        }else{/* nothing */} 

        /* pin configuration */
        gpio_pin_initialize(&(_ccp_obj->ccpx_pin));

        /* Interrupt Configuration */
        #if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP2_IterruptEnable();
            CCP2_InterruptHandler = _ccp_obj->CCPx_InterruptHandler;
            CCP2_IterruptFlagClear();
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                if(_ccp_obj->priority == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_GobalInterruptLowEnable();
                    CCP2_INTERRUPT_LowPrioritySet();
                }else if(_ccp_obj->priority == INTERRUPT_HIGH_PRIORITY){
                    INTERRUPT_GobalInterruptHighEnable();
                    CCP2_INTERRUPT_HighPrioritySet();
                }    
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable(); 
            #endif
        #endif
    }
    return ret;
} 


Std_ReturnType CCPx_DeInit(const ccpx_t* _ccp_obj){
    Std_ReturnType ret = E_OK;
    if(_ccp_obj == NULL){
        ret = E_NOT_OK;
    }else{
        if(_ccp_obj->ccpx_inst == CCP1_INST){
            /* CCP1 Module Disable */
            CCP1_SET_MODE(CCPx_MODULE_DISABLED);
            #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
                CCP1_IterruptDisable();
            #endif
        }else if(_ccp_obj->ccpx_inst == CCP2_INST){
            /* CCP2 Module Disable */
            CCP2_SET_MODE(CCPx_MODULE_DISABLED);
            #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
                CCP2_IterruptDisable();
            #endif
        }else{/* nothing */}        
    }
    return ret;
}


#if CCPx_CFG_SELECTED_MODE == CCPx_CFG_CAPTURE_MODE_SELECTED

    Std_ReturnType CCPx_IsCapturedDataReady(uint8 *_capture_status){
        Std_ReturnType ret = E_OK;
        if(_capture_status == NULL){
            ret = E_NOT_OK;
        }else{
            if(PIR1bits.CCP1IF == CCP1_CAPTURE_TRIGGERED){
                *_capture_status = CCP1_CAPTURE_TRIGGERED;
                CCP1_IterruptFlagClear();
            }else{
                *_capture_status = CCP1_CAPTURE_IDLE;
            }
        }
        return ret;
    }
    
    Std_ReturnType CCP1_Capture_Mode_Read_Value(uint16 *_captured_value){
        Std_ReturnType ret = E_OK;
        CCP1_PERIOD_REG_T ccpr1 = {.ccpr1_low = ZERO_INIT, .ccpr1_high = ZERO_INIT};
        if(_captured_value == NULL){
            ret = E_NOT_OK;
        }else{
            ccpr1.ccpr1_low = CCPR1L;
            ccpr1.ccpr1_high = CCPR1H;
            *_captured_value = ccpr1.ccpr1_16_bit;
        }
        return ret;             
    }
    
#endif

    
#if CCPx_CFG_SELECTED_MODE == CCPx_CFG_COMPARE_MODE_SELECTED
    
    Std_ReturnType CCP1_IsCompareTriggered(uint8 *_compare_status){
        Std_ReturnType ret = E_OK;
        if(_compare_status == NULL){
            ret = E_NOT_OK;
        }else{
            if(PIR1bits.CCP1IF == CCP1_COMPARE_TRIGGERED){
                *_compare_status = CCP1_COMPARE_TRIGGERED;
                CCP1_IterruptFlagClear();
            }else{
                *_compare_status = CCP1_COMPARE_IDLE;
            }
        }
        return ret;
    }
    
    Std_ReturnType CCP1_Compare_Mode_Write_Value(uint16 _compare_value){
        Std_ReturnType ret = E_OK;
        CCP1_PERIOD_REG_T ccpr1 = {.ccpr1_low = ZERO_INIT, .ccpr1_high = ZERO_INIT};
        ccpr1.ccpr1_16_bit = _compare_value;
        CCPR1L = ccpr1.ccpr1_low;
        CCPR1H = ccpr1.ccpr1_high;
        return ret;
    }
    
#endif
    
    

#if CCPx_CFG_SELECTED_MODE == CCPx_CFG_PWM_MODE_SELECTED
    
    Std_ReturnType CCPx_PWM_Set_Duty(const ccpx_t* _ccp_obj, const uint8 _duty){
        Std_ReturnType ret = E_OK;
        if(_ccp_obj == NULL){
            ret = E_NOT_OK;
        }else{
            uint16 l_duty_temp = (uint16)(((PR2+1) * (_duty / 100.0)) * 4);
            if(_ccp_obj->ccpx_inst == CCP1_INST){
                CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
                CCPR1L = (uint8)(l_duty_temp >> 2);
            }else if(_ccp_obj->ccpx_inst == CCP2_INST){
                CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003);
                CCPR2L = (uint8)(l_duty_temp >> 2);
            }else{/* nothing */}
        }        
        return ret;
    }
    Std_ReturnType CCPx_PWM_Start(const ccpx_t* _ccp_obj){
        Std_ReturnType ret = E_OK;
        if(_ccp_obj == NULL){
            ret = E_NOT_OK;
        }else{
            if(_ccp_obj->ccpx_inst == CCP1_INST){
                CCP1_SET_MODE(CCPx_PWM_MODE);
            }else if(_ccp_obj->ccpx_inst == CCP2_INST){
                CCP2_SET_MODE(CCPx_PWM_MODE);
            }else{/* nothing */}
        }
        
        return ret;
    }
    Std_ReturnType CCPx_PWM_Stop(const ccpx_t* _ccp_obj){
        Std_ReturnType ret = E_OK;
        if(_ccp_obj == NULL){
            ret = E_NOT_OK;
        }else{
            if(_ccp_obj->ccpx_inst == CCP1_INST){
                CCP1_SET_MODE(CCPx_MODULE_DISABLED);
            }else if(_ccp_obj->ccpx_inst == CCP2_INST){
                CCP2_SET_MODE(CCPx_MODULE_DISABLED);
            }else{/* nothing */}
        }
        return ret;
    }
    
#endif
    
void CCP1_ISR(void){
    /* The Internal CCP1 Interrupt has been occurred (must be cleared in software) */ 
    CCP1_IterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context*/
    /* Callback function gets called every time this ISR executes*/
    if(CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }
}

void CCP2_ISR(void){
    /* The Internal CCP1 Interrupt has been occurred (must be cleared in software) */ 
    CCP2_IterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context*/
    /* Callback function gets called every time this ISR executes*/
    if(CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    }
}    