/* 
 * File:   hal_spi.c
 * Author: hp
 *
 * Created on 14 ??????, 2023, 07:36 ?
 */

/*
 * Interrupt Features
 * Receive Operation (SSPSR and SSPBUF together create a double-buffered receiver)
    * complete byte --------> SSPSR -> SSPBUF -> SSPIF interrupt and BF Buffer Full detect bit are set
 * Transmit Operation ( the SSPBUF is not double buffered. A write to SSPBUF will write to both SSPBUF and SSPSR)
    * complete byte --------> SSPSR -> SSPBUF -> SSPIF interrupt and BF Buffer Full detect bit are set
 */

#include "hal_spi.h"

static inline void SPI_Interrupt_Configuration(const spi_t *_spi_obj);

#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void(* MSSP_SPI_InterruptHandler)(void) = NULL;              
#endif 
    
Std_ReturnType SPI_Init(const spi_t *_spi_obj){
    Std_ReturnType ret = E_OK;
    if(_spi_obj == NULL){
        ret = E_NOT_OK;
    }else{
        /* Disable SPI Module */
        MSSP_SPI_MODULE_DISABLE();
        
        /* SPI Mode Select */
        /* SPI Master Mode Configurations */
        if(_spi_obj->spi_mode == SPI_MASTER_MODE_FOSC_DIV_4 || _spi_obj->spi_mode == SPI_MASTER_MODE_FOSC_DIV_16 ||
           _spi_obj->spi_mode == SPI_MASTER_MODE_FOSC_DIV_64 || _spi_obj->spi_mode == SPI_MASTER_MODE_TMR2_CLOCK){
            
            /* Configure SPI I/O Pins To Work in master mode */
            MASTER_CONFIG_SPI_IO_PINS();
            /* Configure SMP: Sample bit (Clear for slave mode)*/
            CONFIG_SAMPLE_INPUT_DATA_BIT(_spi_obj->spi_config.SampleSelect);
        }
        /* SPI Slave Mode Configurations */
        else if(_spi_obj->spi_mode == SPI_SLAVE_MODE_SS_ENABLED || _spi_obj->spi_mode == SPI_SLAVE_MODE_SS_DISABLED){
            /* Configure SPI I/O Pins To Work in slave mode */
            SLAVE_CONFIG_SPI_IO_PINS();
            /* SSPOV: Receive Overflow Indicator bit (Slave Mode Only) */
            CLEAR_RECEIVE_OVERFLOW_BIT();
            /* Configure SMP: Sample bit (Clear for slave mode)*/
            CONFIG_SAMPLE_INPUT_DATA_BIT(0);
        }
        else{/* nothing */}
        
        /* SPI Set Master/Slave Operation Mode */
        MSSP_SPI_SET_MODE(_spi_obj->spi_mode);
        
        /* Clear WCOL: Write Collision Detect bit */
        CLEAR_WRITE_COLLISION_BIT();
        
        /* Configure the interrupt */
        #if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            SPI_Interrupt_Configuration(_spi_obj);
        #endif

        /* Enable SPI Module */
        MSSP_SPI_MODULE_ENABLE();     
    }
    return ret;
}

Std_ReturnType SPI_DeInit(const spi_t *_spi_obj){
    Std_ReturnType ret = E_OK;
    if(_spi_obj == NULL){
        ret = E_NOT_OK;
    }else{
        /* Disable I2C Module */
        MSSP_SPI_MODULE_DISABLE();
        #if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            MSSP_SPI_InterruptDisable();
        #endif
    }
    return ret;
}

/* Must be used with interrupt feature disabled */
Std_ReturnType SPI_Send_Byte_Blocking(const spi_t *_spi_obj, const uint8 _data){
    Std_ReturnType ret = E_OK;
    if(_spi_obj == NULL){
        ret = E_NOT_OK;
    }else{        
        SSPBUF_WRITE_REG(_data);
        while(!(PIR1bits.SSPIF)); /* Waiting to transmit */
        PIR1bits.SSPIF = 0;
    }
    return ret;
}

Std_ReturnType SPI_Read_Byte_Blocking(const spi_t *_spi_obj, uint8 *_data){
    Std_ReturnType ret = E_OK;
    if(_spi_obj == NULL || _data == NULL){
        ret = E_NOT_OK;
    }else{
        while(SSPSTATbits.BF == 0); /* Receive not complete, SSPBUF is empty */
        *_data = SSPBUF;   
    }
    return ret;
}

Std_ReturnType SPI_Send_Byte_NonBlocking(const spi_t *_spi_obj, const uint8 _data){
    Std_ReturnType ret = E_OK;
    if(_spi_obj == NULL){
        ret = E_NOT_OK;
    }else{
       SSPBUF_WRITE_REG(_data);
    }
    return ret;
}

Std_ReturnType SPI_Read_Byte_NonBlocking(const spi_t *_spi_obj, uint8 *_data){
    Std_ReturnType ret = E_OK;
    if(_spi_obj == NULL || _data == NULL){
        ret = E_NOT_OK;
    }else{ 
        if(GET_SSPBUF_STATE()){
            *_data = SSPBUF;
        }else if(GET_SSPBUF_STATE()){
            ret = E_NOT_OK;
        } 
    }
    return ret;
}

void MSSP_SPI_ISR(void){
    #if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* The Internal MSSP_SPI Interrupt has been occurred (must be cleared in software) */ 
        MSSP_SPI_IterruptFlagClear();
        /* Code : To be executed from MCAL Interrupt Context*/

        /* Callback function gets called every time this ISR executes*/
        if(MSSP_SPI_InterruptHandler){
            MSSP_SPI_InterruptHandler();
        }
    #endif
}


static inline void SPI_Interrupt_Configuration(const spi_t *_spi_obj){
    /* Configure the interrupt */
    #if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        MSSP_SPI_InterruptEnable();
        MSSP_SPI_IterruptFlagClear();
        MSSP_SPI_InterruptHandler = _spi_obj->MSSP_SPI_InterruptHandler;
        /* Configure the interrupt Priority */
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            if(_spi_obj->priority == INTERRUPT_LOW_PRIORITY){
                INTERRUPT_GobalInterruptLowEnable();
                MSSP_SPI_INTERRUPT_LowPrioritySet();
            }else if(_spi_obj->priority == INTERRUPT_HIGH_PRIORITY){
                INTERRUPT_GobalInterruptHighEnable();
                MSSP_SPI_INTERRUPT_HighPrioritySet();
            }       
        #else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable(); 
        #endif
    #endif
}