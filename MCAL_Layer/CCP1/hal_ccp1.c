/* 
 * File:   hal_ccp1.c
 * Author: hp
 *
 * Created on 02 ??????, 2023, 08:53 ?
 */

#include "hal_ccp1.h"
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void(* CCP1_InterruptHandler)(void) = NULL;       
#endif 

Std_ReturnType CCP1_Init(const ccp1_t* _ccp_obj){
    Std_ReturnType ret = E_OK;
    if(_ccp_obj == NULL){
        ret = E_NOT_OK;
    }else{
        /* CCP1 Module Disable */
        CCP1_SET_MODE(CCP1_MODULE_DISABLED);
        
        if(_ccp_obj->ccp1_mode == CCP1_CAPTURE_MODE_SELECTED){
            switch(_ccp_obj->ccp1_mode_varient){
                case CCP1_CAPTURE_MODE_1_FALLING_EDGE: CCP1_SET_MODE(CCP1_CAPTURE_MODE_1_FALLING_EDGE); break;
                case CCP1_CAPTURE_MODE_1_RISING_EDGE : CCP1_SET_MODE(CCP1_CAPTURE_MODE_1_RISING_EDGE);  break;
                case CCP1_CAPTURE_MODE_4_RISING_EDGE : CCP1_SET_MODE(CCP1_CAPTURE_MODE_4_RISING_EDGE);  break;
                case CCP1_CAPTURE_MODE_16_RISING_EDGE: CCP1_SET_MODE(CCP1_CAPTURE_MODE_16_RISING_EDGE); break;
                default: ret = E_NOT_OK;
            }  
        }else if(_ccp_obj->ccp1_mode == CCP1_COMPARE_MODE_SELECTED){
            switch(_ccp_obj->ccp1_mode_varient){
                case CCP1_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP1_SET_MODE(CCP1_COMPARE_MODE_TOGGLE_ON_MATCH);   break;
                case CCP1_COMPARE_MODE_SET_PIN_LOW      : CCP1_SET_MODE(CCP1_COMPARE_MODE_SET_PIN_LOW);       break;
                case CCP1_COMPARE_MODE_SET_PIN_HIGH     : CCP1_SET_MODE(CCP1_COMPARE_MODE_SET_PIN_HIGH);      break;
                case CCP1_COMPARE_MODE_GEN_SW_INTERRUPT : CCP1_SET_MODE(CCP1_COMPARE_MODE_GEN_SW_INTERRUPT);  break;
                case CCP1_COMPARE_MODE_GEN_SPECIAL_EVENT: CCP1_SET_MODE(CCP1_COMPARE_MODE_GEN_SPECIAL_EVENT); break;
                default: ret = E_NOT_OK;
            }  
        }else if(_ccp_obj->ccp1_mode == CCP1_PWM_MODE_SELECTED){
            #if CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED
                switch(_ccp_obj->ccp1_mode_varient){
                    case CCP1_PWM_MODE: CCP1_SET_MODE(CCP1_PWM_MODE); break;
                    default: ret = E_NOT_OK;
                }
                PR2 = (uint8)((_XTAL_FREQ / (_ccp_obj->PWM_frequency * 4.0 * _ccp_obj->timer2_postscaler_value * 
                        _ccp_obj->timer2_prescaler_value)) - 1);
            #endif
        }else{/* nothing */} 
        
        /* pin configuration */
        gpio_pin_initialize(&(_ccp_obj->ccp_pin));
        
        /* Interrupt Configuration */
        #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP1_IterruptEnable();
            CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
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

Std_ReturnType CCP1_DeInit(const ccp1_t* _ccp_obj){
    Std_ReturnType ret = E_OK;
    if(_ccp_obj == NULL){
        ret = E_NOT_OK;
    }else{
        /* CCP1 Module Disable */
        CCP1_SET_MODE(CCP1_MODULE_DISABLED);
        #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP1_IterruptDisable();
        #endif
    }
    return ret;
}


#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED

    Std_ReturnType CCP1_IsCapturedDataReady(uint8 *_capture_status){
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

    
#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELECTED
    
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
    
    

#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED
    
    Std_ReturnType CCP1_PWM1_Set_Duty(const uint8 _duty){
        Std_ReturnType ret = E_OK;
        uint16 l_duty_temp = (uint16)(((PR2+1) * (_duty / 100.0)) * 4);
        CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
        CCPR1L = (uint8)(l_duty_temp >> 2);
        return ret;
    }
    Std_ReturnType CCP1_PWM1_Start(void){
        Std_ReturnType ret = E_OK;
        CCP1_SET_MODE(CCP1_PWM_MODE);
        return ret;
    }
    Std_ReturnType CCP1_PWM1_Stop(void){
        Std_ReturnType ret = E_OK;
        CCP1_SET_MODE(CCP1_MODULE_DISABLED);
        return ret;
    }
    
#endif