/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWRE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef DATA_H
#define DATA_H
    
#include <cytypes.h>

    
typedef struct __attribute__((__packed__))  /* Defining incoming data structure   */
{
    uint8 charge_data;
    uint16 input_current;
} tx_data_t;

tx_data_t tx_data;  
uint16 current_data;

#endif

/* [] END OF FILE */
