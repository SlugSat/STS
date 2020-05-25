/*******************************************************************************
* File Name: LCD_Char_1.c
* Version 1.30
*
* Description:
*  This file provides source code for the Character LCD component's API.
*
* Note:
*
********************************************************************************
* Copyright (2008), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/

#include "LCD_Char_1.h"


/*******************************************************************************
* Function Name: LCD_Char_1_Start
********************************************************************************
* Summary:
*  This method does the prep work necessary to start the LCD Hardware Module.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void LCD_Char_1_Start()
{
    /* INIT CODE */
    CyDelay(40);                                                         /* Delay 15 ms */
    LCD_Char_1_WrCntrlNib(LCD_Char_1_DISPLAY_8_BIT_INIT);   /* Selects 8-bit mode */
    CyDelay(5);                                                         /* Delay 5 ms */
    LCD_Char_1_WrCntrlNib(LCD_Char_1_DISPLAY_8_BIT_INIT);   /* Selects 8-bit mode */
    CyDelay(15);                                                         /* Delay .15 ms */
    LCD_Char_1_WrCntrlNib(LCD_Char_1_DISPLAY_8_BIT_INIT);   /* Selects 8-bit mode */
    LCD_Char_1_WrCntrlNib(LCD_Char_1_DISPLAY_4_BIT_INIT);   /* Selects 4-bit mode */
    CyDelay(5);                                                         /* Delay 4.5 ms */
    /************************************************************\
    **      Can now write full bytes to LCD in 4-bit mode       **
    \************************************************************/

    LCD_Char_1_WriteControl(LCD_Char_1_CURSOR_AUTO_INCR_ON);    /* Incr Cursor After Writes */
    LCD_Char_1_WriteControl(LCD_Char_1_DISPLAY_CURSOR_ON);      /* Turn Display, Cursor ON */
    LCD_Char_1_WriteControl(LCD_Char_1_DISPLAY_2_LINES_5x10);   /* 2 Lines by 5x10 Characters */
    LCD_Char_1_WriteControl(LCD_Char_1_DISPLAY_CURSOR_OFF);     /* Turn Display, Cursor OFF */
    LCD_Char_1_WriteControl(LCD_Char_1_CLEAR_DISPLAY);          /* Clear LCD Screen */
    LCD_Char_1_WriteControl(LCD_Char_1_DISPLAY_ON_CURSOR_OFF);  /* Turn Display ON, Cursor OFF */
    LCD_Char_1_WriteControl(LCD_Char_1_RESET_CURSOR_POSITION);  /* Set Cursor to 0,0 */
    CyDelay(5);                                                             /* Delay 4.5 ms */
}


/*******************************************************************************
* Function Name: LCD_Char_1_Stop
********************************************************************************
* Summary:
*  Turns off the display of the LCD screen.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void LCD_Char_1_Stop()
{
    /* Calls LCD Off Macro */
    LCD_Char_1_DisplayOff();
}


/*******************************************************************************
*  Function Name: LCD_Char_1_Position
********************************************************************************
* Summary:
*  Moves active cursor location to a point specified by the input arguments
*
* Parameters:
*  row:     Specific row of LCD module to be written
*  column:  Column of LCD module to be written
*
* Return:
*  void
*
* Note:
*  This only applies for LCD displays which use the 2X40 address mode.
*  This results in Row 2 offset from row one by 0x28.
*  When there are more than 2 rows, each row must be fewer than 20 characters.
*
*******************************************************************************/
void LCD_Char_1_Position(uint8 row, uint8 column)
{
    switch (row)
    {
        case 0:
            LCD_Char_1_WriteControl(LCD_Char_1_ROW_0_START + column);
            break;
        case 1:
            LCD_Char_1_WriteControl(LCD_Char_1_ROW_1_START + column);
            break;
        case 2:
            LCD_Char_1_WriteControl(LCD_Char_1_ROW_2_START + column);
            break;
        case 3:
            LCD_Char_1_WriteControl(LCD_Char_1_ROW_3_START + column);
            break;
        default:
            /* if default case is hit, invalid row argument was passed.*/
            break;
    }
}


