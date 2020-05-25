/*******************************************************************************
* File Name: Pin_CollectSamples.h  
* Version 1.20
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_Pin_CollectSamples_H) /* Pins Pin_CollectSamples_H */
#define CY_PINS_Pin_CollectSamples_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_CollectSamples_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_CollectSamples_Write(uint8 value);
void    Pin_CollectSamples_SetDriveMode(uint8 mode);
uint8   Pin_CollectSamples_ReadDataReg(void);
uint8   Pin_CollectSamples_Read(void);
uint8   Pin_CollectSamples_ClearInterrupt(void);

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_CollectSamples_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin_CollectSamples_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin_CollectSamples_DM_RES_UP          PIN_DM_RES_UP
#define Pin_CollectSamples_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin_CollectSamples_DM_OD_LO           PIN_DM_OD_LO
#define Pin_CollectSamples_DM_OD_HI           PIN_DM_OD_HI
#define Pin_CollectSamples_DM_STRONG          PIN_DM_STRONG
#define Pin_CollectSamples_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin_CollectSamples_MASK               Pin_CollectSamples__MASK
#define Pin_CollectSamples_SHIFT              Pin_CollectSamples__SHIFT
#define Pin_CollectSamples_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_CollectSamples_PS                     (* (reg8 *) Pin_CollectSamples__PS)
/* Data Register */
#define Pin_CollectSamples_DR                     (* (reg8 *) Pin_CollectSamples__DR)
/* Port Number */
#define Pin_CollectSamples_PRT_NUM                (* (reg8 *) Pin_CollectSamples__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_CollectSamples_AG                     (* (reg8 *) Pin_CollectSamples__AG)                       
/* Analog MUX bux enable */
#define Pin_CollectSamples_AMUX                   (* (reg8 *) Pin_CollectSamples__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_CollectSamples_BIE                    (* (reg8 *) Pin_CollectSamples__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_CollectSamples_BIT_MASK               (* (reg8 *) Pin_CollectSamples__BIT_MASK)
/* Bypass Enable */
#define Pin_CollectSamples_BYP                    (* (reg8 *) Pin_CollectSamples__BYP)
/* Port wide control signals */                                                   
#define Pin_CollectSamples_CTL                    (* (reg8 *) Pin_CollectSamples__CTL)
/* Drive Modes */
#define Pin_CollectSamples_DM0                    (* (reg8 *) Pin_CollectSamples__DM0) 
#define Pin_CollectSamples_DM1                    (* (reg8 *) Pin_CollectSamples__DM1)
#define Pin_CollectSamples_DM2                    (* (reg8 *) Pin_CollectSamples__DM2) 
/* Input Buffer Disable Override */
#define Pin_CollectSamples_INP_DIS                (* (reg8 *) Pin_CollectSamples__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_CollectSamples_LCD_COM_SEG            (* (reg8 *) Pin_CollectSamples__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_CollectSamples_LCD_EN                 (* (reg8 *) Pin_CollectSamples__LCD_EN)
/* Slew Rate Control */
#define Pin_CollectSamples_SLW                    (* (reg8 *) Pin_CollectSamples__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_CollectSamples_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_CollectSamples__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_CollectSamples_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_CollectSamples__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_CollectSamples_PRTDSI__OE_SEL0        (* (reg8 *) Pin_CollectSamples__PRTDSI__OE_SEL0) 
#define Pin_CollectSamples_PRTDSI__OE_SEL1        (* (reg8 *) Pin_CollectSamples__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_CollectSamples_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_CollectSamples__PRTDSI__OUT_SEL0) 
#define Pin_CollectSamples_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_CollectSamples__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_CollectSamples_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_CollectSamples__PRTDSI__SYNC_OUT) 


#if defined(Pin_CollectSamples__INTSTAT)  /* Interrupt Registers */

    #define Pin_CollectSamples_INTSTAT                (* (reg8 *) Pin_CollectSamples__INTSTAT)
    #define Pin_CollectSamples_SNAP                   (* (reg8 *) Pin_CollectSamples__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_CollectSamples_H */


/* [] END OF FILE */
