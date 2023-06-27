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

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data-Type Declarations */
extern chr_lcd_4bit_t _lcd_1;
extern chr_lcd_8bit_t _lcd_2;

/* Section : Function Declarations */
void application_initialize();

#endif	/* APPLICATION_H */