/*******************************************************************************
* Function Name: LCD_Char_1_PrintString
********************************************************************************
* Summary:
*  Writes a zero terminated string to the LCD.
*
* Parameters:
*  string:  pointer to head of char8 array to be written to the LCD module
*
* Return:
*  void
*
*******************************************************************************/
void LCD_Char_1_PrintString(char8 * string)
{
    uint8 index_u8 = 1;
    char8 current = *string;
    /* Until null is reached, print next character */
    while(current != (char8)'\0')
    {
        LCD_Char_1_WriteData(current);
        current = *(string+index_u8);
        index_u8++;
    }
}


/*******************************************************************************
*  Function Name: LCD_Char_1_PutChar
********************************************************************************
* Summary:
*  Writes a single character to the current cursor position of the LCD module.
*  Custom character names (_CUSTOM_0 through
*  _CUSTOM_7) are acceptable as inputs.
*
* Parameters:
*  character:   character to be written to the LCD
*
* Return:
*  void
*
*******************************************************************************/
void LCD_Char_1_PutChar(char8 character)
{
    LCD_Char_1_WriteData(character);
}


/*******************************************************************************
*  Function Name: LCD_Char_1_WriteData
********************************************************************************
* Summary:
*  Writes a data byte to the LCD module's Data Display RAM.
*
* Parameters:
*  dByte:   byte to be written to LCD module.
*
* Return:
*  void
*
*******************************************************************************/
void LCD_Char_1_WriteData(uint8 dByte)
{
    uint8 nibble;

    LCD_Char_1_IsReady();
    nibble = dByte >> LCD_Char_1_NIBBLE_SHIFT;
    nibble &= LCD_Char_1_NIBBLE_MASK;
    /* Write high nibble */
    LCD_Char_1_WrDatNib(nibble);

    nibble = dByte & LCD_Char_1_NIBBLE_MASK;
    /* Write low nibble */
    LCD_Char_1_WrDatNib(nibble);
}


/*******************************************************************************
*  Function Name: LCD_Char_1_WriteControl
********************************************************************************
* Summary:
*  Writes a command byte to the LCD module.
*
* Parameters:
*  cByte:   byte to be written to LCD module.
*
* Return:
*  void
*
*******************************************************************************/
void LCD_Char_1_WriteControl(uint8 cByte)
{
    uint8 nibble = cByte >> LCD_Char_1_NIBBLE_SHIFT;
    LCD_Char_1_IsReady();
    nibble &= LCD_Char_1_NIBBLE_MASK;
    /* WrCntrlNib(High Nibble) */
    LCD_Char_1_WrCntrlNib(nibble);

    nibble = cByte & LCD_Char_1_NIBBLE_MASK;
    /* WrCntrlNib(Low Nibble) */
    LCD_Char_1_WrCntrlNib(nibble);
}


