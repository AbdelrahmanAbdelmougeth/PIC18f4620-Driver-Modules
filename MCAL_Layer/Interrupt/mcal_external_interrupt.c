/* 
 * File:   mcal_external_interrupt.c
 * Author: hp
 *
 * Created on 26 ?????, 2023, 03:46 ?
 */

#include "mcal_external_interrupt.h"

static void(* INT0_InterruptHandler)(void) = NULL;
static void(* INT1_InterruptHandler)(void) = NULL;
static void(* INT2_InterruptHandler)(void) = NULL;

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t* int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t* int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t* int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t* int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t* int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t* int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t* int_obj);

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t* int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t* int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t* int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t* int_obj);

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t* int_obj){
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }else{
       /*Disable The External Interrupt*/
        ret = Interrupt_INTx_Disable(int_obj);
       /*Clear Interrupt Flag : External Interrupt did not occur*/
        ret = Interrupt_INTx_Clear_Flag(int_obj);
       /*Configure External Interrupt edge*/
        ret = Interrupt_INTx_Edge_Init(int_obj);
       /*Configure External Interrupt priority*/ 
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        ret = Interrupt_INTx_Priority_Init(int_obj);
        #endif
       /*Configure External Interrupt I/O Pin*/ 
        ret = Interrupt_INTx_Pin_Init(int_obj);
       /*Configure Default Interrupt callback*/ 
        ret = Interrupt_INTx_SetInterruptHandler(int_obj);
       /*Enable The External Interrupt*/
        ret = Interrupt_INTx_Enable(int_obj);
    }
    return ret;
}


void INT0_ISR(void){
    /* The INT0 External Interrupt has been occurred (must be cleared in software) */ 
    EXT_INT0_IterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context*/
    
    /* Callback function gets called every time this ISR executes*/
    if(INT0_InterruptHandler){ INT0_InterruptHandler(); }
    else{/*Nothing*/}
}

void INT1_ISR(void){
    /* The INT1 External Interrupt has been occurred (must be cleared in software) */ 
    EXT_INT1_IterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context*/
    
    /* Callback function gets called every time this ISR executes*/
    if(INT1_InterruptHandler){ INT1_InterruptHandler(); }
    else{/*Nothing*/}
}

void INT2_ISR(void){
    /* The INT2 External Interrupt has been occurred (must be cleared in software) */ 
    EXT_INT2_IterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context*/
    
    /* Callback function gets called every time this ISR executes*/
    if(INT2_InterruptHandler){ INT2_InterruptHandler(); }
    else{/*Nothing*/}
}

Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t* int_obj){
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }else{
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret;
}

Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t* int_obj){
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }else{
        
    }
    return ret;
}

Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t* int_obj){
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }else{
        
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t* int_obj){
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_GobalInterruptHighEnable();
                #else
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT0_IterruptEnable(); 
                break;
            case INTERRUPT_EXTERNAL_INT1:
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriorityLevelsEnable();
                    if(int_obj->priority == INTERRUPT_LOW_PRIORITY){INTERRUPT_GobalInterruptLowEnable();}
                    else if(int_obj->priority == INTERRUPT_HIGH_PRIORITY){INTERRUPT_GobalInterruptHighEnable();}
                    else{/*nothing*/} 
                #else
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT1_IterruptEnable(); 
                break;            
            case INTERRUPT_EXTERNAL_INT2: 
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriorityLevelsEnable();
                    if(int_obj->priority == INTERRUPT_LOW_PRIORITY){INTERRUPT_GobalInterruptLowEnable();}
                    else if(int_obj->priority == INTERRUPT_HIGH_PRIORITY){INTERRUPT_GobalInterruptHighEnable();}
                    else{/*nothing*/} 
                #else
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT2_IterruptEnable();
                break;            
            default: ret = E_NOT_OK; break;    
        }
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t* int_obj){
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0: EXT_INT0_IterruptDisable(); break;
            case INTERRUPT_EXTERNAL_INT1: EXT_INT1_IterruptDisable(); break;            
            case INTERRUPT_EXTERNAL_INT2: EXT_INT2_IterruptDisable(); break;            
            default: ret = E_NOT_OK; break;    
        }
    }
    return ret;
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t* int_obj){
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }else{
         switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT1: 
                if(int_obj->priority == INTERRUPT_LOW_PRIORITY){EXT_INT1_LowPrioritySet();}
                else if(int_obj->priority == INTERRUPT_HIGH_PRIORITY){EXT_INT1_HighPrioritySet();}
                else{/*nothing*/} 
                break;            
            case INTERRUPT_EXTERNAL_INT2: 
                if(int_obj->priority == INTERRUPT_LOW_PRIORITY){EXT_INT2_LowPrioritySet();}
                else if(int_obj->priority == INTERRUPT_HIGH_PRIORITY){EXT_INT2_HighPrioritySet();}
                else{/*nothing*/} 
                break;            
            default: ret = E_NOT_OK; break;    
        }
    }
    return ret;
}
#endif

static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t* int_obj){
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0: 
                if(int_obj->edge == INTERRUPT_FALLING_EDGE){EXT_INT0_FallingEdgeSet();}
                else if(int_obj->edge == INTERRUPT_RISING_EDGE){EXT_INT0_RisingEdgeSet();}
                else{/*nothing*/} 
                break;
            case INTERRUPT_EXTERNAL_INT1: 
                if(int_obj->edge == INTERRUPT_FALLING_EDGE){EXT_INT1_FallingEdgeSet();}
                else if(int_obj->edge == INTERRUPT_RISING_EDGE){EXT_INT1_RisingEdgeSet();}
                else{/*nothing*/} 
                break;            
            case INTERRUPT_EXTERNAL_INT2: 
                 if(int_obj->edge == INTERRUPT_FALLING_EDGE){EXT_INT2_FallingEdgeSet();}
                else if(int_obj->edge == INTERRUPT_RISING_EDGE){EXT_INT2_RisingEdgeSet();}
                else{/*nothing*/} 
                break;            
            default: ret = E_NOT_OK; break;    
        }
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t* int_obj){
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t* int_obj){
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0: EXT_INT0_IterruptFlagClear(); break;
            case INTERRUPT_EXTERNAL_INT1: EXT_INT1_IterruptFlagClear(); break;            
            case INTERRUPT_EXTERNAL_INT2: EXT_INT2_IterruptFlagClear(); break;            
            default: ret = E_NOT_OK; break;    
        }
    }
    return ret;
}


static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if(InterruptHandler == NULL){
        ret = E_NOT_OK;
    }else{
       INT0_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if(InterruptHandler == NULL){
        ret = E_NOT_OK;
    }else{
       INT1_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if(InterruptHandler == NULL){
        ret = E_NOT_OK;
    }else{
       INT2_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t* int_obj){
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0: ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler); break;
            case INTERRUPT_EXTERNAL_INT1: ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler); break;            
            case INTERRUPT_EXTERNAL_INT2: ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler); break;            
            default: ret = E_NOT_OK; break;    
        }
    }
    return ret;
}