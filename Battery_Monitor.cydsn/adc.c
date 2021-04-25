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

#include "adc.h"
#include "project.h"


#define NUM_CHANNELS    (3u)


static uint16 adc_cache[NUM_CHANNELS];
static uint8 curr_ch = 0;


void adc_update(void)
{    
    if(ADC_SAR_1_IsEndConversion(ADC_SAR_1_RETURN_STATUS))
    {
        adc_cache[curr_ch] = CY_GET_REG16(ADC_SAR_1_SAR_WRK_PTR) - ADC_SAR_1_shift;
        curr_ch = (curr_ch + 1 >= NUM_CHANNELS)? 0: curr_ch + 1;
        
        AMux_1_FastSelect(curr_ch);
        ADC_SAR_1_StartConvert();
    }
}


uint16 adc_read(uint8 channel)
{
    return adc_cache[channel];
}

/* [] END OF FILE */
