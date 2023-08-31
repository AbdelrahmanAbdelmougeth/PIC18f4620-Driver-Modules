/* 
 * File:   mcal_internal_interrupt.h
 * Author: hp
 *
 * Created on 26 ?????, 2023, 03:45 ?
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H


/* Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macro Declarations */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /*This Macro Will Enable The Internal ADC Interrupt*/
    #define ADC_IterruptEnable()      (PIE1bits.ADIE = 1)
    /*This Macro Will Disable The Internal ADC Interrupt*/
    #define ADC_IterruptDisable()     (PIE1bits.ADIE = 0)
    /*This Macro Will Clear The Internal ADC Flag Bit*/
    #define ADC_IterruptFlagClear()   (PIR1bits.ADIF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        /*This Macro will set the Internal ADC Interrupt priority to be high*/
        #define ADC_INTERRUPT_HighPrioritySet() (IPR1bits.ADIP = 1)
        /*This Macro will set the Internal ADC Interrupt priority to be low*/
        #define ADC_INTERRUPT_LowPrioritySet()  (IPR1bits.ADIP = 0)
    #endif

#endif 


#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /*This Macro Will Enable The Internal TIMER0 Interrupt*/
    #define TIMER0_IterruptEnable()      (INTCONbits.T0IE = 1)
    /*This Macro Will Disable The Internal TIMER0 Interrupt*/
    #define TIMER0_IterruptDisable()     (INTCONbits.T0IE = 0)
    /*This Macro Will Clear The Internal TIMER0 Flag Bit*/
    #define TIMER0_IterruptFlagClear()   (INTCONbits.T0IF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        /*This Macro will set the Internal TIMER0 Interrupt priority to be high*/
        #define TIMER0_INTERRUPT_HighPrioritySet() (INTCON2bits.TMR0IP = 1)
        /*This Macro will set the Internal TIMER0 Interrupt priority to be low*/
        #define TIMER0_INTERRUPT_LowPrioritySet()  (INTCON2bits.TMR0IP = 0)
    #endif

#endif

#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /*This Macro Will Enable The Internal TIMER1 Interrupt*/
    #define TIMER1_IterruptEnable()      (PIE1bits.TMR1IE = 1)
    /*This Macro Will Disable The Internal TIMER1 Interrupt*/
    #define TIMER1_IterruptDisable()     (PIE1bits.TMR1IE = 0)
    /*This Macro Will Clear The Internal TIMER1 Flag Bit*/
    #define TIMER1_IterruptFlagClear()   (PIR1bits.TMR1IF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        /*This Macro will set the Internal TIMER1 Interrupt priority to be high*/
        #define TIMER1_INTERRUPT_HighPrioritySet() (IPR1bits.TMR1IP = 1)
        /*This Macro will set the Internal TIMER1 Interrupt priority to be low*/
        #define TIMER1_INTERRUPT_LowPrioritySet()  (IPR1bits.TMR1IP = 0)
    #endif

#endif

#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /*This Macro Will Enable The Internal TIMER2 Interrupt*/
    #define TIMER2_IterruptEnable()      (PIE1bits.TMR2IE = 1)
    /*This Macro Will Disable The Internal TIMER2 Interrupt*/
    #define TIMER2_IterruptDisable()     (PIE1bits.TMR2IE = 0)
    /*This Macro Will Clear The Internal TIMER2 Flag Bit*/
    #define TIMER2_IterruptFlagClear()   (PIR1bits.TMR2IF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        /*This Macro will set the Internal TIMER2 Interrupt priority to be high*/
        #define TIMER2_INTERRUPT_HighPrioritySet() (IPR1bits.TMR2IP = 1)
        /*This Macro will set the Internal TIMER2 Interrupt priority to be low*/
        #define TIMER2_INTERRUPT_LowPrioritySet()  (IPR1bits.TMR2IP = 0)
    #endif

#endif

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /*This Macro Will Enable The Internal TIMER3 Interrupt*/
    #define TIMER3_IterruptEnable()      (PIE2bits.TMR3IE = 1)
    /*This Macro Will Disable The Internal TIMER3 Interrupt*/
    #define TIMER3_IterruptDisable()     (PIE2bits.TMR3IE = 0)
    /*This Macro Will Clear The Internal TIMER3 Flag Bit*/
    #define TIMER3_IterruptFlagClear()   (PIR2bits.TMR3IF = 0)
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        /*This Macro will set the Internal TIMER3 Interrupt priority to be high*/
        #define TIMER3_INTERRUPT_HighPrioritySet() (IPR2bits.TMR3IP = 1)
        /*This Macro will set the Internal TIMER3 Interrupt priority to be low*/
        #define TIMER3_INTERRUPT_LowPrioritySet()  (IPR2bits.TMR3IP = 0)
    #endif

#endif

/* Section : Macro Functions Declarations */

/* Section : Data-Type Declarations */

/* Section : Function Declarations */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

