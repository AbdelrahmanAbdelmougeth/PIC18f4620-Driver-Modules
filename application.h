/* 
 * File:   application.h
 * Author: abdo9
 *
 * Created on May 15, 2023, 1:37 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H


/* Section : Includes */
#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "MCAL_Layer/hal_adc.h"
#include "MCAL_Layer/Timer0/hal_timer0.h"
#include "MCAL_Layer/Timer1/hal_timer1.h"
#include "MCAL_Layer/Timer2/hal_timer2.h"
#include "MCAL_Layer/Timer3/hal_timer3.h"
#include "MCAL_Layer/CCP1/hal_ccp1.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data-Type Declarations */

/* Section : Function Declarations */
void application_initialize();

#endif	/* APPLICATION_H */

