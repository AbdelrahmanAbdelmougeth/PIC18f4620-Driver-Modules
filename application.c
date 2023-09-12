/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

mssp_i2c_t i2c_obj;

#define _slave1 0x60
#define _slave2 0x61

volatile uint8 i2c_slave1_rec_counter;

void MSSP_I2C_DefaultInterruptHandler(){
    i2c_slave1_rec_counter++;
}

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    i2c_obj.i2c_cfg.i2c_mode = MSSP_I2C_SLAVE_MODE;
    i2c_obj.i2c_cfg.i2c_mode_cfg = I2C_SLAVE_MODE_7_BIT_ADDRESS;
    i2c_obj.i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLED;
    i2c_obj.i2c_cfg.i2c_slave_add = _slave1;
    i2c_obj.i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLED;
    i2c_obj.i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLED;
    i2c_obj.I2C_DefaultInterruptHandler = MSSP_I2C_DefaultInterruptHandler;
    i2c_obj.I2C_Report_Receive_Overflow = NULL;
    i2c_obj.I2C_Report_Write_Collision = NULL;
    ret = MSSP_I2C_Init(&i2c_obj);
    
    while(1){  
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
