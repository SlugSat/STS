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
#include "config.h"

#include <FS.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Definitions
#define BUZZER_ON BUZZER_PWM_WriteCompare(127)
#define BUZZER_OFF BUZZER_PWM_WriteCompare(0)
#define OFF     0b000
#define RED     0b001
#define YELLOW  0b011
#define GREEN   0b010
#define CYAN    0b110
#define BLUE    0b100
#define MAGENTA 0b101

typedef enum FSM_State{
    SPLASH_SCREEN,
    LIVE_READOUT,
    TARE_SELECT,
    TARE,
    EJECT_SELECT,
    EJECT,
    FORMAT_SELECT,
    FORMAT_CONFIRM,
    FORMAT,
    SD_ERROR_DISPLAY
}FSM_State;

typedef enum event_t{
    NO_EVENT,
    UP_CLICK,
    DOWN_CLICK,
    SELECT_CLICK
}event_t;

enum {
    X,
    Y,
    Z
};

// SD Variables
char sdVolName[10];
FS_FILE * pFile;

// Program Variables
FSM_State ui_state = SPLASH_SCREEN;
event_t event = NO_EVENT;

bool update_ui = false;
char LCD_MSG[2][16];

int encRaw = 0;
float encAngle = 0;
float encAnglePrev = 0;

float rawAccelZeroOffset[3] = {0};

// ISR Prototypes
CY_ISR_PROTO(UP_CLICK_ISR);
CY_ISR_PROTO(DOWN_CLICK_ISR);
CY_ISR_PROTO(SELECT_CLICK_ISR);
CY_ISR_PROTO(UPDATE_UI_ISR);

// Helper Function Prototypes
void EnableButtonISRs(void);
void DisableButtonISRs(void);
void UpdateLCD(void);

