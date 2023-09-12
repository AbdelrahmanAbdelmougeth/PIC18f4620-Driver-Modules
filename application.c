/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

mssp_i2c_t i2c_obj;

#define _slave1 0x60
#define _slave2 0x62

volatile uint8 i2c_slave2_rec_counter;
static volatile uint8 i2c_slave2_rec_data;

void MSSP_I2C_DefaultInterruptHandler(){
    /* Stretch SCK To force the master to stay idle and don't send any data */
    /* Stretch Enable bit : Clock stretching is enabled for both slave transmit and slave receive */
    I2C_CLOCK_STRETCH_ENABLE();
    /* Check If The Master Needs To Read/Write and the last received byte wasn't an address*/
    if(SSPSTATbits.R_nW == 0 && SSPSTATbits.D_nA == 0){
        uint8 dummy_buffer = SSPBUF;  /* read the last byte to clear the buffer */
        while(!I2C_GET_SSPBUF_STATUS()); /* wait for the data to be completely received */
        i2c_slave2_rec_data = SSPBUF; /* read the data */
    }else if(SSPSTATbits.R_nW = 1){
        
    }else{ /* nothing */ }
    
    /* SCK Stretch disable */
    I2C_CLOCK_STRETCH_DISABLE();
    
    i2c_slave2_rec_counter++;
}

led_t led1 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    i2c_obj.i2c_cfg.i2c_mode = MSSP_I2C_SLAVE_MODE;
    i2c_obj.i2c_cfg.i2c_mode_cfg = I2C_SLAVE_MODE_7_BIT_ADDRESS;
    i2c_obj.i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLED;
    i2c_obj.i2c_cfg.i2c_slave_add = _slave2;
    i2c_obj.i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLED;
    i2c_obj.i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLED;
    i2c_obj.I2C_DefaultInterruptHandler = MSSP_I2C_DefaultInterruptHandler;
    i2c_obj.I2C_Report_Receive_Overflow = NULL;
    i2c_obj.I2C_Report_Write_Collision = NULL;
    ret = MSSP_I2C_Init(&i2c_obj);
    led_initialize(&led1);
    
    while(1){  
        if(i2c_slave2_rec_data == 'b'){
            led_turn_on(&led1);
        }else if(i2c_slave2_rec_data == 'd'){
            led_turn_off(&led1);
        } 
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
