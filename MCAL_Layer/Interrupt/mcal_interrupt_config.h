/* 
 * File:   mcal_interrupt_config.h
 * Author: hp
 *
 * Created on 26 ?????, 2023, 03:44 ?
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H


/* Section : Includes */
#include "../include/proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "mcal_interrupt_gen_cfg.h"

/* Section : Macro Declarations */
#define INTERRUPT_ENABLE    1
#define INTERRUPT_DISABLE   0
#define INTERRUPT_OCCUR     1
#define INTERRUPT_NOT_OCCUR 0
#define INTERRUPT_PRIORITY_ENABLE  1
#define INTERRUPT_PRIORITY_DISABLE 0

/* Section : Macro Functions Declarations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

/*This Macro Function will enable priority levels on interrupts*/
#define INTERRUPT_PriorityLevelsEnable()       (RCONbits.IPEN = 1)
/*This Macro Function will disable priority levels on interrupts*/
#define INTERRUPT_PriorityLevelsDisable()      (RCONbits.IPEN = 0)

/*This Macro Function will enable high priority global interrupts*/
#define INTERRUPT_GobalInterruptHighEnable()   (INTCONbits.GIEH = 1)
/*This Macro Function will disable high priority global interrupts*/
#define INTERRUPT_GobalInterruptHighDisable()  (INTCONbits.GIEH = 0)

/*This Macro Function will enable low priority global interrupts*/
#define INTERRUPT_GobalInterruptLowEnable()    (INTCONbits.GIEL = 1)
/*This Macro Function will disable low priority global interrupts*/
#define INTERRUPT_GobalInterruptLowDisable()   (INTCONbits.GIEL = 0)

#else

/*This Macro will enable global interrupt*/
#define INTERRUPT_GlobalInterruptEnable()      (INTCONbits.GIE = 1)
/*This Macro will disable global interrupt*/
#define INTERRUPT_GlobalInterruptDisable()     (INTCONbits.GIE = 0)
/*This Macro function will enable peripheral interrupts */
#define INTERRUPT_PeripheralInterruptEnable()  (INTCONbits.PEIE = 1)
/*This Macro function will disable peripheral interrupts */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

#endif


/* Section : Data-Type Declarations */
typedef enum{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY,         
}interrupt_periority_cfg;
/* Section : Function Declarations */

#endif	/* MCAL_INTERRUPT_CONFIG_H */

