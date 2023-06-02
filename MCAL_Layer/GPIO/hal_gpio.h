/* 
 * File:   hal_gpio.h
 * Author: abdo9
 *
 * Created on May 15, 2023, 12:57 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section : Includes */
#include "../include/proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"

/* Section : Macro Declarations */
#define BIT_MASK (uint8)1

/* Section : Macro Functions Declarations */
#define HWREG8(REG_ADDR)   (*(volatile uint8 *(REG_ADDR)))

#define SET_BIT   (REG, BIT_POSN) (REG |=  (BIT_MASK << BIT_POSN))
#define CLEAR_BIT (REG, BIT_POSN) (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG, BIT_POSN) (REG ^=  (BIT_MASK << BIT_POSN))
#define READ_BIT  (REG, BIT_POSN) ((REG >> BIT_POSN) & BIT_MASK)


/* Section : Data-Type Declarations */
typedef enum{
    LOW = 0,
    HIGH        
}logic_t;

typedef enum{
    OUTPUT =0,
    INPUT        
}direction_t;

typedef enum{
    PIN0 =0,
    PIN1,
    PIN2,
    PIN3,
    PIN4, 
    PIN5,
    PIN6,
    PIN7
}pin_index_t;


typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEXPIN3,
    PORTE_INDEX, 
}port_index_t;


typedef struct{
    uint8 port :3;
    uint8 pin :3;
    uint8 direction: 1;
    uint8 logic : 1;
}pin_config_t;


/* Section : Function Declarations */
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t* _pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t* _pin_config, direction_t* direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t* _pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t* _pin_config, logic_t* logic);
Std_ReturnType gpio_toggle_logic(const pin_config_t* _pin_config);

Std_ReturnType gpio_port_direction_initialize(const port_index_t port);
Std_ReturnType gpio_port_get_direction_status(const port_index_t port, uint8* direction_status);
Std_ReturnType gpio_port_write_logic(const port_index_t port, uint8 logic);
Std_ReturnType gpio_port_read_logic(const port_index_t port, uint8* logic);
Std_ReturnType gpio_port_toggle_logic(const port_index_t port);


#endif	/* HAL_GPIO_H */

