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

// Definitions
#define BUZZER_ON BUZZER_PWM_WriteCompare(127)
#define BUZZER_OFF BUZZER_PWM_WriteCompare(0)
#define RED     0b001
#define YELLOW  0b011
#define GREEN   0b010
#define CYAN    0b110
#define BLUE    0b100
#define MAGENTA 0b101

typedef enum FSM_State{
    INIT,
    IDLE,
    SD_ERROR,
    TARE,
    READY,
    RECORD,
    SAVE    
}FSM_State;

// Program Variables
FSM_State state = INIT;

// Main Program
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    //UI
    LCD_Start();
    LED_Write(0b000);
    BUZZER_PWM_Start();
    BUZZER_OFF;
    
    //Data Storage
    //SD_CARD_Start();
    
    //Encoder
    ARM_ANGLE_ENCODER_Start();
    
    //Accelerometer
    ACC_ADC_Start();
    
    LCD_PrintString("STS");
    LED_Write(RED);
    // Main Loop
    for(;;)
    {      
        // Program State Machine
        switch(state){
            case INIT:
                LED_Write(RED);
                break;
            
            case IDLE:
                LED_Write(GREEN);
                break;
            
            case SD_ERROR:
                LED_Write(RED);
                break;
            
            case TARE:
                LED_Write(CYAN);
                break;
            
            case READY:
                LED_Write(BLUE);
                break;
            
            case RECORD:
                LED_Write(MAGENTA);
                break;
            
            case SAVE:
                LED_Write(MAGENTA);
                break;
        }
    }
}

/* [] END OF FILE */
