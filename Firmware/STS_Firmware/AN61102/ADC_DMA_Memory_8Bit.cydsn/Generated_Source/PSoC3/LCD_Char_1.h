/*******************************************************************************
* File Name: LCD_Char_1.h
* Version 1.30
*
* Description:
*  This header file contains registers and constants associated with the
*  Character LCD component.
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

#if !defined(CY_CHARLCD_LCD_Char_1_H)
#define CY_CHARLCD_LCD_Char_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "device.h"

/***************************************
*        Function Prototypes
***************************************/

void LCD_Char_1_Start(void);
void LCD_Char_1_Stop(void);
void LCD_Char_1_WriteControl(uint8 cByte);
void LCD_Char_1_WriteData(uint8 dByte);
void LCD_Char_1_PrintString(char8 *);
void LCD_Char_1_Position(uint8 row, uint8 column);
void LCD_Char_1_PutChar(char8 character);
void LCD_Char_1_IsReady(void);
void LCD_Char_1_WrDatNib(uint8 nibble);
void LCD_Char_1_WrCntrlNib(uint8 nibble);

/* ASCII Conversion Routines */                        
void LCD_Char_1_PrintHexUint8(uint8 value);      
void LCD_Char_1_PrintHexUint16(uint16 value);    
void LCD_Char_1_PrintDecUint16(uint16 value);   
#define LCD_Char_1_PrintNumber(x)   LCD_Char_1_PrintDecUint16(x)
#define LCD_Char_1_PrintInt8(x)     LCD_Char_1_PrintHexUint8(x)
#define LCD_Char_1_PrintInt16(x)    LCD_Char_1_PrintHexUint16(x)

/* Clear Macro */
#define LCD_Char_1_ClearDisplay() LCD_Char_1_WriteControl(LCD_Char_1_CLEAR_DISPLAY)

/* Off Macro */
#define LCD_Char_1_DisplayOff() LCD_Char_1_WriteControl(LCD_Char_1_DISPLAY_CURSOR_OFF)

/* On Macro */
#define LCD_Char_1_DisplayOn() LCD_Char_1_WriteControl(LCD_Char_1_DISPLAY_ON_CURSOR_OFF)


/***************************************
*           API Constants
***************************************/

/* Full Byte Commands Sent as Two Nibbles */
#define LCD_Char_1_DISPLAY_8_BIT_INIT      0x03u
#define LCD_Char_1_DISPLAY_4_BIT_INIT      0x02u
#define LCD_Char_1_DISPLAY_CURSOR_OFF      0x08u
#define LCD_Char_1_CLEAR_DISPLAY           0x01u
#define LCD_Char_1_CURSOR_AUTO_INCR_ON     0x06u
#define LCD_Char_1_DISPLAY_CURSOR_ON       0x0Eu
#define LCD_Char_1_DISPLAY_2_LINES_5x10    0x2Cu
#define LCD_Char_1_DISPLAY_ON_CURSOR_OFF   0x0Cu

#define LCD_Char_1_RESET_CURSOR_POSITION   0x03u
#define LCD_Char_1_CURSOR_WINK             0x0Du
#define LCD_Char_1_CURSOR_BLINK            0x0Fu
#define LCD_Char_1_CURSOR_SH_LEFT          0x10u
#define LCD_Char_1_CURSOR_SH_RIGHT         0x14u
#define LCD_Char_1_CURSOR_HOME             0x02u
#define LCD_Char_1_CURSOR_LEFT             0x04u
#define LCD_Char_1_CURSOR_RIGHT            0x06u
/* Point to Character Generator Ram 0 */
#define LCD_Char_1_CGRAM_0                 0x40u
/* Point to Display Data Ram 0 */
#define LCD_Char_1_DDRAM_0                 0x80u

/* LCD Characteristics */
#define LCD_Char_1_CHARACTER_WIDTH         0x05u
#define LCD_Char_1_CHARACTER_HEIGHT        0x08u

/* Nibble Offset and Mask */
#define LCD_Char_1_NIBBLE_SHIFT            0x04u
#define LCD_Char_1_NIBBLE_MASK             0x0Fu

/* LCD Module Address Constants */
#define LCD_Char_1_ROW_0_START             0x80u
#define LCD_Char_1_ROW_1_START             0xC0u
#define LCD_Char_1_ROW_2_START             0x94u
#define LCD_Char_1_ROW_3_START             0xD4u

/* Bargraph and Custom Character Constants */
#define LCD_Char_1_NONE                    0x00u   /* No Custom Fonts      */
#define LCD_Char_1_HBG                     0x01u   /* Horizontal Bar Graph */
#define LCD_Char_1_VBG                     0x02u   /* Vertical Bar Graph   */
#define LCD_Char_1_UD                      0x03u   /* User Defined Fonts   */




/***************************************
*             Registers
***************************************/

/* Port Register Definitions */
#define LCD_Char_1_PORT_DR        (*(reg8 *) LCD_Char_1_LCDPort__DR)   /* Data Output Register */
#define LCD_Char_1_PORT_PS        (*(reg8 *) LCD_Char_1_LCDPort__PS)   /* Pin State Register */
#define LCD_Char_1_PORT_DM0       (*(reg8 *) LCD_Char_1_LCDPort__DM0)  /* Port Drive Mode 0 */
#define LCD_Char_1_PORT_DM1       (*(reg8 *) LCD_Char_1_LCDPort__DM1)  /* Port Drive Mode 1 */
#define LCD_Char_1_PORT_DM2       (*(reg8 *) LCD_Char_1_LCDPort__DM2)  /* Port Drive Mode 2 */


/***************************************
*       Register Constants
***************************************/

/* SHIFT must be 1 or 0 */
#define LCD_Char_1_PORT_SHIFT             LCD_Char_1_LCDPort__SHIFT
#define LCD_Char_1_PORT_MASK              LCD_Char_1_LCDPort__MASK

/**Drive Mode register values for High Z */
#define LCD_Char_1_HIGH_Z_DM0             0xFFu
#define LCD_Char_1_HIGH_Z_DM1             0x00u
#define LCD_Char_1_HIGH_Z_DM2             0x00u

/* Drive Mode register values for Strong */
#define LCD_Char_1_STRONG_DM0             0x00u
#define LCD_Char_1_STRONG_DM1             0xFFu
#define LCD_Char_1_STRONG_DM2             0xFFu

/* Pin Masks */
#define LCD_Char_1_RS                     (0x20u << LCD_Char_1_LCDPort__SHIFT)
#define LCD_Char_1_RW                     (0x40u << LCD_Char_1_LCDPort__SHIFT)
#define LCD_Char_1_E                      (0x10u << LCD_Char_1_LCDPort__SHIFT)
#define LCD_Char_1_READY_BIT              (0x08u << LCD_Char_1_LCDPort__SHIFT)
#define LCD_Char_1_DATA_MASK              (0x0Fu << LCD_Char_1_LCDPort__SHIFT)

#endif /* CY_CHARLCD_LCD_Char_1_H */


/* [] END OF FILE */
