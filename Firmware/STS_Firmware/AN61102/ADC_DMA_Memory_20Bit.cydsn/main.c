/******************************************************************************
* File Name: main.c
*
* Version: 1.00
*
* Description:  This example project demonstrates how to buffer 20 bit ADC data 
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
* This example project demonstrates how to buffer 20 bit ADC data using DMA.
* The DMA is configured to buffer specified number of ADC samples on a 
* switch press. The DMA channel is enabled on each switch press and disabled 
* after collecting the specified number of ADC samples. Connect P1[2] to switch
* SW1 on DVK and connect ADC input to P0[2]. Run the debugger and put a 
* break point inside the 'if(DMADone_flag)' loop and watch the 'ADC_sample' 
* buffer in watch window of debugger to verify the output.
***************************************************************************** */

#include <device.h>
#define BUFFER_SIZE 50
#define TRANSFER_COUNT BUFFER_SIZE*4

/* Variable declarations for DMA */
uint8 DMA_ADC2Mem_Chan;
uint8 DMA_ADC2Mem_TD[1];

void Configure_DMA_ADC2Mem(void);
void Configure_DMA_Mem2Mem(void);

volatile uint8 switch_Flag,DMADone_flag;

/* adc_ temp is the intermediate variable used to store ADC data . 
* It is important to place this variable in 32 bit aligned location for
* DMA to transfer 4 bytes data in one shot */

#if (defined(__C51__))/* If PSoC 3 Keil compiler */

/* Directive to place adc_temp at a particular location. The location is 
chosen as a multiple of 4 bytes (even boundary) */
uint32 xdata adc_temp _at_ 0x100; 
uint32 xdata ADC_sample[BUFFER_SIZE] _at_ 0x200;

#else

/* Explicitly specify the alignment (in bytes) that you wish the compiler 
 * to use for a given variable or structure field */
uint32 adc_temp;
uint32 ADC_sample[BUFFER_SIZE];

#endif

/* DMA Configuration for DMA_ADC2Mem */
#define DMA_ADC2Mem_BYTES_PER_BURST 4
#define DMA_ADC2Mem_REQUEST_PER_BURST 1
#define DMA_ADC2Mem_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_ADC2Mem_DST_BASE (CYDEV_SRAM_BASE)

/* Variable declarations for DMA_Mem2Mem */
uint8 DMA_Mem2Mem_Chan;
uint8 DMA_Mem2Mem_TD[1];
	
/* DMA Configuration for DMA_Mem2Mem */
#define DMA_Mem2Mem_BYTES_PER_BURST 4
#define DMA_Mem2Mem_REQUEST_PER_BURST 1
#define DMA_Mem2Mem_SRC_BASE (CYDEV_SRAM_BASE)
#define DMA_Mem2Mem_DST_BASE (CYDEV_SRAM_BASE)

int main()
{
	/* Enable interrupts */
    CyGlobalIntEnable; 
	
	/*Start isr connected to switch pin*/
	ISR_Switch_Start();

	/*Start isr connected to DMA nrq signal*/
	ISR_DMA_Done_Start();

	/* Configure DMA to transfer data from ADC to temporary memory*/
	Configure_DMA_ADC2Mem();
	
	/* Configure DMA to transfer the data from temporary memory to memory buffer*/
	Configure_DMA_Mem2Mem();

	/*Start ADC*/
	ADC_DelSig_Start();

    /* Disable ADC interrupts */
	ADC_DelSig_IRQ_Disable();

	/*Change the ADC coherent key to high byte*/
	ADC_DelSig_DEC_COHER_REG |= ADC_DelSig_DEC_SAMP_KEY_HIGH;

	/*Start ADC conversions*/
	ADC_DelSig_StartConvert();

    for(;;)
    {
		/*If switch is pressed */
		if(switch_Flag)
		{
			/* Enable the DMA channels */
			CyDmaChEnable(DMA_ADC2Mem_Chan, 1);
			CyDmaChEnable(DMA_Mem2Mem_Chan, 1);
	
			/* Reset the flag */
			switch_Flag=0;
		}
		/* Once the DMA finished buffering of specified number of ADC samples */
		if(DMADone_flag)
		{
			/* Disable the DMA channels*/
			CyDmaChDisable(DMA_ADC2Mem_Chan);
			CyDmaChDisable(DMA_Mem2Mem_Chan);
			
			/* Reset the flag */
			DMADone_flag=0;
		}
    }
}

