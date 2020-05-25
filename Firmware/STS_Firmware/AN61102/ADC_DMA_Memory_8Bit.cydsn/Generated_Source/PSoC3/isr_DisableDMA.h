/*******************************************************************************
* File Name: isr_DisableDMA_intc.h
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
#if !defined(__isr_DisableDMA_INTC_H__)
#define __isr_DisableDMA_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

#if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)     
    #if(CYDEV_CHIP_REV_EXPECT <= CYDEV_CHIP_REV_LEOPARD_ES2)      
        #include <intrins.h>
        #define isr_DisableDMA_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    #endif
#endif


/* Interrupt Controller API. */
void isr_DisableDMA_Start(void);
void isr_DisableDMA_Stop(void);

CY_ISR_PROTO(isr_DisableDMA_Interrupt);

void isr_DisableDMA_SetVector(cyisraddress address);
cyisraddress isr_DisableDMA_GetVector(void);

void isr_DisableDMA_SetPriority(uint8 priority);
uint8 isr_DisableDMA_GetPriority(void);

void isr_DisableDMA_Enable(void);
uint8 isr_DisableDMA_GetState(void);
void isr_DisableDMA_Disable(void);

void isr_DisableDMA_SetPending(void);
void isr_DisableDMA_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_DisableDMA ISR. */
#define isr_DisableDMA_INTC_VECTOR            ((reg16 *) isr_DisableDMA__INTC_VECT)

/* Address of the isr_DisableDMA ISR priority. */
#define isr_DisableDMA_INTC_PRIOR             ((reg8 *) isr_DisableDMA__INTC_PRIOR_REG)

/* Priority of the isr_DisableDMA interrupt. */
#define isr_DisableDMA_INTC_PRIOR_NUMBER      isr_DisableDMA__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_DisableDMA interrupt. */
#define isr_DisableDMA_INTC_SET_EN            ((reg8 *) isr_DisableDMA__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_DisableDMA interrupt. */
#define isr_DisableDMA_INTC_CLR_EN            ((reg8 *) isr_DisableDMA__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_DisableDMA interrupt state to pending. */
#define isr_DisableDMA_INTC_SET_PD            ((reg8 *) isr_DisableDMA__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_DisableDMA interrupt. */
#define isr_DisableDMA_INTC_CLR_PD            ((reg8 *) isr_DisableDMA__INTC_CLR_PD_REG)

/* __isr_DisableDMA_INTC_H__ */
#endif

