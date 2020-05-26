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
#include "eventQueue.h"
#include "DS1307.h"

#include "FS.h"
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

#define ADC_DMA_BYTES_PER_BURST 2
#define ADC_DMA_REQUEST_PER_BURST 1
#define ADC_DMA_SRC_BASE (CYDEV_PERIPH_BASE)
#define ADC_DMA_DST_BASE (CYDEV_SRAM_BASE)

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
    TIMEDATE_SELECT,
    TIMEDATE_SET,
    ARMED,
    DROPPED,
    PROCESSING,
    RECORDING,
    RESULTS,
    ERROR_DISPLAY
}FSM_State;

enum {
    X,
    Y,
    Z
};

enum {
    BUFF_A,
    BUFF_B
};

// SD Variables
char sdVolName[10];
FS_FILE * pFile;
FS_FILE * rawFile;
FS_FILE * csvFile;
char strbuff[80];
char rawfilename[48];
char csvfilename[48];
U32 TimeStamp;
FS_FILETIME FileTime;
int i;

// ADC Variables
uint16_t ADC_Buffer_A[4095]; //1365 per axis
uint16_t ADC_Buffer_B[4095]; //1365 per axis
uint8 ADC_DMA_Chan;
uint8 ADC_DMA_TD[2];
float rawAccelZeroOffset[3] = {0};
uint8 currADCBuff = BUFF_B;
bool accDataReady = false;

// Encoder Variables
int encRaw = 0;
float encAngle = 0;
float encAnglePrev = 0;
float maxAngle = 0;

// Program Variables
FSM_State ui_state = SPLASH_SCREEN;
EventQueuePtr_t eventQueue = NULL;
event_t event = NO_EVENT;
bool update_ui = false;
char LCD_MSG[2][16];
timedate now;

