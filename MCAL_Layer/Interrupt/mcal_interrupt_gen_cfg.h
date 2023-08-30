/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: hp
 *
 * Created on 03 ?????, 2023, 01:09 ?
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

#define INTERRUPT_FEATURE_ENABLE 1U
//#define INTERRUPT_PRIORITY_LEVELS_ENABLE           INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE     INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_FEATURE_ENABLE               INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUPT_FEATURE_ENABLE            INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_FEATURE_ENABLE            INTERRUPT_FEATURE_ENABLE

#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

