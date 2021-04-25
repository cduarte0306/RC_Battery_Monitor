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
#include "project.h"
#include "data.h"
#include "i2c_process.h"
#include "alarm_ctrl.h"
#include "adc.h"


#define INPUT_CURRENT_INDEX     (0u)
#define MOTOR_CURRENT_INDEX     (1u)
#define VOLTAGE_INDEX           (2u)

#define K                       (11u)
#define BATTERY_MAX_VOLTAGE     (7.2f)
#define BATTERY_VOLTAGE_LOW     (5.4f)


void sys_init(void)
{
    I2C_Start();
    ADC_SAR_1_Start();
    AMux_1_Start();
}


float battery_level(float voltage)
{
    float compensated_voltage = voltage * K; // K factor to be proven
    return 100*(compensated_voltage - BATTERY_VOLTAGE_LOW)/(BATTERY_MAX_VOLTAGE - BATTERY_VOLTAGE_LOW);    
}


void read_data(void)
{
    tx_data.charge_data = (uint8)battery_level((float)ADC_SAR_1_CountsTo_Volts(adc_read(VOLTAGE_INDEX)));
    tx_data.input_current = adc_read(INPUT_CURRENT_INDEX);
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    sys_init();
    
    ADC_SAR_1_StartConvert();
    
    i2c_init();

    for(;;)
    {   
        adc_update();
        read_data();
        alarm_update();
        i2c_update();
    }
}

/* [] END OF FILE */