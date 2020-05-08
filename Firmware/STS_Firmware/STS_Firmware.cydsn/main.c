/* ========================================
 * FILE:   main.c
 * AUTHOR: Caleb Cotter
 * 
 * DESCRIPTION: MAIN FILE FOR SHOCK TEST
 * STAND DATA AQUISITION SYSTEM.
 *
 * CREATED ON MAY 6, 2020, 7:45 PM
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
#include "project.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    //UI
    LCD_Start();
    RGB_LED_Write(0b000);
    BUZZER_Write(0b0);
    
    //Data Storage
    //SD_CARD_Start();
    
    //Encoder
    ARM_ANGLE_ENCODER_Start();
    
    //Accelerometer
    ACC_ADC_Start();
    

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
