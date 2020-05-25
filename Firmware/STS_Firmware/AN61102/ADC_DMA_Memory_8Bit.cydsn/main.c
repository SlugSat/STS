/******************************************************************************
* File Name: main.c
*
* Version: 1.00
*
* Description:  This example project demonstrates how to buffer 8 bit ADC data 
*               using DMA. 
*
* Related Document: AN61102- PSoC 3 and PSoC 5LP - ADC Data Buffering Using DMA
*
* Hardware Dependency: CY8CKIT-050 PSoC 5LP Development Kit, 
*                      CY8CKIT-030 PSoC 3 Development Kit or
*                      CY8CKIT-001 PSoC Development Kit
*                      
*******************************************************************************
* Copyright (2018), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product”). By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/
/******************************************************************************
* This example project demonstrates how to buffer 8 bit ADC data using DMA.
* The DMA is configured to buffer specified number of ADC samples on a 
* switch press. The DMA channel is enabled on each switch press and disabled 
* after buffering the specified number of ADC samples. Connect P1[2] to switch 
* SW1 on DVK and connect ADC input to P0[2]. Run the debugger and verify the
* output - Watch the 'ADC_sample' buffer in watch window of debugger.
***************************************************************************** */

#include <device.h>

/* Define for the number of samples to be transferred to memory on
 * each switch press */
#define NO_OF_SAMPLES 500

/* Variable declarations for DMA */
uint8 DMA_Chan;
uint8 DMA_TD[1];
volatile uint8 switch_flag = 0, DMADone_flag = 0;

int main()
{
	/* The buffer to store the ADC samples */
    uint8 ADC_sample[NO_OF_SAMPLES] = {0};
   
    /* Defines for DMA Configuration */
    #define DMA_BYTES_PER_BURST 1
    #define DMA_REQUEST_PER_BURST 1
    #define DMA_SRC_BASE (CYDEV_PERIPH_BASE)
    #define DMA_DST_BASE (CYDEV_SRAM_BASE)

	/* Start isr connected to collect samples pin */
	ISR_Switch_Start();
	
	/* Start isr connected to DMA nrq signal */
	ISR_DMA_Done_Start();
	
    /* DMA Initialization - 1 byte per trigger.  Each burst transfer needs a new request. 
     * Also set the upper source and destination address. */
	DMA_Chan = DMA_DmaInitialize(DMA_BYTES_PER_BURST, DMA_REQUEST_PER_BURST, 
                                    HI16(DMA_SRC_BASE), HI16(DMA_DST_BASE));
    
    /* Allocate TD */
    DMA_TD[0] = CyDmaTdAllocate();
    
    /* Tranfer the specified no. of samples and generate term out.
     * Increment destination address after each transaction.
     * The TD is also looped back to itself */	
    CyDmaTdSetConfiguration(DMA_TD[0], NO_OF_SAMPLES, DMA_TD[0],
                            DMA__TD_TERMOUT_EN | TD_INC_DST_ADR);
    
    /* Set source and destination address */
    CyDmaTdSetAddress(DMA_TD[0], LO16((uint32)ADC_DelSig_DEC_SAMP_PTR),
                      LO16((uint32)ADC_sample));
    
    /* Set the intial TD for the channel */
    CyDmaChSetInitialTd(DMA_Chan, DMA_TD[0]);

	/* Start ADC */
	ADC_DelSig_Start();

    /* The ADC Interrupt is disabled because the system doesn't need the interrupt */
    ADC_DelSig_IRQ_Disable();
    
    /* Enable global interrupt */
	CyGlobalIntEnable; 
	
    /* Start ADC conversion */
	ADC_DelSig_StartConvert();


	for(;;)
    {
	    /* If Switch is pressed */
		if(switch_flag)
		{
			/* Enable the DMA channel */
			CyDmaChEnable(DMA_Chan, 1);
			
			/* Clear the Flag */
			switch_flag=0;
			
		}/* If statement ends here */

	    /* If DMA has finished the transfer */
		if(DMADone_flag)
		{
			/* Disable the DMA channel */
			CyDmaChDisable(DMA_Chan);
			
			/* Clear the Flag */
			DMADone_flag=0;
			
		}/* If statement ends here */
		
    }/* for loop ends here */
        
}

/* [] END OF FILE */
