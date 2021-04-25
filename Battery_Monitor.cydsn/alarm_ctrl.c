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

#include "alarm_ctrl.h"
#include "project.h"
#include "adc.h"
#include "data.h"


#define AMP_GAIN                (200u)    // Combined opamp gain
#define MOTOR_CURRENT_INDEX     (2u)      // Motor current adc index
#define CURRENT_MAX             (4.0f)    // Maximum allowed motor current 
#define WEIGHT                  (0.001f)  // Filter weight factor
#define R_SENSE                 (0.025f)  // Sense resistor 

#define TRUE    (1u)
#define FALSE   (0u)


static float motor_current_avg;


/* Function used to further smooth the incoming current reading */
float avg(float* ret, uint16 val, double weight)
{
    *ret += (val - *ret) * weight;
    return *ret;
}


void alarm_update(void)
{   
    float r_sense_voltage = ADC_SAR_1_CountsTo_Volts(adc_read(MOTOR_CURRENT_INDEX)) / AMP_GAIN;
    float filtered_voltage = avg(&motor_current_avg, r_sense_voltage, WEIGHT);
    float motor_current = filtered_voltage / R_SENSE;
    
    if(motor_current >= CURRENT_MAX)
        Alert_Write(TRUE);
        
    else Alert_Write(FALSE);
}

/* [] END OF FILE */