/*******************************************************************************
* Function Name: LCD_Char_1_IsReady
********************************************************************************
* Summary:
*  Polls LCD until the ready bit is set.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Note:
*  Changes pins to High-Z.
*
*******************************************************************************/
void LCD_Char_1_IsReady()
{
    /* Change Port to High-Z Status on data pins */
    uint8 value = 0;
    uint8 readyValue = 0;

    /* Clear the LCD port*/
    LCD_Char_1_PORT_DR &= ~LCD_Char_1_PORT_MASK ;

    /* Mask off data pins to clear old values out */
    value = LCD_Char_1_PORT_DM0 & ~LCD_Char_1_DATA_MASK;
    /* Load in high Z values for data pins, others unchanged */
    LCD_Char_1_PORT_DM0 = value | (LCD_Char_1_HIGH_Z_DM0 & LCD_Char_1_DATA_MASK);

    /* Mask off data pins to clear old values out */
    value = LCD_Char_1_PORT_DM1 & ~LCD_Char_1_DATA_MASK;
    /* Load in high Z values for data pins, others unchanged */
    LCD_Char_1_PORT_DM1 = value | (LCD_Char_1_HIGH_Z_DM1 & LCD_Char_1_DATA_MASK);

    /* Mask off data pins to clear old values out */
    value = LCD_Char_1_PORT_DM2 & ~LCD_Char_1_DATA_MASK;
    /* Load in high Z values for data pins, others unchanged */
    LCD_Char_1_PORT_DM2 = value | (LCD_Char_1_HIGH_Z_DM2 & LCD_Char_1_DATA_MASK);

    /* Set R/W high to read */
    LCD_Char_1_PORT_DR |= LCD_Char_1_RW;

    do
    {
        /* Set E high */
        LCD_Char_1_PORT_DR |= LCD_Char_1_E;
        /* Delay the setup time for data pins */
        value ++;
        value --;
        value ++;
        value --;

        readyValue = LCD_Char_1_PORT_PS;

        LCD_Char_1_PORT_DR &= ~LCD_Char_1_E;

        value ++;
        value --;
        value ++;
        value --;

        /* Set E high */
        LCD_Char_1_PORT_DR |= LCD_Char_1_E;
        /* Delay the setup time for data pins */
        value ++;
        value --;
        value ++;
        value --;

        LCD_Char_1_PORT_DR &= ~LCD_Char_1_E;
        /* Repeat until bit 4 is zero. */
        readyValue &= LCD_Char_1_READY_BIT;
    } while (readyValue != 0);

    /* Set R/W low to write, could be next to do while loop, delay needed then */
    LCD_Char_1_PORT_DR &= ~LCD_Char_1_RW;

    /* Change Port to Output (Strong) on data pins */
    /* Mask off data pins to clear high z values out */
    value = LCD_Char_1_PORT_DM0 & (~LCD_Char_1_DATA_MASK);
    /* Load in high Z values for data pins, others unchanged */
    LCD_Char_1_PORT_DM0 = value | (LCD_Char_1_STRONG_DM0 & LCD_Char_1_DATA_MASK);

    /* Mask off data pins to clear high z values out */
    value = LCD_Char_1_PORT_DM1 & (~LCD_Char_1_DATA_MASK);
    /* Load in high Z values for data pins, others unchanged */
    LCD_Char_1_PORT_DM1 = value | (LCD_Char_1_STRONG_DM1 & LCD_Char_1_DATA_MASK);

    /* Mask off data pins to clear high z values out */
    value = LCD_Char_1_PORT_DM2 & (~LCD_Char_1_DATA_MASK);
    /* Load in high Z values for data pins, others unchanged */
    LCD_Char_1_PORT_DM2 = value | (LCD_Char_1_STRONG_DM2 & LCD_Char_1_DATA_MASK);
}


/* Non API Functions */

/*******************************************************************************
*  Function Name: LCD_Char_1_WrDatNib
********************************************************************************
* Summary:
*  Writes a data nibble to the LCD module.
*
* Parameters:
*  nibble:  byte containing nibble in least significant nibble to be written
*           to LCD module.
*
* Return:
*  void
*
*******************************************************************************/
void LCD_Char_1_WrDatNib(uint8 nibble)
{
    uint8 dataNibble = (nibble & LCD_Char_1_NIBBLE_MASK) << LCD_Char_1_PORT_SHIFT;

    /* RS High (DATA) 140ns delay ahead of raising E */
    LCD_Char_1_IsReady();
    LCD_Char_1_PORT_DR |= LCD_Char_1_RS;
    LCD_Char_1_PORT_DR &= ~(LCD_Char_1_E | LCD_Char_1_DATA_MASK);
    /* Assign Data To Port (Watch out for extra Pin Value) and bring E High */
    LCD_Char_1_PORT_DR |= (LCD_Char_1_E | dataNibble);/* Write in data, bring E high*/
    /* Minimum of 450 ns delay (30 Instructions at 66 MHz), Bring E low */
    LCD_Char_1_IsReady();
    LCD_Char_1_PORT_DR &= ~LCD_Char_1_E;
}


