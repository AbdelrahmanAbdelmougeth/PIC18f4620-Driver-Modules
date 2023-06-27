/* 
 * File:   ecu_chr_lcd_cfg.h
 * Author: abdo9
 *
 * Created on June 26, 2023, 8:29 PM
 */

#include "ecu_chr_lcd.h"

static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t* _lcd, uint8 _dat_command);
static Std_ReturnType lcd_send_4bit_send_enable_signal(const chr_lcd_4bit_t* _lcd);

Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t* _lcd){
    Std_ReturnType ret = E_OK;
    if(_lcd == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_initialize(&(_lcd->lcd_rs));
        ret = gpio_pin_initialize(&(_lcd->lcd_en));
        for(uint8 l_data_pins_counter=0; l_data_pins_counter<4; l_data_pins_counter++){
            ret = gpio_pin_initialize(&(_lcd->lcd_data[l_data_pins_counter]));
        }
        
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t* _lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    if(_lcd == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs), GPIO_LOW);
        ret = lcd_send_4bits(_lcd, command >> 4);
        ret = lcd_send_4bit_send_enable_signal(_lcd);
        ret = lcd_send_4bits(_lcd, command);
        ret = lcd_send_4bit_send_enable_signal(_lcd);
    }
    return ret;
}


Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t* _lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    if(_lcd == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs), GPIO_HIGH);
        ret = lcd_send_4bits(_lcd, data >> 4);
        ret = lcd_send_4bit_send_enable_signal(_lcd);
        ret = lcd_send_4bits(_lcd, data);
        ret = lcd_send_4bit_send_enable_signal(_lcd);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t* _lcd, uint8 row, uint8 column, uint8 data){}
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t* _lcd, uint8 *str){}
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t* _lcd, uint8 row, uint8 column, uint8 *str){}
Std_ReturnType lcd_4bit_custom_char(const chr_lcd_4bit_t* _lcd, uint8 row, uint8 column, const uint8 _chr[], uint8 mem_pos){}


Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t* _lcd){
    Std_ReturnType ret = E_OK;
    if(_lcd == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_initialize(&(_lcd->lcd_rs));
        ret = gpio_pin_initialize(&(_lcd->lcd_en));
        for(uint8 l_data_pins_counter=0; l_data_pins_counter<8; l_data_pins_counter++){
            ret = gpio_pin_initialize(&(_lcd->lcd_data[l_data_pins_counter]));
        }
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t* _lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    if(_lcd == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs), GPIO_LOW);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t* _lcd, uint8 data){}
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t* _lcd, uint8 row, uint8 column, uint8 data){}
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t* _lcd, uint8 *str){}
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t* _lcd, uint8 row, uint8 column, uint8 *str){}
Std_ReturnType lcd_8bit_custom_char(const chr_lcd_8bit_t* _lcd, uint8 row, uint8 column, const uint8 _chr[], uint8 mem_pos){}


void convert_byte_to_string(uint8 value, uint8 *str){}
void convert_short_to_string(uint16 value, uint8 *str){}
void convert_int_to_string(uint32 value, uint8 *str){}


static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t* _lcd, uint8 _dat_command){
    Std_ReturnType ret = E_OK;
    if(_lcd == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(_lcd->lcd_data[0]), (_dat_command >> GPIO_PIN0) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(_lcd->lcd_data[1]), (_dat_command >> GPIO_PIN1) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(_lcd->lcd_data[2]), (_dat_command >> GPIO_PIN2) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(_lcd->lcd_data[3]), (_dat_command >> GPIO_PIN3) & (uint8)0x01);
    }
    return ret;
}

static Std_ReturnType lcd_send_4bit_send_enable_signal(const chr_lcd_4bit_t* _lcd){
    Std_ReturnType ret = E_OK;
    if(_lcd == NULL){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(_lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(_lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}
 