// ISR Prototypes
CY_ISR_PROTO(UP_CLICK_ISR);
CY_ISR_PROTO(DOWN_CLICK_ISR);
CY_ISR_PROTO(SELECT_CLICK_ISR);
CY_ISR_PROTO(UPDATE_UI_ISR);
CY_ISR_PROTO(SWITCH_BUFFER_ISR);
CY_ISR_PROTO(RECORD_COMPLETE);

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
    SWITCH_BUFFER_ISR_StartEx(SWITCH_BUFFER_ISR);
    RECORD_COMPLETE_StartEx(RECORD_COMPLETE);
    UI_TIMER_Start();
    RECORDING_TIMER_Start();
    
    //Data Storage
    FS_FAT_SupportLFN();
    FS_Init();
    FS_GetVolumeName(0u, &sdVolName[0], 9u);
    
    // Real-Time Clock
    RTC_Init();
    //now.seconds = 0;
    //now.minutes = 56;
    //now.hours = 18;
    //now.date = 57;
    //now.month = 5;
    //now.year = 2020;
    //RTC_SetTimeDate(now);
    
    //Encoder
    ARM_ANGLE_ENCODER_Start();
    
    //Accelerometer
    ADC_DMA_Chan = ADC_DMA_DmaInitialize(ADC_DMA_BYTES_PER_BURST, ADC_DMA_REQUEST_PER_BURST, 
        HI16(ADC_DMA_SRC_BASE), HI16(ADC_DMA_DST_BASE));
    ADC_DMA_TD[0] = CyDmaTdAllocate();
    ADC_DMA_TD[1] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(ADC_DMA_TD[0], 4095, ADC_DMA_TD[1], ADC_DMA__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetConfiguration(ADC_DMA_TD[1], 4095, ADC_DMA_TD[0], ADC_DMA__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(ADC_DMA_TD[0], LO16((uint32)ACC_ADC_SAR_SAR_WRK0_PTR), LO16((uint32)ADC_Buffer_A));
    CyDmaTdSetAddress(ADC_DMA_TD[1], LO16((uint32)ACC_ADC_SAR_SAR_WRK0_PTR), LO16((uint32)ADC_Buffer_B));
    CyDmaChSetInitialTd(ADC_DMA_Chan, ADC_DMA_TD[0]);
    
    DVDAC_Start();
    ACC_ADC_Start();
    ACC_ADC_IRQ_Disable();
    
    
    //Initialize Event Manager    
    eventQueue = EventQueue_New();
    event = NO_EVENT;
    
    // Main Loop
    for(;;)
    {   
        // Collect Sensor Data
        encAnglePrev = encAngle;
        encRaw = ARM_ANGLE_ENCODER_GetCounter();
        encAngle = ((float) encRaw) / ((float) ENCODER_COUNTS_PER_REV) * 360;
        if(encAngle >= LIFT_THRESHOLD_DEG){
            BUZZER_ON;
        } else {
            BUZZER_OFF;
        }
        
        // Check for Sensor Events
        if(encAngle >= LIFT_THRESHOLD_DEG && encAnglePrev < LIFT_THRESHOLD_DEG){
            EventQueue_Clear(eventQueue);
            EventQueue_Enqueue(eventQueue,HAMMER_LIFTED);
            maxAngle = 0;
        }
        // Track Max Lift Angle
        if(encAngle > maxAngle){
            maxAngle = encAngle;
        }
        
        // UI Update
        if(update_ui){
            now = RTC_ReadTimeDate();
            UpdateLCD();
            update_ui = false;
        }
        
        // Load Next Event for Processing
        if(!EventQueue_IsEmpty(eventQueue)){
            event = EventQueue_Dequeue(eventQueue);
        } else {
            event = NO_EVENT;
        }
        
        // State Machine
        switch(ui_state){
            case SPLASH_SCREEN:
                sprintf(LCD_MSG[0],"Shock Test Stand");
                sprintf(LCD_MSG[1]," ");
                LED_Write(RED);
                
                switch(event){
                    case UP_CLICK:
                    case DOWN_CLICK:
                    case SELECT_CLICK:
                        ui_state = LIVE_READOUT;
                        event = NO_EVENT;
                    default:
                        break;
                }
                break;
            
            case LIVE_READOUT:
                sprintf(LCD_MSG[0],"IDLE");
                sprintf(LCD_MSG[1],"  %.1f deg", encAngle);
                LCD_Position(1u, 0u);
                LCD_PutChar(LCD_CUSTOM_0);
                
                LED_Write(GREEN);
                
                switch(event){
                    case UP_CLICK:
                        event = NO_EVENT;
                        break;
                    case DOWN_CLICK:
                        ui_state = TARE_SELECT;
                        event = NO_EVENT;
                        break;
                    case HAMMER_LIFTED:
                        ui_state = ARMED;
                        event = NO_EVENT;
                    default:
                        break;
                }
                break;
            
            case TARE_SELECT:
                sprintf(LCD_MSG[0],">Tare");
                sprintf(LCD_MSG[1]," Eject SD Card");
                LED_Write(YELLOW);
                
                switch(event){
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
                    default:
                        break;
                }
                break;
            
            case TARE:
                sprintf(LCD_MSG[0],"Taring system...");
                sprintf(LCD_MSG[1]," ");
                LED_Write(CYAN);
                
                CyDelay(500);
                ARM_ANGLE_ENCODER_SetCounter(0);
                
                ui_state = LIVE_READOUT;
                event = NO_EVENT;
                break;
            
            case EJECT_SELECT:
                sprintf(LCD_MSG[0]," Tare");
                sprintf(LCD_MSG[1],">Eject SD Card");
                LED_Write(YELLOW);
                
                switch(event){
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
                    default:
                        break;
                }
                break;
            
            case EJECT:
                sprintf(LCD_MSG[0],"Ejecting SD...");
                sprintf(LCD_MSG[1]," ");
                LED_Write(CYAN);
                CyDelay(1000);
                
                
                ui_state = LIVE_READOUT;
                event = NO_EVENT;
                break;
                
            case FORMAT_SELECT:
                sprintf(LCD_MSG[0],">Format SD");
                sprintf(LCD_MSG[1]," Set Time/Date");
                LED_Write(YELLOW);
                
                switch(event){
                    case UP_CLICK:
                        ui_state = EJECT_SELECT;
                        event = NO_EVENT;
                        break;
                    case DOWN_CLICK:
                        ui_state = TIMEDATE_SELECT;
                        event = NO_EVENT;
                        break;
                    case SELECT_CLICK:
                        ui_state = FORMAT_CONFIRM;
                        event = NO_EVENT;
                        break;
                    default:
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
                    case UP_CLICK:
                        ui_state = FORMAT;
                        event = NO_EVENT;
                        break;
                    case DOWN_CLICK:
                        ui_state = LIVE_READOUT;
                        event = NO_EVENT;
                        break;
                    default:
                        break;
                }
                break;
                
            case FORMAT:
                sprintf(LCD_MSG[0],"Formatting...");
                sprintf(LCD_MSG[1]," ");
                LED_Write(CYAN);
                
                DisableButtonISRs();
                FS_FormatSD(sdVolName);
                FS_MkDir("Data");
                
                // Generate Configuration File
                pFile = FS_FOpen("config.txt", "w");
                if(pFile){
                    FS_Write(pFile, "STS V0.1\n", 9u);
                    sprintf(strbuff,"Compiled %s at %s\n",__DATE__,__TIME__);
                    FS_Write(pFile,strbuff,strlen(strbuff));
                    FS_FClose(pFile);
                }
                
                // Create Example Test File
                pFile = FS_FOpen("test.csv", "w");
                if(pFile){
                    // System Header Parameters
                    sprintf(strbuff,"X,Y,Z\n");
                    FS_Write(pFile,strbuff,strlen(strbuff));
                    for(i = 0; i < 128; i++){
                        sprintf(strbuff,"%i,%i,%i\n",(i%3),i,(i%3));
                        FS_Write(pFile,strbuff,strlen(strbuff));
                    }
                    for(i = 128; i > 0; i--){
                        sprintf(strbuff,"%i,%i,%i\n",(i%3),i,(i%3));
                        FS_Write(pFile,strbuff,strlen(strbuff));
                    }
                    for(i = 0; i < 256; i++){
                        sprintf(strbuff,"%i,%i,%i\n",(i%3),(i%3),(i%3));
                        FS_Write(pFile,strbuff,strlen(strbuff));
                    }
                    FS_FClose(pFile);
                }
                EnableButtonISRs();
                ui_state = LIVE_READOUT;
                event = NO_EVENT;
                break;
                
            case TIMEDATE_SELECT:
                sprintf(LCD_MSG[0]," Format SD");
                sprintf(LCD_MSG[1],">Set Time/Date");
                LED_Write(YELLOW);
                
                switch(event){
                    case UP_CLICK:
                        ui_state = FORMAT_SELECT;
                        event = NO_EVENT;
                        break;
                    case DOWN_CLICK:
                        event = NO_EVENT;
                        break;
                    case SELECT_CLICK:
                        ui_state = TIMEDATE_SET;
                        event = NO_EVENT;
                        break;
                    default:
                        break;
                }
                break;
                
            case TIMEDATE_SET:
                sprintf(LCD_MSG[0],"%02u:%02u:%02u",now.hours,now.minutes,now.seconds);
                sprintf(LCD_MSG[1],"%u/%u/%u",now.month,now.date,now.year);
                LED_Write(YELLOW);
                
                switch(event){
                    case UP_CLICK:
                        event = NO_EVENT;
                        break;
                    case DOWN_CLICK:
                        event = NO_EVENT;
                        break;
                    case SELECT_CLICK:
                        ui_state = LIVE_READOUT;
                        event = NO_EVENT;
                        break;
                    default:
                        break;
                }
                break;
            
                
            case ARMED:
                sprintf(LCD_MSG[0],"ARMED");
                sprintf(LCD_MSG[1],"  %.1f deg", encAngle);
                LED_Write(RED);
                
                if((maxAngle - encAngle) > DROP_ANGLE_THRESHOLD_DEG){
                    EventQueue_Clear(eventQueue);
                    EventQueue_Enqueue(eventQueue,HAMMER_DROPPED);
                }
                
                switch(event){
                    case HAMMER_DROPPED:
                        ui_state = DROPPED;
                        event = NO_EVENT;
                        break;
                    default:
                        break;
                }
                break;
                
            case DROPPED:
                sprintf(LCD_MSG[0],"DROPPED");
                sprintf(LCD_MSG[1],"  %.1f deg", encAngle);
                LED_Write(YELLOW);
                
                // Check for Recording Trigger
                if(encAngle < RECORD_ANGLE_THRESHOLD_DEG){
                    sprintf(rawfilename,"\\Data\\STS_D_%u_%u_%u_T_%u_%u_%u",now.month,now.date,now.year,now.hours,now.minutes,now.seconds);
                    
                    FileTime.Year = now.year;
                    FileTime.Month = now.month;
                    FileTime.Day = now.date;
                    FileTime.Hour = now.hours;
                    FileTime.Minute = now.minutes;
                    FileTime.Second = now.seconds;
                    FS_FileTimeToTimeStamp (&FileTime, &TimeStamp);

                    pFile = FS_FOpen(rawfilename, "w");
                    if(pFile){
                        CyDmaChSetInitialTd(ADC_DMA_Chan, ADC_DMA_TD[0]);
                        CyDmaChEnable(ADC_DMA_Chan, 1);
                        ACC_ADC_StartConvert();
                        ui_state = RECORDING;
                        event = NO_EVENT;
                        Timer_Reset_Write(1);
                    }else{
                        ui_state = ERROR_DISPLAY;
                        event = NO_EVENT;
                    }            
                }
                break;
                
            case RECORDING:
                sprintf(LCD_MSG[0],"RECORDING");
                sprintf(LCD_MSG[1]," ");
                LED_Write(YELLOW);
                 
                        
                switch(event){
                    case RECORD_COMPLETED:
                        FS_FClose(pFile);
                        ui_state = PROCESSING;
                        event = NO_EVENT;
                        break;
                    default:
                        break;
                }
                break;
            
            case PROCESSING:
                sprintf(LCD_MSG[0],"PROCESSING");
                
                // Open Test Data
                rawFile = FS_FOpen(rawfilename, "rb");
                if(rawFile == NULL){
                    ui_state = ERROR_DISPLAY;
                    event = NO_EVENT;
                    break;
                }
                sprintf(csvfilename,"%s.csv",rawfilename);
                csvFile = FS_FOpen(csvfilename, "w");
                if(csvFile == NULL){
                    ui_state = ERROR_DISPLAY;
                    event = NO_EVENT;
                    break;
                }
                FS_FSeek(rawFile, 0, SEEK_END);          
                long filelen = FS_FTell(rawFile);   
                FS_FSeek(rawFile, 0, SEEK_SET);
                // Convert Binary to CSV
                FS_Write(csvFile, "X,Y,Z\n", 6u);
                
 
                uint16_t x_raw,y_raw,z_raw;
                char line[80];
                for(i=0;i < filelen; i+=3){
                    FS_FRead(&x_raw,2,1,rawFile);
                    FS_FRead(&y_raw,2,1,rawFile);
                    FS_FRead(&z_raw,2,1,rawFile);
                    sprintf(line,"%u,%u,%u\n",x_raw,y_raw,z_raw);
                    FS_FWrite(line,strlen(line),1,csvFile);
                    if(update_ui){
                        sprintf(LCD_MSG[1],"%.1f%%",(i*100/(float)filelen));
                        UpdateLCD();
                    }
                }
                
                FS_FClose(rawFile);
                FS_FClose(csvFile);
                
                FS_SetFileTimeEx(rawfilename, TimeStamp, FS_FILETIME_CREATE);
                FS_SetFileTimeEx(rawfilename, TimeStamp, FS_FILETIME_MODIFY);
                FS_SetFileTimeEx(csvfilename, TimeStamp, FS_FILETIME_CREATE);
                FS_SetFileTimeEx(csvfilename, TimeStamp, FS_FILETIME_MODIFY);
                ui_state = RESULTS;
                event = NO_EVENT;
                break;
                
                
            case RESULTS:
                sprintf(LCD_MSG[0],"TEST COMPLETE");
                sprintf(LCD_MSG[1],"Press any key...");
                LED_Write(MAGENTA);
                    
                switch(event){
                    case UP_CLICK:
                    case DOWN_CLICK:
                    case SELECT_CLICK:
                        ui_state = LIVE_READOUT;
                        event = NO_EVENT;
                    default:
                        break;
                }
                break;
            
            case ERROR_DISPLAY:
                sprintf(LCD_MSG[0],"Error: ");
                sprintf(LCD_MSG[1],"No SD Card Found");
                LED_Write(RED);
                
                switch(event){
                    case UP_CLICK:
                    case DOWN_CLICK:
                    case SELECT_CLICK:
                        ui_state = LIVE_READOUT;
                        event = NO_EVENT;
                    default:
                        break;
                }
                break;
        }

    }
}

CY_ISR(UPDATE_UI_ISR){
    update_ui = true;
}

CY_ISR(UP_CLICK_ISR){
    EventQueue_Enqueue(eventQueue, UP_CLICK);
}

CY_ISR(DOWN_CLICK_ISR){
    EventQueue_Enqueue(eventQueue, DOWN_CLICK);
}

CY_ISR(SELECT_CLICK_ISR){
    EventQueue_Enqueue(eventQueue, SELECT_CLICK);
}

CY_ISR(SWITCH_BUFFER_ISR){
    switch(currADCBuff){
        case BUFF_A:
            FS_Write(pFile,ADC_Buffer_A,4095);
            currADCBuff = BUFF_B;
        case BUFF_B:
            FS_Write(pFile,ADC_Buffer_B,4095);
            currADCBuff = BUFF_A;
    }
}

CY_ISR(RECORD_COMPLETE){
    EventQueue_Enqueue(eventQueue, RECORD_COMPLETED);
    CyDmaChDisable(ADC_DMA_Chan);
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