/*******************************************************************************
*  Function Name: LCD_Char_1_WrCntrlNib
********************************************************************************
* Summary:
*  Writes a control nibble to the LCD module.
*
* Parameters:
*  nibble:  byte containing nibble in least significant nibble to be written
*           to LCD module.
*
* Return:
*  void
*
*******************************************************************************/
void LCD_Char_1_WrCntrlNib(uint8 nibble)
{
    uint8 dataNibble = (nibble & LCD_Char_1_NIBBLE_MASK) << LCD_Char_1_PORT_SHIFT;

    /* E should already be low, clear data and bring RS low */
    LCD_Char_1_PORT_DR &= ~(LCD_Char_1_E | LCD_Char_1_RS | LCD_Char_1_DATA_MASK);
    LCD_Char_1_PORT_DR |= (LCD_Char_1_E | dataNibble);
    LCD_Char_1_PORT_DR &= ~LCD_Char_1_E;
}



/*******************************************************************************
*  Function Name: LCD_Char_1_PrintHexUint8
********************************************************************************
* Summary:
*  Print a byte as two ASCII characters
*
* Parameters:  
*  value:   The byte to be printed out as ASCII characters.
*
* Return:
*  void
*
*******************************************************************************/
void LCD_Char_1_PrintHexUint8(uint8 value)
{
    static char8 const hex[16] = "0123456789ABCDEF";
    
    LCD_Char_1_PutChar((char8)hex[value>>4]);
    LCD_Char_1_PutChar((char8)hex[value&0x0F]);
}


/*******************************************************************************
*  Function Name: LCD_Char_1_PrintHexUint16
********************************************************************************
* Summary:
*  Print a uint16 as four ASCII characters.
*
* Parameters:  
*  value:   The uint16 to be printed out as ASCII characters.
*
* Return:
*  void
*
*******************************************************************************/
void LCD_Char_1_PrintHexUint16(uint16 value)
{
    LCD_Char_1_PrintHexUint8(value >> 8);
    LCD_Char_1_PrintHexUint8(value & 0xFF);
}


/*******************************************************************************
*  Function Name: LCD_Char_1_PrintDecUint16
********************************************************************************
* Summary:
*  Print an uint32 value as a left-justified decimal value.
*
* Parameters:  
*  value:   The byte to be printed out as ASCII characters.
*
* Return:
*  void
*
*******************************************************************************/
void LCD_Char_1_PrintDecUint16(uint16 value)
{
    #define LCD_Char_1_NUMBER_OF_REMAINDERS 5
    #define LCD_Char_1_TEN 10

    char8 number[LCD_Char_1_NUMBER_OF_REMAINDERS];
    char8 temp[LCD_Char_1_NUMBER_OF_REMAINDERS]; 

    uint8 index = 0;
    uint8 numDigits = 0;

    
    /* Load these in reverse order */ 
    while(value >= LCD_Char_1_TEN)
    {
        temp[index]= (value % LCD_Char_1_TEN) + '0';
        value /= LCD_Char_1_TEN;
        index++;
    }
    
    temp[index] = (value % LCD_Char_1_TEN) + '0';
    numDigits = index;

    /* While index is greater than or equal to zero */
    while (index != 0xFFu)
    {
        number[numDigits - index] = temp[index];
        index--;
    }
    
    /* Null Termination */
    number[numDigits + 1] = (char8) 0;

    /* Print out number */
    LCD_Char_1_PrintString(number);
}



/* [] END OF FILE */
