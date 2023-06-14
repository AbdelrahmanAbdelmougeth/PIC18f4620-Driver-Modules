/* 
 * File:   ecu_ seven_seg.h
 * Author: hp
 *
 * Created on 13 ?????, 2023, 03:52 ?
 */

#ifndef ECU__SEVEN_SEG_H
#define	ECU__SEVEN_SEG_H


/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_seven_seg_cfg.h"

/* Section : Macro Declarations */
#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3

/* Section : Macro Functions Declarations */

/* Section : Data-Type Declarations */
typedef enum {
    COMMON_ANODE_SEGMENT,
    COMMON_CATHODE_SEGMENT         
}segment_type_t;

typedef struct {
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;

/* Section : Function Declarations */
Std_ReturnType seven_segment_initialize(const segment_t *segment);
Std_ReturnType seven_segment_write_number(const segment_t *segment, uint8 number);

#endif	/* ECU__SEVEN_SEG_H */

