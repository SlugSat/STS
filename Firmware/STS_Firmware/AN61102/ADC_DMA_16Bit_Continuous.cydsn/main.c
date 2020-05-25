/******************************************************************************
* File Name: main.c
*
* Version: 1.00
*
* Description:  This example project demonstrates how to continuously buffer 
*               16 bit ADC data using DMA. 
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
* This example project demonstrates how to continuously buffer 16 bit ADC data
* using DMA. The buffered data can be transferred to a terminal program on PC 
* using the USBUART. The DMA is configured to buffer blocks of ADC data where 
* each block has 64 ADC samples. 
*
* The ADC starts conversion of the input signal and the 64 bytes of data 
* is transferred to the internal memory. The ADC conversion is stopped after 
* this step to allow transfer of data to the USBUART. The USB is configured 
* for Automatic DMA transfers. The ADC conversion is restarted once the data 
* is transferred to terminal program. 
* Connect the USB cable between the PSoC USB port and PC, and ADC input to P6[5]. 
* Run a terminal program like HyperTerminal or PuTTy and watch the 'ADC_sample'.
***************************************************************************** */

#include <project.h>

#define DEVICE_0			0
#define USB_BUFFER_SIZE		62
#define USBUART_EndPoint_Number    0x02

/* DMA Configuration for DMA */
#define DMA_BYTES_PER_BURST 2
#define DMA_REQUEST_PER_BURST 1
#define DMA_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_DST_BASE (CYDEV_SRAM_BASE)

/* Variable declarations for DMA */
uint8 DMA_Chan;
uint8 DMA_TD[1];

uint8 DMA_done = 0;

uint8 ADC_sample[USB_BUFFER_SIZE] = {0};
	
int main()
{
	/* DMA Initialization - 2 byte per trigger. Each burst transfer
	 * needs a new request. Set upper source and destination address. */	
    DMA_Chan = DMA_DmaInitialize(DMA_BYTES_PER_BURST, DMA_REQUEST_PER_BURST, 
                                 HI16(DMA_SRC_BASE), HI16(DMA_DST_BASE));

    /* Allocate TD */
    DMA_TD[0] = CyDmaTdAllocate();

    #if (defined(__C51__))
    /* In PSoC 3 TD swap should be enabled for endian swapping . 
	 * Destination address is incremented after each transaction and
 	 * Term out generated after the specified no. of bytes are 
	 * transferred to memory. Tranfer the specified number of samples
	 * and generate term out */	
    CyDmaTdSetConfiguration(DMA_TD[0], 62, DMA_TD[0], 
                            TD_SWAP_EN | DMA__TD_TERMOUT_EN | TD_INC_DST_ADR);
                            
    #else
		
    /* Destination address is incremented after each transaction and 
	 * Term out generated after the specified no. of bytes are transferred 
	 * to memory. Tranfer the specified number of samples and generate 
	 * term out */
    CyDmaTdSetConfiguration(DMA_TD[0], 62, DMA_TD[0], 
                            DMA__TD_TERMOUT_EN | TD_INC_DST_ADR);     
    #endif
    
    /* Set source and destination address */
    CyDmaTdSetAddress(DMA_TD[0], LO16((uint32)ADC_DelSig_DEC_SAMP_PTR), 
                            LO16((uint32)ADC_sample));
                           
    /* Set the intial TD for the channel */
    CyDmaChSetInitialTd(DMA_Chan, DMA_TD[0]);
	
	/* Enable the DMA channel */
	CyDmaChEnable(DMA_Chan, 1);
	
	/* Enable global interrupt */
	CYGlobalIntEnable;
	
	/* Start USBFS operation with 3V operation */
	USBUART_Start(DEVICE_0, USBUART_3V_OPERATION);
	
	/* Wait for device to enumerate */
	while(!USBUART_GetConfiguration());
	
	/* Initalize USBUART */
	USBUART_CDC_Init();
	
	/* Setup the USB component for automatic DMA transfers */
	USBUART_LoadInEP(USBUART_EndPoint_Number , ADC_sample, 62);
	
	/* Start ADC */
	ADC_DelSig_Start();
    
    /* Disable the ADC ISR as it is not required */
    ADC_DelSig_IRQ_Enable();

	/* Start the interrupt to identify end of DMA transfers */
	DMA_Done_isr_Start();
	
	/* Start ADC conversion */
	ADC_DelSig_StartConvert();
	
	for(;;)
    {
		if(DMA_done)
		{
			/* Stop ADC Conversion for transferring the buffered data */
			ADC_DelSig_StopConvert();
			
			/* Check for USB ready. */
			if(USBUART_CDCIsReady() != 0u) 
			{
				/* Transfer data - can only send 31 ADC results (64 bytes) 
				 * because UART needs null termination. */
				USBUART_LoadInEP(USBUART_EndPoint_Number, 0 , 62);
		
				/* Reset the flag set in DMA Done ISR */
				DMA_done = 0;
				
				/* Delay to allow for human validation of transferred data. 
				 * This is not required in a real project. */
				//CyDelay(1);
				
				/* Restart ADC conversions */
				ADC_DelSig_StartConvert();
			}
		}
	    		
    }/* for loop ends here */
}

/* [] END OF FILE */
