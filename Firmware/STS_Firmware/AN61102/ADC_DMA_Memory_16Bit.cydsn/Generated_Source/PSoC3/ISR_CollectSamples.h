/*******************************************************************************
* File Name: ISR_CollectSamples_intc.h
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
#if !defined(__ISR_CollectSamples_INTC_H__)
#define __ISR_CollectSamples_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

#if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)     
    #if(CYDEV_CHIP_REV_EXPECT <= CYDEV_CHIP_REV_LEOPARD_ES2)      
        #include <intrins.h>
        #define ISR_CollectSamples_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    #endif
#endif


/* Interrupt Controller API. */
void ISR_CollectSamples_Start(void);
void ISR_CollectSamples_Stop(void);

CY_ISR_PROTO(ISR_CollectSamples_Interrupt);

void ISR_CollectSamples_SetVector(cyisraddress address);
cyisraddress ISR_CollectSamples_GetVector(void);

void ISR_CollectSamples_SetPriority(uint8 priority);
uint8 ISR_CollectSamples_GetPriority(void);

void ISR_CollectSamples_Enable(void);
uint8 ISR_CollectSamples_GetState(void);
void ISR_CollectSamples_Disable(void);

void ISR_CollectSamples_SetPending(void);
void ISR_CollectSamples_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ISR_CollectSamples ISR. */
#define ISR_CollectSamples_INTC_VECTOR            ((reg16 *) ISR_CollectSamples__INTC_VECT)

/* Address of the ISR_CollectSamples ISR priority. */
#define ISR_CollectSamples_INTC_PRIOR             ((reg8 *) ISR_CollectSamples__INTC_PRIOR_REG)

/* Priority of the ISR_CollectSamples interrupt. */
#define ISR_CollectSamples_INTC_PRIOR_NUMBER      ISR_CollectSamples__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ISR_CollectSamples interrupt. */
#define ISR_CollectSamples_INTC_SET_EN            ((reg8 *) ISR_CollectSamples__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ISR_CollectSamples interrupt. */
#define ISR_CollectSamples_INTC_CLR_EN            ((reg8 *) ISR_CollectSamples__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ISR_CollectSamples interrupt state to pending. */
#define ISR_CollectSamples_INTC_SET_PD            ((reg8 *) ISR_CollectSamples__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ISR_CollectSamples interrupt. */
#define ISR_CollectSamples_INTC_CLR_PD            ((reg8 *) ISR_CollectSamples__INTC_CLR_PD_REG)

/* __ISR_CollectSamples_INTC_H__ */
#endif

