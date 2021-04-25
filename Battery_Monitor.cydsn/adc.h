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

#ifndef ADC_H
#define ADC_H
    
#include <cytypes.h>
    

void adc_update(void);
uint16 adc_read(uint8 channel);
    
#endif

/* [] END OF FILE */
