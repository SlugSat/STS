/*******************************************************************************
* File Name: ADC_DelSig_1_INT.c  
* Version 1.30
*
*  Description:
*    This file contains the code that operates during the ADC_DelSig interrupt 
*    service routine.  
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



#include "cytypes.h"
#include "ADC_DelSig_1.h"  

/*******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following 
*   #START and #END tags
*******************************************************************************/
/* `#START ADC_SYS_VAR`  */

/* `#END`  */


/*******************************************************************************
* Function Name: ADC_DelSig_1_ISR
********************************************************************************
* Summary:
*  Handle Interrupt Service Routine.  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
CY_ISR( ADC_DelSig_1_ISR )
{
    /***************************************************************************
    *  Custom Code
    *  - add user ISR code between the following #START and #END tags
    **************************************************************************/
    /* `#START MAIN_ADC_ISR`  */

    /* `#END`  */
    
    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
        #if((CYDEV_CHIP_REV_EXPECT <= CYDEV_CHIP_REV_LEOPARD_ES2) && (ADC_DelSig_1_IRQ__ES2_PATCH ))      
            ADC_DelSig_1_ISR_PATCH();
        #endif
    #endif
            
}

/* [] END OF FILE */
