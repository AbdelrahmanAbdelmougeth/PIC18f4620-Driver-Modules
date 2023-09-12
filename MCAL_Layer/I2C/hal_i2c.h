/* 
 * File:   hal_i2c.h
 * Author: hp
 *
 * Created on 11 ??????, 2023, 05:59 ?
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../include/proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */

/*I2C Module Enable/Disable*/
#define I2C_MODULE_ENABLED            1
#define I2C_MODULE_DISABLED           0
/* SMP: Slew Rate Control bit */
#define I2C_SLEW_RATE_ENABLED        0
#define I2C_SLEW_RATE_DISABLED       1
/* CKE: SMBus Select bit */
#define I2C_SMBus_ENABLED            1
#define I2C_SMBus_DISABLED           0
/* D/A': Data/Address bit */
#define I2C_LAST_BYTE_WAS_DATA       1
#define I2C_LAST_BYTE_WAS_ADDRESS    0
/* P: Stop bit */
#define I2C_STOP_BIT_DETECTED        1
#define I2C_STOP_BIT_NOT_DETECTED    0
/* S: Start bit */
#define I2C_START_BIT_DETECTED       1
#define I2C_START_BIT_NOT_DETECTED   0
/* I2C: Master or Slave Mode */
#define MSSP_I2C_MASTER_MODE         1
#define MSSP_I2C_SLAVE_MODE          0
/* SSPM3:SSPM0: Master Synchronous Serial Port Mode Select */
#define I2C_SLAVE_MODE_10_BIT_ADDRESS_START_STOP_BIT_INTERRUPTS_ENABLED     0x0FU
#define I2C_SLAVE_MODE_7_BIT_ADDRESS_START_STOP_BIT_INTERRUPTS_ENABLED      0x0EU
#define I2C_FIRMWARE_CONTROLLED_MASTER_MODE_SLAVE_IDLE                      0x0BU  
#define I2C_MASTER_MODE_DEFINED_CLOCK                                       0x08U  
#define I2C_SLAVE_MODE_10_BIT_ADDRESS                                       0x07U  
#define I2C_SLAVE_MODE_7_BIT_ADDRESS                                        0x06U  
/* I2C General Call */
#define I2C_GENERAL_CALL_INTERRUPT_ENABLED     1
#define I2C_GENERAL_CALL_DISABLED              0
/* I2C Master Mode Receive Enable/Disable */
#define I2C_MASTER_MODE_RECEIVE_ENABLED     1
#define I2C_MASTER_MODE_RECEIVE_DISABLED    0
/* Start Condition Enable/Idle */
#define I2C_INIT_START_CONDITION       1
#define I2C_START_COND_IDLE            0
#define I2C_INIT_REPEATED_START_CONDITION       1
#define I2C_REPEATED_START_COND_IDLE            0
#define I2C_INIT_STOP_CONDITION       1
#define I2C_STOP_COND_IDLE            0
/* ACKSTAT: Acknowledge Status bit (Master Transmit mode only) */
#define I2C_ACK_RECEIVED_FROM_SLAVE          0
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE      1
/* ACKDT: Acknowledge Data bit (Master Receive mode only) */
#define I2C_MASTER_SEND_ACK       0
#define I2C_MASTER_SEND_NACK      1


/* Section : Macro Functions Declarations */
/* SMP: Slew Rate Control bit */
#define I2C_SLEW_RATE_ENABLE()       (SSPSTATbits.SMP = I2C_SLEW_RATE_ENABLED)
#define I2C_SLEW_RATE_DISABLE()      (SSPSTATbits.SMP = I2C_SLEW_RATE_DISABLED)
/* CKE: SMBus Select bit */
#define I2C_SMBus_ENABLE()            (SSPSTATbits.CKE = I2C_SMBus_ENABLED)
#define I2C_SMBus_DISABLE()           (SSPSTATbits.CKE = I2C_SMBus_DISABLED)
/* General Call CFG */
#define I2C_GENERAL_CALL_INTERRUPT_ENABLE() (SSPCON2bits.GCEN = I2C_GENERAL_CALL_INTERRUPT_ENABLED)
#define I2C_GENERAL_CALL_DISABLE()          (SSPCON2bits.GCEN = I2C_GENERAL_CALL_DISABLED)
/* SSPEN: Master Synchronous Serial Port Enable bit */
#define MSSP_I2C_MODULE_ENABLE()            (SSPCON1bits.SSPEN = I2C_MODULE_ENABLED)
#define MSSP_I2C_MODULE_DISABLE()           (SSPCON1bits.SSPEN = I2C_MODULE_DISABLED)
/* I2C Master Mode Receive Enable/Disable */
#define I2C_MASTER_MODE_RECEIVE_ENABLE()    (SSPCON2bits.RCEN = I2C_MASTER_MODE_RECEIVE_ENABLED)
#define I2C_MASTER_MODE_RECEIVE_DISABLE()   (SSPCON2bits.RCEN = I2C_MASTER_MODE_RECEIVE_DISABLED)


