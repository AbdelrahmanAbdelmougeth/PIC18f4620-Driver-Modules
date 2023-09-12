/* 
 * File:   hal_i2c.c
 * Author: hp
 *
 * Created on 11 ??????, 2023, 05:59 ?
 */

#include "hal_i2c.h"

static inline void MSSP_I2C_GPIO_cfg(void);
static inline void I2C_Master_Mode_Clock_Configuration(const mssp_i2c_t *_i2c_obj);
static inline void I2C_Interrupt_Configuration(const mssp_i2c_t *_i2c_obj);
static inline void I2C_Slave_Mode_Configuration(const mssp_i2c_t *_i2c_obj);

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void(* MSSP_I2C_InterruptHandler)(void) = NULL;       
    static void(* MSSP_I2C_Report_Write_Collision)(void) = NULL;       
    static void(* MSSP_I2C_Report_Receive_Overflow)(void) = NULL;       
#endif 

Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *_i2c_obj){
    Std_ReturnType ret = E_OK;
    if(_i2c_obj == NULL){
        ret = E_NOT_OK;
    }else{
        /* Disable I2C Module */
        MSSP_I2C_MODULE_DISABLE();
        
        /* I2C Mode Select */
        if(_i2c_obj->i2c_cfg.i2c_mode == MSSP_I2C_MASTER_MODE){/* I2C Master Mode Configurations */
            /* I2C Master Mode Clock Configurations */
            I2C_Master_Mode_Clock_Configuration(_i2c_obj);
            /* RCEN: Receive Enable bit (Master mode only) */
            if(_i2c_obj->i2c_cfg.i2c_master_receive_mode == I2C_MASTER_MODE_RECEIVE_ENABLED){
                I2C_MASTER_MODE_RECEIVE_ENABLE();
            }else if(_i2c_obj->i2c_cfg.i2c_master_receive_mode == I2C_MASTER_MODE_RECEIVE_DISABLED){
                I2C_MASTER_MODE_RECEIVE_DISABLE();
            }else{/* nothing */}
        }
        else if(_i2c_obj->i2c_cfg.i2c_mode == MSSP_I2C_SLAVE_MODE){/* I2C Slave Mode Configurations */
            /* I2C Slave Mode General call Configurations */
            if(_i2c_obj->i2c_cfg.i2c_general_call == I2C_GENERAL_CALL_INTERRUPT_ENABLED){
                I2C_GENERAL_CALL_INTERRUPT_ENABLE();
            }else if(_i2c_obj->i2c_cfg.i2c_general_call == I2C_GENERAL_CALL_DISABLED){
                I2C_GENERAL_CALL_DISABLE();
            }else{/* nothing */}
            
            /* Clear The Write Collision Detect */
            I2C_CLEAR_WRITE_COL_DETECT();
            /* Clear Receive Overflow Indicator */
            I2C_CLEAR_RECEIVE_OF_DETECT();
            /* SCK Release Control */
            I2C_SLAVE_RELEASE_CLOCK();
            /* Assign Slave Address */
            I2C_SLAVE_ADDRESS_ASSIGN(_i2c_obj->i2c_cfg.i2c_slave_add);
            /* Set Slave Configurations */
            I2C_Slave_Mode_Configuration(_i2c_obj);
        }
        else{/* nothing */}
        
        /* I2C GPIO Configurations */
        MSSP_I2C_GPIO_cfg();
        
        /* I2C Slew Rate Configurations */
        if(_i2c_obj->i2c_cfg.i2c_slew_rate == I2C_SLEW_RATE_ENABLED){
            I2C_SLEW_RATE_ENABLE();
        }else if(_i2c_obj->i2c_cfg.i2c_slew_rate == I2C_SLEW_RATE_DISABLED){
            I2C_SLEW_RATE_DISABLE();
        }else{/* nothing */}
        
        /* I2C SMBus Configurations */
        if(_i2c_obj->i2c_cfg.i2c_SMBus_control == I2C_SMBus_ENABLED){
            I2C_SMBus_ENABLE();
        }else if(_i2c_obj->i2c_cfg.i2c_SMBus_control == I2C_SMBus_DISABLED){
            I2C_SMBus_DISABLE();
        }else{/* nothing */}
        
        /* Configure the interrupt */
        #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            I2C_Interrupt_Configuration(_i2c_obj);
        #endif

        /* Enable I2C Module */
        MSSP_I2C_MODULE_ENABLE();     
    }
    return ret;
}

Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *_i2c_obj){
    Std_ReturnType ret = E_OK;
    if(_i2c_obj == NULL){
        ret = E_NOT_OK;
    }else{
        /* Disable I2C Module */
        MSSP_I2C_MODULE_DISABLE();
        #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            MSSP_I2C_InterruptDisable();
        #endif
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *_i2c_obj){
    Std_ReturnType ret = E_OK;
    if(_i2c_obj == NULL){
        ret = E_NOT_OK;
    }else{
       /* initiate start condition --> SEN: Start Condition Enable/Stretch Enable bit*/
       I2C_INITIATE_START_CONDITION();
       /* wait for the start condition to finish we pole --> SEN: Start Condition Enable/Stretch Enable bit */
       while(GET_START_CONDITION_STATE());
       /* Clear MSSP Interrupt Flag */
       MSSP_IterruptFlagClear();
       /* check if the start condition was detected */
       if(CHECK_START_CONDITION_DETECTED() == I2C_START_BIT_NOT_DETECTED){
           ret = E_NOT_OK;
       }
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *_i2c_obj){
    Std_ReturnType ret = E_OK;
    if(_i2c_obj == NULL){
        ret = E_NOT_OK;
    }else{
       /* initiate repeated start condition --> SREN: Start Condition Enable/Stretch Enable bit*/
       I2C_INITIATE_REPEATED_START_CONDITION();
       /* wait for the repeated start condition to finish we pole --> SREN: Repeated Start Condition Enable/Stretch Enable bit */
       while(GET_REPEATED_START_CONDITION_STATE());
       /* Clear MSSP Interrupt Flag */
       MSSP_IterruptFlagClear();
       /* check if the start condition was detected */
       if(CHECK_START_CONDITION_DETECTED() == I2C_START_BIT_NOT_DETECTED){
           ret = E_NOT_OK;
       }
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *_i2c_obj){
    Std_ReturnType ret = E_OK;
    if(_i2c_obj == NULL){
        ret = E_NOT_OK;
    }else{
       /* initiate Stop condition --> PEN: Start Condition Enable/Stretch Enable bit*/
       I2C_INITIATE_STOP_CONDITION();
       /* wait for the stop condition to finish we pole --> PEN: Stop Condition Enable/Stretch Enable bit */
       while(GET_STOP_CONDITION_STATE());
       /* Clear MSSP Interrupt Flag */
       MSSP_IterruptFlagClear();
       /* check if the start condition was detected */
       if(CHECK_STOP_CONDITION_DETECTED() == I2C_STOP_BIT_NOT_DETECTED){
           ret = E_NOT_OK;
       }
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *_i2c_obj, uint8 _i2c_data, uint8 *_ack){
Std_ReturnType ret = E_OK;
    if(_i2c_obj == NULL || _ack == NULL){
        ret = E_NOT_OK;
    }else{
        /* Write data to the SSPBUF register */
        I2C_WRITE_SSPBUF_REG(_i2c_data);
        /* Wait for the MSSP flag to be set: the transmit have finished */
        while(!MSSP_GetIterruptFlag());
        /* Clear MSSP Interrupt Flag */
        MSSP_IterruptFlagClear();
        /* Report Acknowledge 0 = slave received data, 1 = slave did not receive data */
        _ack = I2C_GET_ACK_RECEIVED_FROM_SLAVE_STATE();                
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Read(const mssp_i2c_t *_i2c_obj, uint8 _ack, uint8 *_i2c_data){
    Std_ReturnType ret = E_OK;
    if(_i2c_obj == NULL){
        ret = E_NOT_OK;
    }else{
        /* Master Mode Receive Enable */
        I2C_MASTER_MODE_RECEIVE_ENABLE();
        /* Wait for buffer full flag to be set */
        while(!I2C_GET_SSPBUF_STATUS());
        /* Read The SSPBUF Register */
        *_i2c_data = (uint8)I2C_READ_SSPBUF_REG();
        /* send ACK or NACK after read */
        if(_ack == I2C_MASTER_SEND_ACK){
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_ACK;
        }else if(_ack == I2C_MASTER_SEND_NACK){
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_NACK;
        }
        I2C_INITIATE_MASTER_ACKNOWLEDGE_SEQUENCE();    
    }
    return ret;
}

void MSSP_I2C_ISR(void){
    #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* The Internal MSSP_I2C Interrupt has been occurred (must be cleared in software) */ 
        MSSP_I2C_IterruptFlagClear();
        /* Code : To be executed from MCAL Interrupt Context*/

        /* Callback function gets called every time this ISR executes*/
        if(MSSP_I2C_InterruptHandler){
            MSSP_I2C_InterruptHandler();
        }
    #endif
}

void MSSP_I2C_BC_ISR(void){
    #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* The Internal MSSP I2C Bus Collision Interrupt has been occurred (must be cleared in software) */ 
        MSSP_I2C_BUS_COL_IterruptFlagClear();
        /* Code : To be executed from MCAL Interrupt Context*/

        /* Callback function gets called every time this ISR executes*/
        if(MSSP_I2C_Report_Write_Collision){
            MSSP_I2C_Report_Write_Collision();
        }
    #endif    
}


static inline void MSSP_I2C_GPIO_cfg(void){
    SET_BIT(TRISC, GPIO_PIN3);   /* Serial Clock (SCL) is Input */
    SET_BIT(TRISC, GPIO_PIN4);   /* Serial DATA (SDA) is Input */         
}

static inline void I2C_Master_Mode_Clock_Configuration(const mssp_i2c_t *_i2c_obj){
    SSPCON1bits.SSPM = _i2c_obj->i2c_cfg.i2c_mode_cfg;
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / _i2c_obj->i2c_clock) - 1);
}

static inline void I2C_Slave_Mode_Configuration(const mssp_i2c_t *_i2c_obj){
    SSPCON1bits.SSPM = _i2c_obj->i2c_cfg.i2c_mode_cfg;
}

static inline void I2C_Interrupt_Configuration(const mssp_i2c_t *_i2c_obj){
    /* Configure the interrupt */
    #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_InterruptEnable();
        MSSP_I2C_BUS_COL_InterruptEnable();
        MSSP_I2C_IterruptFlagClear();
        MSSP_I2C_BUS_COL_IterruptFlagClear();
        MSSP_I2C_InterruptHandler = _i2c_obj->I2C_DefaultInterruptHandler;
        MSSP_I2C_Report_Write_Collision = _i2c_obj->I2C_Report_Write_Collision;
        MSSP_I2C_Report_Receive_Overflow = _i2c_obj->I2C_Report_Receive_Overflow;
        /* Configure the interrupt Priority */
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            if(_i2c_obj->mssp_i2c_bc_priority == INTERRUPT_LOW_PRIORITY){
                INTERRUPT_GobalInterruptLowEnable();
                MSSP_I2C_INTERRUPT_LowPrioritySet();
            }else if(_i2c_obj->mssp_i2c_priority == INTERRUPT_HIGH_PRIORITY){
                INTERRUPT_GobalInterruptHighEnable();
                MSSP_I2C_INTERRUPT_HighPrioritySet();
            }    
            if(_i2c_obj->mssp_i2c_bc_priority == INTERRUPT_LOW_PRIORITY){
                INTERRUPT_GobalInterruptLowEnable();
                MSSP_I2C_BUS_COL_INTERRUPT_LowPrioritySet();
            }else if(_i2c_obj->mssp_i2c_bc_priority == INTERRUPT_HIGH_PRIORITY){
                INTERRUPT_GobalInterruptHighEnable();
                MSSP_I2C_BUS_COL_INTERRUPT_HighPrioritySet();
            }    
        #else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable(); 
        #endif
    #endif
}