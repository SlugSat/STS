/*******************************************************************************
* File Name: ISR_DMADone_intc.c  
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
#include <ISR_DMADone.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START ISR_DMADone_intc` */
extern uint8 DMADone_flag;
/* `#END` */


/*******************************************************************************
* Function Name: ISR_DMADone_Start
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
void ISR_DMADone_Start(void)
{
    /* For all we know the interrupt is active. */
    ISR_DMADone_Disable();

    /* Set the ISR to point to the ISR_DMADone Interrupt. */
    ISR_DMADone_SetVector(ISR_DMADone_Interrupt);

    /* Set the priority. */
    ISR_DMADone_SetPriority(ISR_DMADone_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ISR_DMADone_Enable();
}

/*******************************************************************************
* Function Name: ISR_DMADone_Stop
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
void ISR_DMADone_Stop(void)
{
    /* Disable this interrupt. */
    ISR_DMADone_Disable();

    /* Set the ISR to point to the passive one. */
//    ISR_DMADone_SetVector(CyDefaultInterrupt);
}

/*******************************************************************************
* Function Name: ISR_DMADone_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for ISR_DMADone.
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
CY_ISR(ISR_DMADone_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START ISR_DMADone_Interrupt` */

	/* Set the flag to disable the DMA channel */
	DMADone_flag = 1;

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
        #if((CYDEV_CHIP_REV_EXPECT <= CYDEV_CHIP_REV_LEOPARD_ES2) && (ISR_DMADone__ES2_PATCH ))      
            ISR_DMADone_ISR_PATCH();
        #endif
    #endif
}


/*******************************************************************************
* Function Name: ISR_DMADone_SetVector
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
void ISR_DMADone_SetVector(cyisraddress address)
{
    CY_SET_REG16(ISR_DMADone_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: ISR_DMADone_GetVector
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
cyisraddress ISR_DMADone_GetVector(void)
{
    return (cyisraddress) CY_GET_REG16(ISR_DMADone_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: ISR_DMADone_SetPriority
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
void ISR_DMADone_SetPriority(uint8 priority)
{
    *ISR_DMADone_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: ISR_DMADone_GetPriority
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
uint8 ISR_DMADone_GetPriority(void)
{
    uint8 priority;


    priority = *ISR_DMADone_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: ISR_DMADone_Enable
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
void ISR_DMADone_Enable(void)
{
    /* Enable the general interrupt. */
    *ISR_DMADone_INTC_SET_EN = ISR_DMADone__INTC_MASK;
}

/*******************************************************************************
* Function Name: ISR_DMADone_GetState
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
uint8 ISR_DMADone_GetState(void)
{
    /* Get the state of the general interrupt. */
    return (*ISR_DMADone_INTC_SET_EN & ISR_DMADone__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: ISR_DMADone_Disable
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
void ISR_DMADone_Disable(void)
{
    /* Disable the general interrupt. */
    *ISR_DMADone_INTC_CLR_EN = ISR_DMADone__INTC_MASK;
}

/*******************************************************************************
* Function Name: ISR_DMADone_SetPending
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
void ISR_DMADone_SetPending(void)
{
    *ISR_DMADone_INTC_SET_PD = ISR_DMADone__INTC_MASK;
}

/*******************************************************************************
* Function Name: ISR_DMADone_ClearPending
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
void ISR_DMADone_ClearPending(void)
{
    *ISR_DMADone_INTC_CLR_PD = ISR_DMADone__INTC_MASK;
}


















































