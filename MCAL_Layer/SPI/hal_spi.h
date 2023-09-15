/* 
 * File:   hal_spi.h
 * Author: hp
 *
 * Created on 14 ??????, 2023, 07:36 ?
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/*------------------------- Section : Includes ---------------------------------*/
#include "../GPIO/hal_gpio.h"
#include "../include/proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"


/*--------------------- Section : Macro Declarations ---------------------------*/
/* CKP: Clock Polarity Select bit */
#define CLOCK_POLARITY_IDLE_IS_HIGH     1
#define CLOCK_POLARITY_IDLE_IS_LOW      0
/* CKE: SPI Clock Select bit */
#define TRANSMIT_FROM_ACTIVE_TO_IDLE    1
#define TRANSMIT_FROM_IDLE_TO_ACTIVE    0
/* SMP: Sample bit (Must Be Cleared In Slave Mode)*/
#define SAMPLE_INPUT_DATA_AT_END        1
#define SAMPLE_INPUT_DATA_AT_MID        0
/* BF: Buffer Full Status bit (Receive mode only) (Read-only bit) */
#define SSPBUF_IS_FULL                  1
#define SSPBUF_IS_EMPTY                 0
/* WCOL: Write Collision Detect bit */
#define WRITE_COLLISION_DETECTED        1
#define WRITE_COLLISION_NONE            0
/* SSPOV: Receive Overflow Indicator bit (Slave Mode Only) */
#define RECEIVE_OVERFLOW_DETECTED       1
#define RECEIVE_OVERFLOW_NONE           0


/*----------------- Section: Macro Functions Declarations ----------------------*/
/* Enable and Disable SPI Module */
#define MSSP_SPI_MODULE_ENABLE()                (SSPCON1bits.SSPEN = 1)
#define MSSP_SPI_MODULE_DISABLE()               (SSPCON1bits.SSPEN = 0)
/* SPI Set Mode --> SSPM3:SSPM0: Master Synchronous Serial Port Mode Select bits */
#define MSSP_SPI_SET_MODE(_config)              (SSPCON1bits.SSPM = _config)
/* Configure SMP: Sample bit (Clear for slave mode)*/
#define CONFIG_SAMPLE_INPUT_DATA_BIT(_config)   (SSPSTATbits.SMP = _config)
/*Configure CKP: Clock Polarity Select bit */
#define CONFIG_CLOCK_POLARITY(_config)          (SSPCON1bits.CKP = _config)
/* Get The Status Of SSPBUF REG (Receive Mode Only)   0 : Receive not complete, 1 : Receive Finished  */
#define GET_SSPBUF_STATE()                      (SSPSTATbits.BF)
/* Clear WCOL: Write Collision Detect bit */
#define CLEAR_WRITE_COLLISION_BIT()             (SSPCON1bits.WCOL = 0)
/* SSPOV: Receive Overflow Indicator bit (Slave Mode Only) */
#define CLEAR_RECEIVE_OVERFLOW_BIT()            (SSPCON1bits.SSPOV = 0)
/* Configure SPI I/O Pins To Work in master mode */
#define MASTER_CONFIG_SPI_IO_PINS()             do{CLEAR_BIT(TRISC, GPIO_PIN5);\
                                                   CLEAR_BIT(TRISC, GPIO_PIN3);\
                                                   SET_BIT(TRISA, GPIO_PIN5);\
                                                }while(0)
/* Configure SPI I/O Pins To Work in slave mode */
#define SLAVE_CONFIG_SPI_IO_PINS()              do{CLEAR_BIT(TRISC, GPIO_PIN5);\
                                                   SET_BIT(TRISC, GPIO_PIN3);\
                                                   SET_BIT(TRISA, GPIO_PIN5);\
                                                }while(0)

/* Write SSPBUF Register */
#define SSPBUF_WRITE_REG(_data)                 (SSPBUF = _data)

/*--------------------- Section : Data-Type Declarations -----------------------*/
typedef enum{
    SPI_MASTER_MODE_FOSC_DIV_4 = 0,
    SPI_MASTER_MODE_FOSC_DIV_16,
    SPI_MASTER_MODE_FOSC_DIV_64,
    SPI_MASTER_MODE_TMR2_CLOCK,
    SPI_SLAVE_MODE_SS_ENABLED,
    SPI_SLAVE_MODE_SS_DISABLED,
}spi_conf_t;

typedef struct{
    uint8 ClockPolarity : 2; /* Clock Polarity Select */
    uint8 SampleSelect : 2;  /* SPI Sample Select */
    uint8 ClockSelect : 2;   /* SPI Clock Select */
    uint8 Reserved : 2;
}SPI_Control_Config;

typedef struct{
    #if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        void (* MSSP_SPI_InterruptHandler)(void);
        interrupt_periority_cfg priority;
    #endif
    uint8 spi_mode;
    SPI_Control_Config spi_config;
}spi_t;

/*----------------------- Section : Function Declarations ----------------------*/
Std_ReturnType SPI_Init(const spi_t *_spi_obj);
Std_ReturnType SPI_DeInit(const spi_t *_spi_obj);
/* Must be used with interrupt feature disabled */
Std_ReturnType SPI_Send_Byte_Blocking(const spi_t *_spi_obj, const uint8 _data);
Std_ReturnType SPI_Read_Byte_Blocking(const spi_t *_spi_obj, uint8 *_data);
Std_ReturnType SPI_Send_Byte_NonBlocking(const spi_t *_spi_obj, const uint8 _data);
Std_ReturnType SPI_Read_Byte_NonBlocking(const spi_t *_spi_obj, uint8 *_data);

#endif	/* HAL_SPI_H */

