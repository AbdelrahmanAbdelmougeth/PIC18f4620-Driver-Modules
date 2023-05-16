/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

#define _XTAL_FREQ 4000000UL

#define HWREG8(_x)    (*(volatile uint8_t *)(_x))

#define ABDO_LATC   (HWREG8(0xF8B))
#define ABDO_TRISC  (HWREG8(0xF94))

#define SET_BIT(REG_ADDR,BIT_POSN)     (REG_ADDR |= (1 << BIT_POSN))
#define CLEAR_BIT(REG_ADDR,BIT_POSN)   (REG_ADDR &= ~(1 << BIT_POSN))
#define TOGGLE_BIT(REG_ADDR,BIT_POSN)  (REG_ADDR ^= (1 << BIT_POSN))


typedef union {
    struct{
        unsigned SELF_LATC0 : 1;
        unsigned SELF_LATC1 : 1;
        unsigned SELF_LATC2 : 1;
        unsigned SELF_LATC3 : 1;
        unsigned SELF_LATC4 : 1;
        unsigned SELF_LATC5 : 1;
        unsigned SELF_LATC6 : 1;
        unsigned SELF_LATC7 : 1;
    };
    uint8_t LATC_REGISTER;
}SELF_LATC;

#define SELF_LATC_REG ((volatile SELF_LATC *)0XF8B)
/*
 * 
 */
int main() {
    ABDO_TRISC = 0x00; //set port c as output
    SELF_LATC_REG->LATC_REGISTER = 0x55;
    __delay_ms(2000);
    SELF_LATC_REG->SELF_LATC1 = 0x1;
    while(1)
    {
    }

    return (EXIT_SUCCESS);
}

