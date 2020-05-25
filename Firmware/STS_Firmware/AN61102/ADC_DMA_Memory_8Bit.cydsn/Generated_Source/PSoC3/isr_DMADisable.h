/*******************************************************************************
* File Name: isr_DMADisable_intc.h
* Version 1.20
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#if !defined(__isr_DMADisable_INTC_H__)
#define __isr_DMADisable_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

#if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)     
    #if(CYDEV_CHIP_REV_EXPECT <= CYDEV_CHIP_REV_LEOPARD_ES2)      
        #include <intrins.h>
        #define isr_DMADisable_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    #endif
#endif


/* Interrupt Controller API. */
void isr_DMADisable_Start(void);
void isr_DMADisable_Stop(void);

CY_ISR_PROTO(isr_DMADisable_Interrupt);

void isr_DMADisable_SetVector(cyisraddress address);
cyisraddress isr_DMADisable_GetVector(void);

void isr_DMADisable_SetPriority(uint8 priority);
uint8 isr_DMADisable_GetPriority(void);

void isr_DMADisable_Enable(void);
uint8 isr_DMADisable_GetState(void);
void isr_DMADisable_Disable(void);

void isr_DMADisable_SetPending(void);
void isr_DMADisable_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_DMADisable ISR. */
#define isr_DMADisable_INTC_VECTOR            ((reg16 *) isr_DMADisable__INTC_VECT)

/* Address of the isr_DMADisable ISR priority. */
#define isr_DMADisable_INTC_PRIOR             ((reg8 *) isr_DMADisable__INTC_PRIOR_REG)

/* Priority of the isr_DMADisable interrupt. */
#define isr_DMADisable_INTC_PRIOR_NUMBER      isr_DMADisable__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_DMADisable interrupt. */
#define isr_DMADisable_INTC_SET_EN            ((reg8 *) isr_DMADisable__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_DMADisable interrupt. */
#define isr_DMADisable_INTC_CLR_EN            ((reg8 *) isr_DMADisable__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_DMADisable interrupt state to pending. */
#define isr_DMADisable_INTC_SET_PD            ((reg8 *) isr_DMADisable__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_DMADisable interrupt. */
#define isr_DMADisable_INTC_CLR_PD            ((reg8 *) isr_DMADisable__INTC_CLR_PD_REG)

/* __isr_DMADisable_INTC_H__ */
#endif

