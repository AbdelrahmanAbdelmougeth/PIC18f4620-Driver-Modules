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
/*
 * 
 */
int main() {
    ABDO_TRISC = 0x00; //set port c as output
    ABDO_LATC = 0x55; //write 0x55 to output pin
    __delay_ms(2000);
    //ABDO_LATC |= (1 << _LATC_LATC1_POSN); //set bit
    SET_BIT(ABDO_LATC, _LATC_LATC1_POSN);
    __delay_ms(1000);
    //ABDO_LATC &= ~(1 << _LATC_LATC1_POSN); //clear bit
    CLEAR_BIT(ABDO_LATC, _LATC_LATC1_POSN);
    __delay_ms(1000);
    //ABDO_LATC ^= (1 << _LATC_LATC1_POSN); //clear bit
    TOGGLE_BIT(ABDO_LATC, _LATC_LATC1_POSN);
    while(1)
    {
    }

    return (EXIT_SUCCESS);
}

