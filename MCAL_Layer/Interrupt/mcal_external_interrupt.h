/* 
 * File:   mcal_external_interrupt.h
 * Author: hp
 *
 * Created on 26 ?????, 2023, 03:46 ?
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Section : Includes */
#include "mcal_interrupt_config.h"


/* Section : Macro Declarations */
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/*This Macro Will Enable The External INT0 Interrupt*/
#define EXT_INT0_IterruptEnable()      (INTCONbits.INT0IE = 1)
/*This Macro Will Disable The External INT0 Interrupt*/
#define EXT_INT0_IterruptDisable()     (INTCONbits.INT0IE = 0)
/*This Macro Will Clear The External INT0 Flag Bit*/
#define EXT_INT0_IterruptFlagClear()   (INTCONbits.INT0IF = 0)
/*This Macro Will set External INT0 Interrupt To Fire on rising edge*/
#define EXT_INT0_RisingEdgeSet()       (INTCON2bits.INTEDG0 = 1)
/*This Macro Will set External INT0 Interrupt To Fire on falling edge*/
#define EXT_INT0_FallingEdgeSet()      (INTCON2bits.INTEDG0 = 0)


/*This Macro Will Enable The External INT1 Interrupt*/
#define EXT_INT1_IterruptEnable()      (INTCON3bits.INT1IE = 1)
/*This Macro Will Disable The External INT1 Interrupt*/
#define EXT_INT1_IterruptDisable()     (INTCON3bits.INT1IE = 0)
/*This Macro Will Clear The External INT1 Flag Bit*/
#define EXT_INT1_IterruptFlagClear()   (INTCON3bits.INT1IF = 0)
/*This Macro Will set External INT1 Interrupt To Fire on rising edge*/
#define EXT_INT1_RisingEdgeSet()       (INTCON2bits.INTEDG1 = 1)
/*This Macro Will set External INT1 Interrupt To Fire on falling edge*/
#define EXT_INT1_FallingEdgeSet()      (INTCON2bits.INTEDG1 = 0)


/*This Macro Will Enable The External INT2 Interrupt*/
#define EXT_INT2_IterruptEnable()      (INTCON3bits.INT2IE = 1)
/*This Macro Will Disable The External INT2 Interrupt*/
#define EXT_INT2_IterruptDisable()     (INTCON3bits.INT2IE = 0)
/*This Macro Will Clear The External INT2 Flag Bit*/
#define EXT_INT2_IterruptFlagClear()   (INTCON3bits.INT2IF = 0)
/*This Macro Will set External INT2 Interrupt To Fire on rising edge*/
#define EXT_INT2_RisingEdgeSet()       (INTCON2bits.INTEDG2 = 1)
/*This Macro Will set External INT2 Interrupt To Fire on falling edge*/
#define EXT_INT2_FallingEdgeSet()      (INTCON2bits.INTEDG2 = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*This Macro will set the External INT1 Interrupt priority to be high*/
#define EXT_INT1_HighPrioritySet() (INTCON3bits.INT1IP = 1)
/*This Macro will set the External INT1 Interrupt priority to be low*/
#define EXT_INT1_LowPrioritySet()  (INTCON3bits.INT1IP = 0)
/*This Macro will set the External INT2 Interrupt priority to high*/
#define EXT_INT2_HighPrioritySet() (INTCON3bits.INT2IP = 1)
/*This Macro will set the External INT2 Interrupt priority to low*/
#define EXT_INT2_LowPrioritySet()  (INTCON3bits.INT2IP = 0)
#endif

#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/*This Macro Will Disable The External RBx Interrupt*/
#define EXT_RBx_InterruptDisable()     (INTCONbits.RBIE = 0)
/*This Macro Will Enable The External RBx Interrupt*/
#define EXT_RBx_InterruptEnable()      (INTCONbits.RBIE = 1)
/*This Macro Will Clear The External RBx Flag Bit*/
#define EXT_RBx_IterruptFlagClear()    (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*This Macro will set the External RBx Interrupt priority to high*/
#define EXT_RBx_HighPrioritySet()  (INTCON2bits.RBIP = 1)
/*This Macro will set the External RBx Interrupt priority to low*/
#define EXT_RBx_LowPrioritySet()   (INTCON2bits.RBIP = 0)
#endif

#endif

/* Section : Macro Functions Declarations */

/* Section : Data-Type Declarations */
typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE        
}interrupt_INTx_edge;

typedef enum{
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2,         
}interrupt_INTx_src;

typedef struct{
    void(* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_src source;
    interrupt_periority_cfg priority;
}interrupt_INTx_t;

typedef struct{
    void(* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_periority_cfg priority;
}interrupt_RBx_t;

/* Section : Function Declarations */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t* int_obj);
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t* int_obj);
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t* int_obj);
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t* int_obj);


#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