// Main Program
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    //UI
    LCD_Start();
    LED_Write(0b000);
    BUZZER_PWM_Start();
    BUZZER_OFF;
    UP_CLICK_ISR_StartEx(UP_CLICK_ISR);
    DOWN_CLICK_ISR_StartEx(DOWN_CLICK_ISR);
    SELECT_CLICK_ISR_StartEx(SELECT_CLICK_ISR);
    UPDATE_UI_ISR_StartEx(UPDATE_UI_ISR);
    UI_TIMER_Start();
    
    //Data Storage
    FS_Init();
    
    //Encoder
    ARM_ANGLE_ENCODER_Start();
    
    //Accelerometer
    ACC_ADC_Start();
    
    
    FS_GetVolumeName(0u, &sdVolName[0], 9u);
    event = NO_EVENT;
    // Main Loop
    for(;;)
    {   
        // Collect Sensor Data
        encAnglePrev = encAngle;
        encRaw = ARM_ANGLE_ENCODER_GetCounter();
        encAngle = ((float) encRaw) / ((float) ENCODER_COUNTS_PER_REV) * 360;
        if(encAngle >= LIFT_THRESHOLD_DEG && encAnglePrev < LIFT_THRESHOLD_DEG){

        }
        if(encAngle >= LIFT_THRESHOLD_DEG){
            BUZZER_ON;
            
        } else {
            BUZZER_OFF;
            
        }
        
        
        // UI State Machine
        if(update_ui){
            switch(ui_state){
                case SPLASH_SCREEN:
                    sprintf(LCD_MSG[0],"Shock Test Stand");
                    sprintf(LCD_MSG[1]," ");
                    UpdateLCD();
                    LED_Write(RED);
                    
                    switch(event){
                        case NO_EVENT:
                            break;
                        case UP_CLICK:
                        case DOWN_CLICK:
                        case SELECT_CLICK:
                            ui_state = LIVE_READOUT;
                            event = NO_EVENT;
                    }
                    break;
                
                case LIVE_READOUT:
                    sprintf(LCD_MSG[0],"Ready, Idle");
                    sprintf(LCD_MSG[1],"  %.1f deg", encAngle);
                    UpdateLCD();
                    LCD_Position(1u, 0u);
                    LCD_PutChar(LCD_CUSTOM_0);
                    
                    LED_Write(GREEN);
                    
                    switch(event){
                        case NO_EVENT:
                            break;
                        case UP_CLICK:
                            event = NO_EVENT;
                            break;
                        case DOWN_CLICK:
                            ui_state = TARE_SELECT;
                            event = NO_EVENT;
                            break;
                        case SELECT_CLICK:
                            break;
                    }
                    break;
                
                case TARE_SELECT:
                    sprintf(LCD_MSG[0],">Tare");
                    sprintf(LCD_MSG[1]," Eject SD Card");
                    UpdateLCD();
                    LED_Write(YELLOW);
                    
                    switch(event){
                        case NO_EVENT:
                            break;
                        case UP_CLICK:
                            ui_state = LIVE_READOUT;
                            event = NO_EVENT;
                            break;
                        case DOWN_CLICK:
                            ui_state = EJECT_SELECT;
                            event = NO_EVENT;
                            break;
                        case SELECT_CLICK:
                            ui_state = TARE;
                            event = NO_EVENT;
                            break;
                    }
                    break;
                
                case TARE:
                    sprintf(LCD_MSG[0],"Taring system...");
                    sprintf(LCD_MSG[1]," ");
                    UpdateLCD();
                    LED_Write(CYAN);
                    
                    CyDelay(500);
                    ARM_ANGLE_ENCODER_SetCounter(0);
                    
                    ui_state = LIVE_READOUT;
                    event = NO_EVENT;
                    break;
                
                case EJECT_SELECT:
                    sprintf(LCD_MSG[0]," Tare");
                    sprintf(LCD_MSG[1],">Eject SD Card");
                    UpdateLCD();
                    LED_Write(YELLOW);
                    
                    switch(event){
                        case NO_EVENT:
                            break;
                        case UP_CLICK:
                            ui_state = TARE_SELECT;
                            event = NO_EVENT;
                            break;
                        case DOWN_CLICK:
                            ui_state = FORMAT_SELECT;
                            event = NO_EVENT;
                            break;
                        case SELECT_CLICK:
                            ui_state = EJECT;
                            event = NO_EVENT;
                            break;
                    }
                    break;
                
                case EJECT:
                    sprintf(LCD_MSG[0],"Ejecting SD...");
                    sprintf(LCD_MSG[1]," ");
                    UpdateLCD();
                    LED_Write(CYAN);
                    CyDelay(1000);
                    
                    
                    ui_state = LIVE_READOUT;
                    event = NO_EVENT;
                    break;
                    
                case FORMAT_SELECT:
                    sprintf(LCD_MSG[0],">Format SD");
                    sprintf(LCD_MSG[1]," ---");
                    UpdateLCD();
                    LED_Write(YELLOW);
                    
                    switch(event){
                        case NO_EVENT:
                            break;
                        case UP_CLICK:
                            ui_state = EJECT_SELECT;
                            event = NO_EVENT;
                            break;
                        case DOWN_CLICK:
                            event = NO_EVENT;
                            break;
                        case SELECT_CLICK:
                            ui_state = FORMAT_CONFIRM;
                            event = NO_EVENT;
                            break;
                    }
                    break;
                
                case FORMAT_CONFIRM:
                    LCD_Position(0u, 0u);
                    LCD_PrintString("Confirm Format");
                    LCD_Position(1u, 0u);
                    LCD_PutChar('Y');
                    LCD_PutChar(LCD_CUSTOM_2);
                    LCD_PutChar(' ');
                    LCD_PutChar('N');
                    LCD_PutChar(LCD_CUSTOM_3);
                    LED_Write(RED);
                    
                    switch(event){
                        case NO_EVENT:
                            break;
                        case UP_CLICK:
                            ui_state = FORMAT;
                            event = NO_EVENT;
                            break;
                        case DOWN_CLICK:
                            ui_state = LIVE_READOUT;
                            event = NO_EVENT;
                            break;
                        case SELECT_CLICK:
                            break;
                    }
                    break;
                    
                case FORMAT:
                    sprintf(LCD_MSG[0],"Formatting...");
                    sprintf(LCD_MSG[1],"");
                    UpdateLCD();
                    LED_Write(CYAN);
                    
                    DisableButtonISRs();
                    FS_FormatSD(sdVolName);
                    FS_MkDir("Data");
                    pFile = FS_FOpen("config.txt", "w");
                    if(pFile){
                        FS_Write(pFile, "STS V0.1", 8u);
                        FS_FClose(pFile);
                    }
                    EnableButtonISRs();
                    ui_state = LIVE_READOUT;
                    event = NO_EVENT;
                    break;
                
                case SD_ERROR_DISPLAY:
                    sprintf(LCD_MSG[0],"Error: ");
                    sprintf(LCD_MSG[1],"No SD Card Found");
                    LED_Write(RED);
                    break;
            }
            update_ui = false;
        }
    }
}

CY_ISR(UPDATE_UI_ISR){
    update_ui = true;
}

CY_ISR(UP_CLICK_ISR){
    event = UP_CLICK;
}

CY_ISR(DOWN_CLICK_ISR){
    event = DOWN_CLICK;
}

CY_ISR(SELECT_CLICK_ISR){
    event = SELECT_CLICK;
}

void EnableButtonISRs(void){
    UP_CLICK_ISR_Enable();
    DOWN_CLICK_ISR_Enable();
    SELECT_CLICK_ISR_Enable();
}

void DisableButtonISRs(void){
    UP_CLICK_ISR_Disable();
    DOWN_CLICK_ISR_Disable();
    SELECT_CLICK_ISR_Disable();
}

void UpdateLCD(void){
    LCD_ClearDisplay();
    LCD_Position(0,0);
    LCD_PrintString(LCD_MSG[0]);
    LCD_Position(1,0);
    LCD_PrintString(LCD_MSG[1]);
}

/* [] END OF FILE */
