/*******************************************************************************
* File Name: ISR_Switch.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ISR_ISR_Switch_H)
#define CY_ISR_ISR_Switch_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ISR_Switch_Start(void) ;
void ISR_Switch_StartEx(cyisraddress address) ;
void ISR_Switch_Stop(void) ;

CY_ISR_PROTO(ISR_Switch_Interrupt);

void ISR_Switch_SetVector(cyisraddress address) ;
cyisraddress ISR_Switch_GetVector(void) ;

void ISR_Switch_SetPriority(uint8 priority) ;
uint8 ISR_Switch_GetPriority(void) ;

void ISR_Switch_Enable(void) ;
uint8 ISR_Switch_GetState(void) ;
void ISR_Switch_Disable(void) ;

void ISR_Switch_SetPending(void) ;
void ISR_Switch_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ISR_Switch ISR. */
#define ISR_Switch_INTC_VECTOR            ((reg16 *) ISR_Switch__INTC_VECT)

/* Address of the ISR_Switch ISR priority. */
#define ISR_Switch_INTC_PRIOR             ((reg8 *) ISR_Switch__INTC_PRIOR_REG)

/* Priority of the ISR_Switch interrupt. */
#define ISR_Switch_INTC_PRIOR_NUMBER      ISR_Switch__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ISR_Switch interrupt. */
#define ISR_Switch_INTC_SET_EN            ((reg8 *) ISR_Switch__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ISR_Switch interrupt. */
#define ISR_Switch_INTC_CLR_EN            ((reg8 *) ISR_Switch__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ISR_Switch interrupt state to pending. */
#define ISR_Switch_INTC_SET_PD            ((reg8 *) ISR_Switch__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ISR_Switch interrupt. */
#define ISR_Switch_INTC_CLR_PD            ((reg8 *) ISR_Switch__INTC_CLR_PD_REG)



#endif /* CY_ISR_ISR_Switch_H */


/* [] END OF FILE */
