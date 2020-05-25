/* ========================================
 * FILE:   DS1307.h
 * AUTHOR: Caleb Cotter
 *
 * CREATED ON MAY 25, 2020, 12:24 PM
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
#ifndef DS1307_H
#define DS1307_H

#include "I2C.h"   
#include <stdint.h>

// I2C Address
#define DS1307_I2C_ADDRESS 0x68
// Register Map
#define DS1307_SECONDS_REG  0x00
#define DS1307_MINUTES_REG  0x01
#define DS1307_HOURS_REG    0x02
#define DS1307_DAY_REG      0x03
#define DS1307_DATE_REG     0x04
#define DS1307_MONTH_REG    0x05
#define DS1307_YEAR_REG     0x06
#define DS1307_CNTRL_REG    0x07
    
// Bit Masks
#define DS1307_CH_BITMASK       0x80
#define DS1307_24HR_BITMASK     0x3F

// Constants
#define Y2K 2000

enum{
    Sunday = 1,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

enum{
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

// Data Types
typedef struct timedate{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint16_t year;
}timedate;
    
// Function Definitions
void RTC_Init(void);

timedate RTC_ReadTimeDate(void);
void RTC_SetTimeDate(timedate data);

#endif
/* [] END OF FILE */
