/* 
 * File:   ecu_keypad.h
 * Author: abdo9
 *
 * Created on June 24, 2023, 6:50 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H


/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_keypad_cfg.h"

/* Section : Macro Declarations */
#define ECU_KEYPAD_ROWS 4
#define ECU_KEYPAD_COLS 4


/* Section : Macro Functions Declarations */

/* Section : Data-Type Declarations */
typedef struct{
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_col_pins[ECU_KEYPAD_COLS];
}keypad_t; 

/* Section : Function Declarations */
Std_ReturnType keypad_initialize (const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value (const keypad_t *_keypad_obj, uint8 *value);

#endif	/* ECU_KEYPAD_H */