/* Initiate start condition */
/* Initiates Start condition on SDA and SCL pins. Automatically cleared by hardware */
#define I2C_INITIATE_START_CONDITION()      (SSPCON2bits.SEN = I2C_INIT_START_CONDITION)
#define I2C_START_CONDITION_IDLE()          (SSPCON2bits.SEN = I2C_START_COND_IDLE)
/* Get The Start Condition State */
#define GET_START_CONDITION_STATE()         (SSPCON2bits.SEN)
/* Check if the start Condition was detected last */
#define CHECK_START_CONDITION_DETECTED()    (SSPSTATbits.S)

/* Initiate repeated start condition */
/* Initiates repeated Start condition on SDA and SCL pins. Automatically cleared by hardware */
#define I2C_INITIATE_REPEATED_START_CONDITION()      (SSPCON2bits.RSEN = I2C_INIT_REPEATED_START_CONDITION)
#define I2C_REPEATED_START_CONDITION_IDLE()          (SSPCON2bits.RSEN = I2C_REPEATED_START_COND_IDLE)
/* Get The Start Condition State */
#define GET_REPEATED_START_CONDITION_STATE()         (SSPCON2bits.RSEN)

/* Initiate stop condition */
/* Initiates Stop condition on SDA and SCL pins. Automatically cleared by hardware */
#define I2C_INITIATE_STOP_CONDITION()       (SSPCON2bits.PEN = I2C_INIT_STOP_CONDITION)
#define I2C_STOP_CONDITION_IDLE()          (SSPCON2bits.PEN = I2C_STOP_COND_IDLE)
/* Get The Stop Condition State */
#define GET_STOP_CONDITION_STATE()         (SSPCON2bits.PEN)
/* Check if the start Condition was detected last */
#define CHECK_STOP_CONDITION_DETECTED()    (SSPSTATbits.S)

#define MSSP_IterruptFlagClear()   (PIR1bits.SSPIF = 0)
#define MSSP_GetIterruptFlag()     (PIR1bits.SSPIF)


#define I2C_WRITE_SSPBUF_REG(_byte_data)      (SSPBUF = _byte_data)
#define I2C_READ_SSPBUF_REG()                 (SSPBUF)

#define I2C_GET_ACK_RECEIVED_FROM_SLAVE_STATE()  (SSPCON2bits.ACKSTAT)
#define I2C_INITIATE_MASTER_ACKNOWLEDGE_SEQUENCE()   (SSPCON2bits.ACKEN = 1)

#define I2C_GET_SSPBUF_STATUS()    (SSPSTATbits.BF)

#define I2C_CLEAR_WRITE_COL_DETECT()   (SSPCON1bits.WCOL = 0)
#define I2C_CLEAR_RECEIVE_OF_DETECT()  (SSPCON1bits.SSPOV = 0)
#define I2C_SLAVE_RELEASE_CLOCK()      (SSPCON1bits.CKP = 1)
#define I2C_SLAVE_ADDRESS_ASSIGN(_ADD) (SSPADD = _ADD)


/* Section : Data-Type Declarations */
typedef struct{
    uint8 i2c_mode_cfg;                 /* SSPM3:SSPM0: Master Synchronous Serial Port Mode Select */
    uint8 i2c_slave_add;                /* slave address (slave mode only) */
    uint8 i2c_mode : 1;                 /* I2C: Master or Slave Mode */
    uint8 i2c_slew_rate : 1;            /* Slew Rate Control bit  1 = Standard Speed mode (100 kHz), 0 = High-Speed mode (400 kHz)*/
    uint8 i2c_SMBus_control : 1;        /* CKE: SMBus Select bit  1 = Enable SMBus specific inputs, 0 = Disable SMBus specific inputs*/
    uint8 i2c_general_call : 1;         /* general call enable/disable */
    uint8 i2c_master_receive_mode : 1;  /* Master Receive Mode Enable/Disable */
    uint8 i2c_reserved : 3;
}i2c_configs_t;

typedef struct{
    uint32 i2c_clock;
    #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void (*I2C_Report_Write_Collision)(void);
        void (*I2C_DefaultInterruptHandler)(void);
        void (*I2C_Report_Receive_Overflow)(void);
        interrupt_periority_cfg mssp_i2c_priority;
        interrupt_periority_cfg mssp_i2c_bc_priority;
    #endif    
    i2c_configs_t i2c_cfg;
}mssp_i2c_t;


/* Section : Function Declarations */
Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *_i2c_obj);
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *_i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *_i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *_i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *_i2c_obj);
Std_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *_i2c_obj, uint8 _i2c_data, uint8 *_ack);
Std_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t *_i2c_obj, uint8 _ack, uint8 *_i2c_data);

#endif	/* HAL_I2C_H */