/*******************************************************************************
* Function Name: Configure_DMA_ADC2Mem
********************************************************************************
* Summary:
*  Configure the DMA channel to move data from ADC to temporary RAM location
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Theory: 
* The following APIs configure the DMA_ADC2Mem to transfer an ADC sample (4 bytes)
* from ADC to memory on each EoC trigger.
* Burst Count = Transfer Count = 4. 
* TD configured to increment source address. Enable endian swapping for PSoC 3.
*
* Side Effects:
*
*******************************************************************************/

void Configure_DMA_ADC2Mem(void)
{

	DMA_ADC2Mem_Chan = DMA_ADC2Mem_DmaInitialize(DMA_ADC2Mem_BYTES_PER_BURST, DMA_ADC2Mem_REQUEST_PER_BURST, 
		HI16(DMA_ADC2Mem_SRC_BASE), HI16(DMA_ADC2Mem_DST_BASE));

	DMA_ADC2Mem_TD[0] = CyDmaTdAllocate();
	
	/* If PSoC 3 enable byte swapping else don't enable swapping*/
	#if (defined(__C51__))

		CyDmaTdSetConfiguration(DMA_ADC2Mem_TD[0], 4, DMA_ADC2Mem_TD[0], TD_SWAP_EN | TD_SWAP_SIZE4 | \
		                                        DMA_ADC2Mem__TD_TERMOUT_EN | TD_INC_SRC_ADR);
	#else 
		CyDmaTdSetConfiguration(DMA_ADC2Mem_TD[0], 4, DMA_ADC2Mem_TD[0],  DMA_ADC2Mem__TD_TERMOUT_EN |\
		                                        TD_INC_SRC_ADR);
    #endif
	
	CyDmaTdSetAddress(DMA_ADC2Mem_TD[0], LO16((uint32)ADC_DelSig_DEC_SAMP_PTR), LO16((uint32)&adc_temp));
	CyDmaChSetInitialTd(DMA_ADC2Mem_Chan, DMA_ADC2Mem_TD[0]);

}


/*******************************************************************************
* Function Name: Configure_DMA_Mem2Mem
********************************************************************************
* Summary:
* Configure the DMA channel to move data from temporary RAM location to RAM buffer
*
* Parameters:  
*  None
*
* Return: 
*  None 
*
* Theory: 
* The following APIs configure the DMA_Mem2Mem to transfer the specified number of 
* samples intermediate memory location to ADC_sample buffer.
* Burst Count =4, Transfer Count = 4* Buffer size , TD configured to increment 
* destination address.
*
* Side Effects:
*
*******************************************************************************/
void Configure_DMA_Mem2Mem(void)
{

	DMA_Mem2Mem_Chan = DMA_Mem2Mem_DmaInitialize(DMA_Mem2Mem_BYTES_PER_BURST, DMA_Mem2Mem_REQUEST_PER_BURST, 
		HI16(DMA_Mem2Mem_SRC_BASE), HI16(DMA_Mem2Mem_DST_BASE));

	DMA_Mem2Mem_TD[0] = CyDmaTdAllocate();
	CyDmaTdSetConfiguration(DMA_Mem2Mem_TD[0], TRANSFER_COUNT, DMA_Mem2Mem_TD[0],\
	                                                  DMA_Mem2Mem__TD_TERMOUT_EN | TD_INC_DST_ADR);
	CyDmaTdSetAddress(DMA_Mem2Mem_TD[0], LO16((uint32)&adc_temp), LO16((uint32)ADC_sample));
	CyDmaChSetInitialTd(DMA_Mem2Mem_Chan, DMA_Mem2Mem_TD[0]);

}

/* [] END OF FILE */
