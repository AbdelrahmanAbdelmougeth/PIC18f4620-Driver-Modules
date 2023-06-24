/* 
 * File:   ecu_led.c
 * Author: abdo9
 *
 * Created on May 15, 2023, 1:31 PM
 */

#include "ecu_keypad.h"

static const uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLS] = {
                                                                    {'7','8','9','/'},
                                                                    {'4','5','6','*'},
                                                                    {'1','2','3','-'},
                                                                    {'#','0','=','+'},
                                                                  };

/**
 * 
 * @param _keypad_obj
 * @return 
 */
Std_ReturnType keypad_initialize (const keypad_t *_keypad_obj){
    Std_ReturnType ret = E_OK;
    if(_keypad_obj == NULL){
        ret = E_NOT_OK;
    }else{
        for(uint8 row_counter = ZERO_INIT; row_counter<ECU_KEYPAD_ROWS; row_counter++){
            ret = gpio_pin_initialize(&(_keypad_obj->keypad_row_pins[row_counter]));
        }
        for(uint8 cols_counter = ZERO_INIT; cols_counter<ECU_KEYPAD_COLS; cols_counter++){
            ret = gpio_pin_direction_initialize(&(_keypad_obj->keypad_col_pins[cols_counter]));
        }
    }
    return ret;
}

/**
 * @param _keypad_obj
 * @param value
 * @return 
 */
Std_ReturnType keypad_get_value (const keypad_t *_keypad_obj, uint8 *value){
    Std_ReturnType ret = E_OK;
    if(_keypad_obj == NULL || value == NULL){
        ret = E_NOT_OK;
    }else{
        logic_t column_logic = ZERO_INIT;
        uint8 c=0, cOld=0, count=0;
        while(1){
            c=0;
            for(uint8 l_rows_counter=ZERO_INIT; l_rows_counter < ECU_KEYPAD_ROWS; l_rows_counter++){
                for (uint8 l_counter=ZERO_INIT; l_counter<ECU_KEYPAD_ROWS; l_counter++){
                    ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_counter]), GPIO_LOW);
                }  
                gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_rows_counter]), GPIO_HIGH);
                for(uint8 l_columns_counter=ZERO_INIT; l_columns_counter < ECU_KEYPAD_COLS; l_columns_counter++){
                    ret = gpio_pin_read_logic(&(_keypad_obj->keypad_col_pins[l_columns_counter]), &column_logic);
                    if(column_logic == GPIO_HIGH){
                        c = btn_values[l_rows_counter][l_columns_counter];
                    }
                }
            }
            if(c != 0 && cOld == 0){count = 0;}
            
            if(c != 0)
                {cOld = c;}
            else 
                {count++;}
            
            if(count == 20 && cOld != 0) {break;}
        }
        *value = cOld;
    }
    return ret;
}
