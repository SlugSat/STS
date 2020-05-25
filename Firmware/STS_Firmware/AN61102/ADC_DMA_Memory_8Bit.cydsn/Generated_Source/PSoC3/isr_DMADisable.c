/*******************************************************************************
* File Name: isr_DMADisable_intc.c  
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
#include <isr_DMADisable.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START isr_DMADisable_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: isr_DMADisable_Start
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
void isr_DMADisable_Start(void)
{
    /* For all we know the interrupt is active. */
    isr_DMADisable_Disable();

    /* Set the ISR to point to the isr_DMADisable Interrupt. */
    isr_DMADisable_SetVector(isr_DMADisable_Interrupt);

    /* Set the priority. */
    isr_DMADisable_SetPriority(isr_DMADisable_INTC_PRIOR_NUMBER);

    /* Enable it. */
    isr_DMADisable_Enable();
}

/*******************************************************************************
* Function Name: isr_DMADisable_Stop
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
void isr_DMADisable_Stop(void)
{
    /* Disable this interrupt. */
    isr_DMADisable_Disable();

    /* Set the ISR to point to the passive one. */
//    isr_DMADisable_SetVector(CyDefaultInterrupt);
}

/*******************************************************************************
* Function Name: isr_DMADisable_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for isr_DMADisable.
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
CY_ISR(isr_DMADisable_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START isr_DMADisable_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
        #if((CYDEV_CHIP_REV_EXPECT <= CYDEV_CHIP_REV_LEOPARD_ES2) && (isr_DMADisable__ES2_PATCH ))      
            isr_DMADisable_ISR_PATCH();
        #endif
    #endif
}


/*******************************************************************************
* Function Name: isr_DMADisable_SetVector
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
void isr_DMADisable_SetVector(cyisraddress address)
{
    CY_SET_REG16(isr_DMADisable_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: isr_DMADisable_GetVector
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
cyisraddress isr_DMADisable_GetVector(void)
{
    return (cyisraddress) CY_GET_REG16(isr_DMADisable_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: isr_DMADisable_SetPriority
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
void isr_DMADisable_SetPriority(uint8 priority)
{
    *isr_DMADisable_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: isr_DMADisable_GetPriority
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
uint8 isr_DMADisable_GetPriority(void)
{
    uint8 priority;


    priority = *isr_DMADisable_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: isr_DMADisable_Enable
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
void isr_DMADisable_Enable(void)
{
    /* Enable the general interrupt. */
    *isr_DMADisable_INTC_SET_EN = isr_DMADisable__INTC_MASK;
}

/*******************************************************************************
* Function Name: isr_DMADisable_GetState
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
uint8 isr_DMADisable_GetState(void)
{
    /* Get the state of the general interrupt. */
    return (*isr_DMADisable_INTC_SET_EN & isr_DMADisable__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: isr_DMADisable_Disable
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
void isr_DMADisable_Disable(void)
{
    /* Disable the general interrupt. */
    *isr_DMADisable_INTC_CLR_EN = isr_DMADisable__INTC_MASK;
}

/*******************************************************************************
* Function Name: isr_DMADisable_SetPending
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
void isr_DMADisable_SetPending(void)
{
    *isr_DMADisable_INTC_SET_PD = isr_DMADisable__INTC_MASK;
}

/*******************************************************************************
* Function Name: isr_DMADisable_ClearPending
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
void isr_DMADisable_ClearPending(void)
{
    *isr_DMADisable_INTC_CLR_PD = isr_DMADisable__INTC_MASK;
}


















































