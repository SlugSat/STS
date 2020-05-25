/*******************************************************************************
* File Name: isr_DisableDMA_intc.c  
* Version 1.20
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include <CYDEVICE.H>
#include <isr_DisableDMA.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START isr_DisableDMA_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: isr_DisableDMA_Start
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void isr_DisableDMA_Start(void)
{
    /* For all we know the interrupt is active. */
    isr_DisableDMA_Disable();

    /* Set the ISR to point to the isr_DisableDMA Interrupt. */
    isr_DisableDMA_SetVector(isr_DisableDMA_Interrupt);

    /* Set the priority. */
    isr_DisableDMA_SetPriority(isr_DisableDMA_INTC_PRIOR_NUMBER);

    /* Enable it. */
    isr_DisableDMA_Enable();
}

/*******************************************************************************
* Function Name: isr_DisableDMA_Stop
********************************************************************************
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
void isr_DisableDMA_Stop(void)
{
    /* Disable this interrupt. */
    isr_DisableDMA_Disable();

    /* Set the ISR to point to the passive one. */
//    isr_DisableDMA_SetVector(CyDefaultInterrupt);
}

/*******************************************************************************
* Function Name: isr_DisableDMA_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for isr_DisableDMA.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
*
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(isr_DisableDMA_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START isr_DisableDMA_Interrupt` */
	extern uint8 DMADone_flag;

	/*Set the flag to disable the DMA channel*/
	DMADone_flag = 1;
    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
        #if((CYDEV_CHIP_REV_EXPECT <= CYDEV_CHIP_REV_LEOPARD_ES2) && (isr_DisableDMA__ES2_PATCH ))      
            isr_DisableDMA_ISR_PATCH();
        #endif
    #endif
}


/*******************************************************************************
* Function Name: isr_DisableDMA_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt.
*
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_DisableDMA_SetVector(cyisraddress address)
{
    CY_SET_REG16(isr_DisableDMA_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: isr_DisableDMA_GetVector
********************************************************************************
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*
*******************************************************************************/
cyisraddress isr_DisableDMA_GetVector(void)
{
    return (cyisraddress) CY_GET_REG16(isr_DisableDMA_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: isr_DisableDMA_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt.
*
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_DisableDMA_SetPriority(uint8 priority)
{
    *isr_DisableDMA_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: isr_DisableDMA_GetPriority
********************************************************************************
* Summary:
*   Gets the Priority of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
*******************************************************************************/
uint8 isr_DisableDMA_GetPriority(void)
{
    uint8 priority;


    priority = *isr_DisableDMA_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: isr_DisableDMA_Enable
********************************************************************************
* Summary:
*   Enables the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_DisableDMA_Enable(void)
{
    /* Enable the general interrupt. */
    *isr_DisableDMA_INTC_SET_EN = isr_DisableDMA__INTC_MASK;
}

/*******************************************************************************
* Function Name: isr_DisableDMA_GetState
********************************************************************************
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   1 if enabled, 0 if disabled.
*
*
*******************************************************************************/
uint8 isr_DisableDMA_GetState(void)
{
    /* Get the state of the general interrupt. */
    return (*isr_DisableDMA_INTC_SET_EN & isr_DisableDMA__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: isr_DisableDMA_Disable
********************************************************************************
* Summary:
*   Disables the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_DisableDMA_Disable(void)
{
    /* Disable the general interrupt. */
    *isr_DisableDMA_INTC_CLR_EN = isr_DisableDMA__INTC_MASK;
}

/*******************************************************************************
* Function Name: isr_DisableDMA_SetPending
********************************************************************************
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_DisableDMA_SetPending(void)
{
    *isr_DisableDMA_INTC_SET_PD = isr_DisableDMA__INTC_MASK;
}

/*******************************************************************************
* Function Name: isr_DisableDMA_ClearPending
********************************************************************************
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_DisableDMA_ClearPending(void)
{
    *isr_DisableDMA_INTC_CLR_PD = isr_DisableDMA__INTC_MASK;
}


















































