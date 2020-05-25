/* ========================================
 * FILE:   DS1307.c
 * AUTHOR: Caleb Cotter
 *
 * CREATED ON MAY 25, 2020, 12:28 PM
 *
 * ========================================
 *
 * Copyright SLUGSAT, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF SLUGSAT.
 *
 * ========================================
*/

#include "DS1307.h"

uint8_t dec2bcd(uint8_t num)
{
  return ((num/10 * 16) + (num % 10));
}
uint8_t bcd2dec(uint8_t num)
{
  return ((num/16 * 10) + (num % 16));
}

void RTC_Init(void){
    // Open I2C Connection
    I2C_Init();
    
    // Configure DS1307
    uint8_t temp = I2C_ReadRegister(DS1307_I2C_ADDRESS,DS1307_SECONDS_REG);
}

timedate RTC_ReadTimeDate(void){
    timedate data;
    data.seconds = bcd2dec(~(DS1307_CH_BITMASK) & I2C_ReadRegister(DS1307_I2C_ADDRESS,DS1307_SECONDS_REG));
    data.minutes = bcd2dec(I2C_ReadRegister(DS1307_I2C_ADDRESS,DS1307_MINUTES_REG));
    data.hours = bcd2dec(I2C_ReadRegister(DS1307_I2C_ADDRESS,DS1307_HOURS_REG) & DS1307_24HR_BITMASK);
    data.date = bcd2dec(I2C_ReadRegister(DS1307_I2C_ADDRESS,DS1307_DAY_REG));
    data.month = bcd2dec(I2C_ReadRegister(DS1307_I2C_ADDRESS,DS1307_MONTH_REG));
    data.year = bcd2dec(I2C_ReadRegister(DS1307_I2C_ADDRESS,DS1307_YEAR_REG)) + Y2K;
    return data;
}

void RTC_SetTimeDate(timedate data){
    I2C_WriteReg(DS1307_I2C_ADDRESS,DS1307_SECONDS_REG,dec2bcd(data.seconds));
    I2C_WriteReg(DS1307_I2C_ADDRESS,DS1307_MINUTES_REG,dec2bcd(data.minutes));
    I2C_WriteReg(DS1307_I2C_ADDRESS,DS1307_HOURS_REG,dec2bcd(data.hours));
    I2C_WriteReg(DS1307_I2C_ADDRESS,DS1307_DAY_REG,dec2bcd(data.date));
    I2C_WriteReg(DS1307_I2C_ADDRESS,DS1307_MONTH_REG,dec2bcd(data.month));
    I2C_WriteReg(DS1307_I2C_ADDRESS,DS1307_YEAR_REG,dec2bcd(data.year - Y2K));
}

/* [] END OF FILE */
