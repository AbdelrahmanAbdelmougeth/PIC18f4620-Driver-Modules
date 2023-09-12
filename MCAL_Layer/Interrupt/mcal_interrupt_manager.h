/* 
 * File:   mcal_interrupt_manager.h
 * Author: hp
 *
 * Created on 26 ?????, 2023, 03:46 ?
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H


/* Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data-Type Declarations */

/* Section : Function Declarations */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(uint8 interrupt_state);
void RB5_ISR(uint8 interrupt_state);
void RB6_ISR(uint8 interrupt_state);
void RB7_ISR(uint8 interrupt_state);

void ADC_ISR(void);

void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);

void CCP1_ISR(void);
void CCP2_ISR(void);

void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);

void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

