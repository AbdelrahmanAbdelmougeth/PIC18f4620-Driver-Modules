/* 
 * File:   hal_usart.c
 * Author: hp
 *
 * Created on 07 ??????, 2023, 06:27 ?
 */

#include "hal_usart.h"

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void(* EUSART_TX_InterruptHandler)(void) = NULL;       
#endif 
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void(* EUSART_RX_InterruptHandler)(void) = NULL;       
    static void(* EUSART_FramingErrorHandler)(void); 
    static void(* EUSART_OverrunErrorHandler)(void);    
#endif

static Std_ReturnType EUSART_ASYNC_Baud_Rate_Calculation(eusart_t *_eusart);
static Std_ReturnType EUSART_ASYNC_TX_Init(eusart_t *_eusart);
static Std_ReturnType EUSART_ASYNC_RX_Init(eusart_t *_eusart);

Std_ReturnType EUSART_ASYNC_Init(eusart_t *_eusart){
    Std_ReturnType ret = E_OK;
    if(_eusart == NULL){
        ret = E_NOT_OK;
    }else{
        /* Disable EUSART Module */
        EUSART_MODULE_DISABLE();
        
        EUSART_SET_TRISC_PIN6();
        EUSART_SET_TRISC_PIN7();
        
        ret = EUSART_ASYNC_Baud_Rate_Calculation(_eusart);
        ret = EUSART_ASYNC_TX_Init(_eusart);
        ret = EUSART_ASYNC_RX_Init(_eusart);
        
        /* Enable EUSART Module */
        EUSART_MODULE_ENABLE();
        uint8 dummy = TXREG;
        
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_RX_Restart(void){
    Std_ReturnType ret = E_OK;
    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1;
    return ret;
}

Std_ReturnType EUSART_ASYNC_DeInit(eusart_t *_eusart){
    Std_ReturnType ret = E_OK;
    if(_eusart == NULL){
        ret = E_NOT_OK;
    }else{
        EUSART_MODULE_DISABLE();
        #if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            EUSART_TX_InterruptDisable();
        #endif 
        #if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            EUSART_RX_InterruptDisable();
        #endif 
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_SendByteBlocking(uint8 _data){
    Std_ReturnType ret = E_OK;
    while(!TXSTAbits.TRMT);
    TXREG = _data;
    return ret;
}


Std_ReturnType EUSART_ASYNC_SendStringBlocking(uint8 *_str, uint16 _str_len){
    Std_ReturnType ret = E_OK;
    for(uint8 char_counter = ZERO_INIT; char_counter < _str_len; char_counter++){
         ret = EUSART_ASYNC_SendByteBlocking(_str[char_counter]);
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_SendByteNonBlocking(uint8 _data){
    /* cannot be done  */
    /*  TRMT is a read-only bit which is set
        when the TSR register is empty. No interrupt logic is
        tied to this bit so the user has to poll this bit in order to
        determine if the TSR register is empty. */
    Std_ReturnType ret = E_OK;
    if(!TXSTAbits.TRMT){
        TXREG = _data;  
    }else{
        ret = E_NOT_OK;
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_SendStringNonBlocking(uint8 *_str, uint16 _str_len){
    /* cannot be done  */
    /*  TRMT is a read-only bit which is set
        when the TSR register is empty. No interrupt logic is
        tied to this bit so the user has to poll this bit in order to
        determine if the TSR register is empty. */
    Std_ReturnType ret = E_OK;
    uint16 char_counter = ZERO_INIT;
    while(char_counter < _str_len){
       ret = EUSART_ASYNC_SendByteNonBlocking(_str[char_counter]);
       if(ret == E_OK){          
            char_counter++;     
       }
    }
}


Std_ReturnType EUSART_ASYNC_RecieveByteBlocking(uint8 *_data){
    Std_ReturnType ret = E_OK;
    if(_data == NULL){
        ret = E_NOT_OK;
    }else{
        while(!PIR1bits.RCIF);
        *_data = RCREG;
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_RecieveByteNonBlocking(uint8 *_data){
    Std_ReturnType ret = E_OK;
    if(_data == NULL){
        ret = E_NOT_OK;
    }else{
        if(PIR1bits.RCIF){
            *_data = RCREG;
        }else{
            ret = E_NOT_OK;
        }       
    }
    return ret;
}


static Std_ReturnType EUSART_ASYNC_Baud_Rate_Calculation(eusart_t *_eusart){
    Std_ReturnType ret = E_OK;
    if(_eusart == NULL){
        ret = E_NOT_OK;
    }else{
        float Baudrate_temp = 0.0;
        switch (_eusart->baudrate_config){
            case BAUDRATE_ASYNC_8BIT_LOW_SPEED:
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
                Baudrate_temp = (((_XTAL_FREQ / (float)_eusart->baudrate) / 64) - 1);
                break;
            case BAUDRATE_ASYNC_8BIT_HIGH_SPEED:
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
                Baudrate_temp = (((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1);
                break;
            case BAUDRATE_ASYNC_16BIT_LOW_SPEED:
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                Baudrate_temp = (((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1);
                break;
            case BAUDRATE_ASYNC_16BIT_HIGH_SPEED:
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                Baudrate_temp = (((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1);
                break;
            case BAUDRATE_SYNC_8BIT:
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
                Baudrate_temp = (((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1);
                break;
            case BAUDRATE_SYNC_16BIT:
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                Baudrate_temp = (((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1);
                break;
            default: ret = E_NOT_OK;
        }
        SPBRG = (uint8)((uint32)Baudrate_temp);
        SPBRGH = (uint8)(((uint32)Baudrate_temp) >> 8);
    }
    return ret;
}

static Std_ReturnType EUSART_ASYNC_TX_Init(eusart_t *_eusart){
    Std_ReturnType ret = E_OK;
    if(_eusart == NULL){
        ret = E_NOT_OK;
    }else{
        /* EUSART Transmit Interrupt Configuration */
        if(_eusart->eusart_tx_cfg.eusart_tx_enable == EUSART_ASYNCHRONOUS_TX_ENABLE){
            /* EUSART Transmit Enable */
            TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
            
            /* Configure the interrupt */
            #if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
                EUSART_TX_InterruptEnable();
                EUSART_TX_InterruptHandler = _eusart->EUSART_TxDefaultInterruptHandler;
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    if(_eusart->eusart_tx_cfg.tx_priority == INTERRUPT_LOW_PRIORITY){
                        INTERRUPT_GobalInterruptLowEnable();
                        EUSART_TX_INTERRUPT_LowPrioritySet();
                    }else if(_eusart->eusart_tx_cfg.tx_priority == INTERRUPT_HIGH_PRIORITY){
                        INTERRUPT_GobalInterruptHighEnable();
                        EUSART_TX_INTERRUPT_HighPrioritySet();
                    }    
                #else
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInterruptEnable(); 
                #endif
            #endif  
            
            /* EUSART Transmit Interrupt Configuration */
            if(_eusart->eusart_tx_cfg.eusart_tx_interrupt_enable == EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE){
                EUSART_TX_InterruptEnable();
            }else if(_eusart->eusart_tx_cfg.eusart_tx_interrupt_enable == EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE){
                EUSART_TX_InterruptDisable();
            }else {ret = E_NOT_OK;}

            /* EUSART Transmit 9-bit Configuration */
            if(_eusart->eusart_tx_cfg.eusart_tx_9bit_enable == EUSART_TX_9BIT_ENABLE){
                TXSTAbits.TX9 = EUSART_TX_9BIT_ENABLE;
            }else if(_eusart->eusart_tx_cfg.eusart_tx_9bit_enable == EUSART_TX_9BIT_DISABLE){
                TXSTAbits.TX9 = EUSART_TX_9BIT_DISABLE;
            }else {ret = E_NOT_OK;}
            
        }else if(_eusart->eusart_tx_cfg.eusart_tx_enable == EUSART_ASYNCHRONOUS_TX_DISABLE){
            /* EUSART Transmit Disable */
            TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_DISABLE;
        }else {ret = E_NOT_OK;}
          
    }
    return ret;
}

static Std_ReturnType EUSART_ASYNC_RX_Init(eusart_t *_eusart){
    Std_ReturnType ret = E_OK;
    if(_eusart == NULL){
        ret = E_NOT_OK;
    }else{
        /* EUSART Receive Interrupt Configuration */
        if(_eusart->eusart_rx_cfg.eusart_rx_enable == EUSART_ASYNCHRONOUS_RX_ENABLE){
            /* EUSART Receiver Enable */
            RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
            
            /* EUSART Receive Interrupt Configuration */
            if(_eusart->eusart_rx_cfg.eusart_rx_interrupt_enable == EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE){
                PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
                /* Configure the interrupt */
                #if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
                    EUSART_RX_InterruptEnable();
                    EUSART_RX_InterruptHandler = _eusart->EUSART_RxDefaultInterruptHandler;
                    EUSART_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler; 
                    EUSART_OverrunErrorHandler = _eusart->EUSART_OverrunErrorHandler;
                    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                        if(_eusart->eusart_rx_cfg.rx_priority == INTERRUPT_LOW_PRIORITY){
                            INTERRUPT_GobalInterruptLowEnable();
                            EUSART_RX_INTERRUPT_LowPrioritySet();
                        }else if(_eusart->eusart_rx_cfg.rx_priority == INTERRUPT_HIGH_PRIORITY){
                            INTERRUPT_GobalInterruptHighEnable();
                            EUSART_RX_INTERRUPT_HighPrioritySet();
                        }    
                    #else
                        INTERRUPT_GlobalInterruptEnable();
                        INTERRUPT_PeripheralInterruptEnable(); 
                    #endif
                #endif
                        
            }else if(_eusart->eusart_rx_cfg.eusart_rx_interrupt_enable == EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE){
                EUSART_RX_InterruptDisable();
            }else {ret = E_NOT_OK;}

            /* EUSART Receive 9-bit Configuration */
            if(_eusart->eusart_rx_cfg.eusart_rx_9bit_enable == EUSART_RX_9BIT_ENABLE){
                RCSTAbits.RX9 = EUSART_RX_9BIT_ENABLE;
            }else if(_eusart->eusart_rx_cfg.eusart_rx_9bit_enable == EUSART_TX_9BIT_DISABLE){
                RCSTAbits.RX9 = EUSART_TX_9BIT_DISABLE;
            }else {ret = E_NOT_OK;}
            
        }else if(_eusart->eusart_rx_cfg.eusart_rx_enable == EUSART_ASYNCHRONOUS_RX_DISABLE){
            /* EUSART Receiver Disable */
            RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_DISABLE;
        }else {ret = E_NOT_OK;}       
    }
    return ret;
}

void EUSART_TX_ISR(void){
    /* The Internal EUSART_TX Interrupt has been occurred (must be cleared in software) */ 

    /* Code : To be executed from MCAL Interrupt Context*/
    EUSART_TX_InterruptDisable();
    /* Callback function gets called every time this ISR executes*/
    if(EUSART_TX_InterruptHandler){
        EUSART_TX_InterruptHandler();
    }
}

void EUSART_RX_ISR(void){
    /* The Internal EUSART_TX Interrupt has been occurred (must be cleared in software) */ 

    /* Code : To be executed from MCAL Interrupt Context*/
    
    /* Callback function gets called every time this ISR executes*/
    if(EUSART_RX_InterruptHandler){
        EUSART_RX_InterruptHandler();
    }
    if(EUSART_FramingErrorHandler){
        EUSART_FramingErrorHandler();
    }
    if(EUSART_OverrunErrorHandler){
        EUSART_OverrunErrorHandler();
    }
}