/* 
 * File:   hal_usart.h
 * Author: hp
 *
 * Created on 07 ??????, 2023, 06:31 ?
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* Section : Includes */
#include "hal_usart_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../include/proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"


/* Section : Macro Declarations */
/*Enable and Disable EUSART Module*/
#define EUSART_MODULE_ENABLED    1
#define EUSART_MODULE_DISABLED   0

/*Select EUSART Working Mode*/
#define EUSART_ASYNCHRONOUS_MODE   0
#define EUSART_SYNCHRONOUS_MODE    1
/* High Baud Rate Select bit Asynchronous mode: */
/* Note: Synchronous mode: Unused in this mode.*/
#define EUSART_ASYNCHRONOUS_HIGH_SPEED   1
#define EUSART_ASYNCHRONOUS_LOW_SPEED    0
/* 8-bit and 16-bit BAUD rate generator */
#define EUSART_16BIT_BAUDRATE_GEN      1
#define EUSART_8BIT_BAUDRATE_GEN       0

/* Transmitting */
/* EUSART Transmit */
#define EUSART_ASYNCHRONOUS_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE  0
/* EUSART Transmit Interrupt */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE   0
/* EUSART 9-Bit Transmit */
#define EUSART_TX_9BIT_ENABLE   1
#define EUSART_TX_9BIT_DISABLE  0


/* Receiving */
/* EUSART Receiver */
#define EUSART_ASYNCHRONOUS_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_RX_DISABLE  0
/* EUSART Receiver Interrupt */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE   0
/* EUSART 9-Bit Receiver */
#define EUSART_RX_9BIT_ENABLE   1
#define EUSART_RX_9BIT_DISABLE  0

/* EUSART Errors*/
/* Framing Error*/
#define EUSART_FRAMING_ERROR_DETECTED  1
#define EUSART_FRAMING_ERROR_CLEARED   0
/* Framing Error*/
#define EUSART_OVERRUN_ERROR_DETECTED  1
#define EUSART_OVERRUN_ERROR_CLEARED   0

/* Section : Macro Functions Declarations */
#define EUSART_MODULE_ENABLE()    (RCSTAbits.SPEN = EUSART_MODULE_ENABLED)
#define EUSART_MODULE_DISABLE()   (RCSTAbits.SPEN = EUSART_MODULE_DISABLED)

#define EUSART_SET_TRISC_PIN6()   (TRISCbits.RC6 = 1)
#define EUSART_SET_TRISC_PIN7()   (TRISCbits.RC7 = 1)

/* Section : Data-Type Declarations */
typedef enum{
    BAUDRATE_ASYNC_8BIT_LOW_SPEED = 0,
    BAUDRATE_ASYNC_8BIT_HIGH_SPEED,
    BAUDRATE_ASYNC_16BIT_LOW_SPEED,
    BAUDRATE_ASYNC_16BIT_HIGH_SPEED,
    BAUDRATE_SYNC_8BIT,
    BAUDRATE_SYNC_16BIT,
}baudrate_gen_t;

typedef struct{
   uint8 eusart_tx_enable : 1; 
   uint8 eusart_tx_interrupt_enable : 1; 
   uint8 eusart_tx_9bit_enable : 1; 
   uint8 eusart_tx_reserved : 5; 
}eusart_tx_cfg_t;

typedef struct{
   uint8 eusart_rx_enable : 1;
   uint8 eusart_rx_interrupt_enable : 1; 
   uint8 eusart_rx_9bit_enable : 1;
   uint8 eusart_rx_reservered : 5;
}eusart_rx_cfg_t;

typedef union{
    struct{
        uint8 eusart_ferr : 1;
        uint8 eusart_oerr : 1;
        uint8 eusart_reserved : 6;
    };
    uint8 status;
}eusart_error_status_t;

typedef struct{
    uint32 baudrate;
    uint8 eusart_mode : 1;             /* SYNCHRONOUS or ASYNCHRONOUS Mode */           
    baudrate_gen_t baudrate_config;
    eusart_tx_cfg_t  eusart_tx_cfg;
    eusart_rx_cfg_t  eusart_rx_cfg;
    eusart_error_status_t eusart_error_status;
    void (* EUSART_TxDefaultInterruptHandler)(void); 
    void (* EUSART_RxDefaultInterruptHandler)(void); 
    void (* EUSART_FramingErrorHandler)(void); 
    void (* EUSART_OverrunErrorHandler)(void); 
}eusart_t;

/* Section : Function Declarations */
Std_ReturnType EUSART_ASYNC_Init(eusart_t *_eusart);
Std_ReturnType EUSART_ASYNC_DeInit(eusart_t *_eusart);
Std_ReturnType EUSART_ASYNC_SendByteBlocking(uint8 _data);
Std_ReturnType EUSART_ASYNC_SendStringBlocking(uint8 *_str, uint16 _str_len);
Std_ReturnType EUSART_ASYNC_RecieveByteBlocking(uint8 *_data);
Std_ReturnType EUSART_ASYNC_RecieveByteNonBlocking(uint8 *_data);

#endif	/* HAL_USART_H */

