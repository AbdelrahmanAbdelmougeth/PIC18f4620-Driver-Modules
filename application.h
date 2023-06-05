/* 
 * File:   application.h
 * Author: abdo9
 *
 * Created on May 15, 2023, 1:37 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H


/* Section : Includes */
#include "ECU_Layer/LED/ecu_led.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data-Type Declarations */

/* Section : Function Declarations */
void application_initialize();
void clock_signal(void);
void latch_enable(void);
void send_data(uint8 data_out);

#endif	/* APPLICATION_H */

