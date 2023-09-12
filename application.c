/* 
 * File:   application.c
 * Author: abdo9
 *
 * Created on May 14, 2023, 8:44 PM
 */


#include "application.h"

mssp_i2c_t i2c_obj;
uint8 _slave_ack = 0xff;

#define _slave1 0x60
#define _slave2 0x61

void MSSP_I2C_Send_1_Byte(uint8 _slave_add, uint8 _data){
    Std_ReturnType ret = E_NOT_OK;
    ret = MSSP_I2C_Master_Send_Start(&i2c_obj);
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, _slave_add , &_slave_ack);
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, _data, &_slave_ack);
    ret = MSSP_I2C_Master_Send_Stop(&i2c_obj);
}

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    
    i2c_obj.i2c_clock = 100000;
    i2c_obj.i2c_cfg.i2c_mode = MSSP_I2C_MASTER_MODE;
    i2c_obj.i2c_cfg.i2c_mode_cfg = I2C_MASTER_MODE_DEFINED_CLOCK;
    i2c_obj.i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLED;
    i2c_obj.i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLED;
    i2c_obj.i2c_cfg.i2c_master_receive_mode = I2C_MASTER_MODE_RECEIVE_DISABLED;
    i2c_obj.I2C_DefaultInterruptHandler = NULL;
    i2c_obj.I2C_Report_Receive_Overflow = NULL;
    i2c_obj.I2C_Report_Write_Collision = NULL;
    ret = MSSP_I2C_Init(&i2c_obj);
    
    while(1){  
        MSSP_I2C_Send_1_Byte(_slave1, 'a');
        __delay_ms(1000);
        MSSP_I2C_Send_1_Byte(_slave2, 'b');
        __delay_ms(1000);
        MSSP_I2C_Send_1_Byte(_slave1, 'c');
        __delay_ms(1000);
        MSSP_I2C_Send_1_Byte(_slave2, 'd');
        __delay_ms(1000);
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();
}
