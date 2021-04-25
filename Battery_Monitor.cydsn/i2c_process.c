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

#include "i2c_process.h"
#include "project.h"
#include "data.h"


#define I2C_ADDR        (0x04)
#define LEFT_SHIFT      (8u)
#define WR_SIZE         (1u)
#define CMD             (0x01)


static uint8 read_buff[sizeof(i2c_data_t)];
static uint8 wr_buff[WR_SIZE];


static uint8 cheksum_out(tx_data_t* buf)
{
    uint8 cheksum_buffer[sizeof(tx_data_t)];
    uint32 cheksum = 0;

    /* Copy contents onto sumation buffer */
    memcpy(cheksum_buffer, buf, sizeof(tx_data_t));
    
    for(uint8 i = 0; i < sizeof(tx_data_t); i++)
    {
        cheksum += cheksum_buffer[i];
    }
       
    return cheksum & 0xFF;
}


void i2c_init(void)
{
    // Need to initialize the read buffer for the master to access during transaction request
    I2C_SlaveSetAddress(I2C_ADDR);
    I2C_SlaveInitReadBuf(read_buff, sizeof(i2c_data_t));
    I2C_SlaveInitWriteBuf(wr_buff, sizeof(wr_buff));
}


void i2c_update(void)
{        
    // Populating the write data struct
    i2c_data.cheksum = cheksum_out(&tx_data);
    memcpy(&i2c_data.data_out, &tx_data, sizeof(tx_data_t));
     
    /* After all of read buffer has been read */
    if(I2C_SlaveGetWriteBufSize() > 0)
    {   
        memcpy(&i2c_write_data, wr_buff, sizeof(wr_buff));
        if(i2c_write_data.request == CMD)
        {
            memcpy(&read_buff, &i2c_data, sizeof(i2c_data_t));

            /* If all contents of the write buffer have been written, clear the buffer */
            if(I2C_SlaveGetWriteBufSize() == sizeof(wr_buff))
            {
                I2C_SlaveClearWriteBuf();
            }
        }
    }
    
    /* Clear read buff if all of it contents have been read */
    if(I2C_SlaveGetReadBufSize() == sizeof(i2c_data_t))
    {
        I2C_SlaveClearReadBuf();
    }
}

/* [] END OF FILE */
