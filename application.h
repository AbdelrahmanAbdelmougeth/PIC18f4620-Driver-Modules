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
#include "ECU_Layer/Button/ecu_button.h"
#include "ECU_Layer/Relay/ecu_relay.h"
#include "ECU_Layer/DC_Motor/ecu_dc_motor.h"
#include "ECU_Layer/Seven_Segment_Display/ecu_seven_seg.h"


/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data-Type Declarations */

/* Section : Function Declarations */
void application_initialize();

#endif	/* APPLICATION_H */

