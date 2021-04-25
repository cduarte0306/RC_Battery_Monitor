/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef I2C_PROCESS_H
#define I2C_PROCESS_H    
    
#include <cytypes.h>
#include "data.h"
    
    
typedef struct __attribute__((__packed__))  /* Defining incoming data structure   */
{
    uint8 request;
} i2c_write_data_t;  
    
    
typedef struct __attribute__((__packed__))  /* Defining incoming data structure   */
{
    tx_data_t data_out;
    uint8 cheksum;
} i2c_data_t;

i2c_data_t i2c_data;
i2c_write_data_t i2c_write_data;
    
    
void i2c_update(void);
void i2c_init(void);
    
    
#endif

/* [] END OF FILE */
