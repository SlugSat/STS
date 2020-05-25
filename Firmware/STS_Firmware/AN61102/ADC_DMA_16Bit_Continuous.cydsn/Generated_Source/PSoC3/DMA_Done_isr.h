/*******************************************************************************
* File Name: DMA_Done_isr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ISR_DMA_Done_isr_H)
#define CY_ISR_DMA_Done_isr_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void DMA_Done_isr_Start(void) ;
void DMA_Done_isr_StartEx(cyisraddress address) ;
void DMA_Done_isr_Stop(void) ;

CY_ISR_PROTO(DMA_Done_isr_Interrupt);

void DMA_Done_isr_SetVector(cyisraddress address) ;
cyisraddress DMA_Done_isr_GetVector(void) ;

void DMA_Done_isr_SetPriority(uint8 priority) ;
uint8 DMA_Done_isr_GetPriority(void) ;

void DMA_Done_isr_Enable(void) ;
uint8 DMA_Done_isr_GetState(void) ;
void DMA_Done_isr_Disable(void) ;

void DMA_Done_isr_SetPending(void) ;
void DMA_Done_isr_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the DMA_Done_isr ISR. */
#define DMA_Done_isr_INTC_VECTOR            ((reg16 *) DMA_Done_isr__INTC_VECT)

/* Address of the DMA_Done_isr ISR priority. */
#define DMA_Done_isr_INTC_PRIOR             ((reg8 *) DMA_Done_isr__INTC_PRIOR_REG)

/* Priority of the DMA_Done_isr interrupt. */
#define DMA_Done_isr_INTC_PRIOR_NUMBER      DMA_Done_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable DMA_Done_isr interrupt. */
#define DMA_Done_isr_INTC_SET_EN            ((reg8 *) DMA_Done_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the DMA_Done_isr interrupt. */
#define DMA_Done_isr_INTC_CLR_EN            ((reg8 *) DMA_Done_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the DMA_Done_isr interrupt state to pending. */
#define DMA_Done_isr_INTC_SET_PD            ((reg8 *) DMA_Done_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the DMA_Done_isr interrupt. */
#define DMA_Done_isr_INTC_CLR_PD            ((reg8 *) DMA_Done_isr__INTC_CLR_PD_REG)



#endif /* CY_ISR_DMA_Done_isr_H */


/* [] END OF FILE */
