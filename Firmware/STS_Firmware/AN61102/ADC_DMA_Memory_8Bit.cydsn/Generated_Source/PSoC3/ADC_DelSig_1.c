/*******************************************************************************
* File Name: ADC_DelSig_1.c  
* Version 1.30
*
*  Description:
*    This file provides the source code to the API for the Delta-Sigma ADC
*    User Module.
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
#include "cyfitter.h"
#include "cylib.h"
#include "ADC_DelSig_1.h"
#if(ADC_DelSig_1_DEFAULT_INTERNAL_CLK)
    #include "ADC_DelSig_1_theACLK.h"
#endif



uint8 ADC_DelSig_1_initVar = 0;
uint8 ADC_DelSig_1_Resolution = ADC_DelSig_1_DEFAULT_RESOLUTION;

int32 ADC_DelSig_1_Offset = 0;
int32 ADC_DelSig_1_CountsPerVolt = (uint32)ADC_DelSig_1_DFLT_COUNTS_PER_VOLT;   // Gain compensation

/*******************************************************************************
* Function Name: ADC_DelSig_1_Start
********************************************************************************
* Summary:
*  The start function initializes the Delta Sigma Modulator with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as executing
*  the stop function.
*
* Parameters:  
*  None
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ADC_DelSig_1_Start() 
{
  
    if(ADC_DelSig_1_initVar == 0)
    {
        ADC_DelSig_1_initVar = 1;
        ADC_DelSig_1_InitRegisters();

        /* This is only valid if there is an internal clock */
        #if(ADC_DelSig_1_DEFAULT_INTERNAL_CLK)
            ADC_DelSig_1_theACLK_SetMode(CYCLK_DUTY);
        #endif

        /* Start and set interrupt vector */
        CyIntSetPriority(ADC_DelSig_1_IRQ__INTC_NUMBER, ADC_DelSig_1_IRQ_INTC_PRIOR_NUMBER);
        CyIntSetVector(ADC_DelSig_1_IRQ__INTC_NUMBER, ADC_DelSig_1_ISR );
    }

    /* Enable power for ADC */
    ADC_DelSig_1_PWRMGR_DEC |= ADC_DelSig_1_ACT_PWR_DEC_EN;
    ADC_DelSig_1_PWRMGR_DSM |= ADC_DelSig_1_ACT_PWR_DSM_EN;

    /* Enable negative pumps for DSM  */
    ADC_DelSig_1_PUMP_CR1  |= ( ADC_DelSig_1_PUMP_CR1_CLKSEL | ADC_DelSig_1_PUMP_CR1_FORCE );

    ADC_DelSig_1_DEC_CR = ADC_DelSig_1_DFLT_DEC_CR;
    
    /* This is only valid if there is an internal clock */
    #if(ADC_DelSig_1_DEFAULT_INTERNAL_CLK)
        ADC_DelSig_1_PWRMGR_CLK |= ADC_DelSig_1_ACT_PWR_CLK_EN;
        ADC_DelSig_1_theACLK_Enable();
    #endif
}


/*******************************************************************************
* Function Name: ADC_DelSig_1_Stop
********************************************************************************
* Summary:
*  Stops and powers down ADC to lowest power state.
*
* Parameters:  
*  (void) 
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ADC_DelSig_1_Stop(void)
{
    /* Stop conversions */
    ADC_DelSig_1_DEC_CR &= ~ADC_DelSig_1_DEC_START_CONV;
    ADC_DelSig_1_DEC_SR |=  ADC_DelSig_1_DEC_INTR_CLEAR;
    
     /* Disable power to the ADC */
    ADC_DelSig_1_PWRMGR_DSM &= ~ADC_DelSig_1_ACT_PWR_DSM_EN;
    ADC_DelSig_1_PWRMGR_DEC &= ~ADC_DelSig_1_ACT_PWR_DEC_EN;
    
    /* Disable negative pumps for DSM  */
    ADC_DelSig_1_PUMP_CR1 &= ~(ADC_DelSig_1_PUMP_CR1_CLKSEL | ADC_DelSig_1_PUMP_CR1_FORCE );
    
    /* This is only valid if there is an internal clock */
    #if(ADC_DelSig_1_DEFAULT_INTERNAL_CLK)
        ADC_DelSig_1_PWRMGR_CLK &= ~ADC_DelSig_1_ACT_PWR_CLK_EN;
        ADC_DelSig_1_theACLK_Disable();
    #endif
    
}


/*******************************************************************************
* Function Name: ADC_DelSig_1_SetBufferGain
********************************************************************************
* Summary:
*  Set input buffer range.
*
* Parameters:  
*  gain:  Two bit value to select a gain of 1, 2, 4, or 8.
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ADC_DelSig_1_SetBufferGain(uint8 gain)
{
    uint8 tmpReg;
    tmpReg = ADC_DelSig_1_DSM_BUF1 & ~ADC_DelSig_1_DSM_GAIN_MASK;
    tmpReg |= (gain << 2);
    ADC_DelSig_1_DSM_BUF1 = tmpReg;
}



/*******************************************************************************
* Function Name: ADC_DelSig_1_SetBufferChop
********************************************************************************
* Summary:
*  Sets the Delta Sigma Modulator Buffer chopper mode.
*
* Parameters:  
*  chopen:   If non-zero set the chopper mode.
*  chopFreq: Chop frequency value.
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ADC_DelSig_1_SetBufferChop(uint8 chopen, uint8 chopFreq)
{
    if(chopen != 0)
    {
        ADC_DelSig_1_DSM_BUF2 = (ADC_DelSig_1_DSM_BUF_FCHOP_MASK & chopFreq) | ADC_DelSig_1_DSM_BUF_CHOP_EN;
    }
    else
    {
        ADC_DelSig_1_DSM_BUF2 = 0x00;
    }
}





/*******************************************************************************
* Function Name: ADC_DelSig_1_SetPower
********************************************************************************
* Summary:
*  Sets power mode of ADC
*
* Parameters:  
*  power:  Power setting for ADC
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ADC_DelSig_1_SetPower(uint8 power)
{
    uint8 tmpReg;

    /* mask off invalid power settings */
    power &= ADC_DelSig_1_POWER_MASK;

    /* Set Power1 parameter  */
    tmpReg = ADC_DelSig_1_DSM_CR14 & ~ADC_DelSig_1_DSM_POWER1_MASK;
    ADC_DelSig_1_DSM_CR14 = tmpReg | power;


    /* Set Power2_3 parameter  */
    /* ADC_DelSig_1_DSM_CR15 = ADC_DelSig_1_DSM_POWER2_3_HIGH | ADC_DelSig_1_DSM_POWER_12MHZ ; */

    /* Set Power_sum parameter  */
    /* ADC_DelSig_1_DSM_CR16 = ADC_DelSig_1_DSM_CP_PWRCTL_DEFAULT | ADC_DelSig_1_DSM_POWER_SUM_HIGH ; */
}


/*******************************************************************************
* Function Name: ADC_DelSig_1_StartConvert
********************************************************************************
* Summary:
*  Starts ADC conversion using the given mode.
*
* Parameters:  
*  (void)
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ADC_DelSig_1_StartConvert(void)
{
    /* Start the conversion */
    ADC_DelSig_1_DEC_CR |= ADC_DelSig_1_DEC_START_CONV;  
}

/*******************************************************************************
* Function Name: ADC_DelSig_1_StopConvert
********************************************************************************
* Summary:
*  Starts ADC conversion using the given mode.
*
* Parameters:  
*  (void)
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ADC_DelSig_1_StopConvert(void)
{
    /* Stop all conversions */
    ADC_DelSig_1_DEC_CR &= ~ADC_DelSig_1_DEC_START_CONV;  
}

/*******************************************************************************
* Function Name: ADC_DelSig_1_IsEndConversion
********************************************************************************
* Summary:
*  Queries the ADC to see if conversion is complete
*
* Parameters:  
*  wMode:  Wait mode, 0 if return with answer imediately.
*                     1 if wait until conversion is complete, then return.
*
* Return: 
*  (uint8)  0 =>  Conversion not complete.
*           1 =>  Conversion complete.
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
uint8 ADC_DelSig_1_IsEndConversion(uint8 wMode)
{
    uint8 status;

    do 
    {
        status = ADC_DelSig_1_DEC_SR & ADC_DelSig_1_DEC_CONV_DONE;
    } while((status != ADC_DelSig_1_DEC_CONV_DONE) && (wMode == ADC_DelSig_1_WAIT_FOR_RESULT));

    return(status);
}

/*******************************************************************************
* Function Name: ADC_DelSig_1_GetResult8
********************************************************************************
* Summary:
*  Returns an 8-bit result or the LSB of the last conversion.
*
* Parameters:  
*  (void) 
*
* Return: 
*  (int8) ADC result.
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
int8 ADC_DelSig_1_GetResult8( void )
{
    return( ADC_DelSig_1_DEC_SAMP );
}


/*******************************************************************************
* Function Name: ADC_DelSig_1_GetResult16
********************************************************************************
* Summary:
*  Returns a 16-bit result from the last ADC conversion.
*
* Parameters:  
*   (void)
*
* Return: 
*  (int16) ADC result.
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
int16 ADC_DelSig_1_GetResult16(void)
{
    uint16 result;
    result = ADC_DelSig_1_DEC_SAMPM ;
    result = (result << 8 ) | ADC_DelSig_1_DEC_SAMP;
    return( result );
}

/*******************************************************************************
* Function Name: ADC_DelSig_1_GetResult32
********************************************************************************
* Summary:
*  Returns an 32-bit result from ADC
*
* Parameters:  
*   (void)
*
* Return: 
*  (int32) ADC result.
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
int32 ADC_DelSig_1_GetResult32(void)
{
    uint32 result;

    result = (int8) ADC_DelSig_1_DEC_SAMPH;
    result = (result << 8) | ADC_DelSig_1_DEC_SAMPM;
    result = (result << 8) | ADC_DelSig_1_DEC_SAMP;
    return( result );
}


/*******************************************************************************
* Function Name: ADC_DelSig_1_SetOffset
********************************************************************************
* Summary:
*  This function sets the offset for voltage readings.
*
* Parameters:  
*  int32  offset  Offset in counts
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ADC_DelSig_1_SetOffset(int32 offset) 
{
 
    ADC_DelSig_1_Offset = offset;
}

/*******************************************************************************
* Function Name: ADC_DelSig_1_SetGain
********************************************************************************
* Summary:
*  This function sets the ADC gain in counts per volt.
*
* Parameters:  
*  int32  offset  Offset in counts
*
* Return: 
*  (void) 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ADC_DelSig_1_SetGain(int32 adcGain) 
{
 
    ADC_DelSig_1_CountsPerVolt = adcGain;
}

/*******************************************************************************
* Function Name: ADC_DelSig_1_CountsTo_mVolts
********************************************************************************
* Summary:
*  This function converts ADC counts to mVolts
*
* Parameters:  
*  int32  adcCounts   Reading from ADC.
*
* Return: 
*  int32  Result in mVolts
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
int16 ADC_DelSig_1_CountsTo_mVolts( int32 adcCounts) 
{

    int32 mVolts = 0;
    int32 A, B;

    /* Subtract ADC offset */
    adcCounts -= ADC_DelSig_1_Offset;

    if(ADC_DelSig_1_DEFAULT_RESOLUTION < 17)
    {
        A = 1000;
        B = 1;
    }
    else
    {
        A = 100;
        B = 10;
    }

    mVolts = ((A * adcCounts) / ((int32)ADC_DelSig_1_CountsPerVolt/B)) ;   

    return( (int16)mVolts );
}

/*******************************************************************************
* Function Name: ADC_DelSig_1_CountsTo_fuVolts
********************************************************************************
* Summary:
*  This function converts ADC counts to uVolts
*
* Parameters:  
*  int32  adcCounts   Reading from ADC.
*
* Return: 
*  int32  Result in uVolts
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
float ADC_DelSig_1_CountsTo_Volts( int32 adcCounts) 
{

    float Volts = 0;

    /* Subtract ADC offset */
    adcCounts -= ADC_DelSig_1_Offset;

    Volts = (float)adcCounts / (float)ADC_DelSig_1_CountsPerVolt;   
    
    return( Volts );
}

/*******************************************************************************
* Function Name: ADC_DelSig_1_CountsTo_uVolts
********************************************************************************
* Summary:
*  This function converts ADC counts to uVolts
*
* Parameters:  
*  int32  adcCounts   Reading from ADC.
*
* Return: 
*  int32  Result in uVolts
*
* Theory: 
* Care must be taken to not exceed the maximum value for a 32 bit signed
* number in the conversion to uVolts and at the same time not loose 
* resolution.
*
* uVolts = ((A * adcCounts) / ((int32)ADC_DelSig_1_CountsPerVolt/B)) ;   
*
*  Resolution       A           B
*   8 - 11      1,000,000         1
*  12 - 14        100,000        10
*  15 - 17         10,000       100
*  18 - 20           1000      1000
*
* Side Effects:
*
*******************************************************************************/
int32 ADC_DelSig_1_CountsTo_uVolts( int32 adcCounts) 
{

    int32 uVolts = 0;
    int32 A, B;
    
    if(ADC_DelSig_1_DEFAULT_RESOLUTION < 12)
    {
        A = 1000000;
        B = 1;
    }
    else if(ADC_DelSig_1_DEFAULT_RESOLUTION < 15)
    {
        A = 100000;
        B = 10;
    }
    else if(ADC_DelSig_1_DEFAULT_RESOLUTION < 18)
    {
        A = 10000;
        B = 100;
    }
    else
    {
        A = 1000;
        B = 1000;
    }

    /* Subtract ADC offset */
    adcCounts -= ADC_DelSig_1_Offset;

    uVolts = ((A * adcCounts) / ((int32)ADC_DelSig_1_CountsPerVolt/B)) ;   
  

    return( uVolts );
}


/*******************************************************************************
* Function Name: ADC_DelSig_1_IRQ_Start(void)
********************************************************************************
* Summary:
*  Set up the interrupt and enable it. The IRQ_Start() API is included to 
*  support legacy code. The routine has been replaced by the library source 
*  code for interrupts. IRQ_Start() should not be used in new designs.
* 
* Parameters:  
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void ADC_DelSig_1_IRQ_Start(void)
{
    /* For all we know the interrupt is active. */
    CyIntDisable(ADC_DelSig_1_IRQ__INTC_NUMBER );

    /* Set the ISR to point to the ADC_DelSig_1_IRQ Interrupt. */
    CyIntSetVector(ADC_DelSig_1_IRQ__INTC_NUMBER, ADC_DelSig_1_ISR);

    /* Set the priority. */
    CyIntSetPriority(ADC_DelSig_1_IRQ__INTC_NUMBER, ADC_DelSig_1_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    CyIntEnable(ADC_DelSig_1_IRQ__INTC_NUMBER);
}


/*******************************************************************************
* Function Name: ADC_DelSig_1_InitRegisters(void)
********************************************************************************
* Summary:
*  Initializes all registers based on customizer settings
*
* Parameters:  
*   (void)
*
* Return: 
*  (void)
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ADC_DelSig_1_InitRegisters(void)
{

    ADC_DelSig_1_DEC_CR     = ADC_DelSig_1_DFLT_DEC_CR;      
    ADC_DelSig_1_DEC_SR     = ADC_DelSig_1_DFLT_DEC_SR;      
    ADC_DelSig_1_DEC_SHIFT1 = ADC_DelSig_1_DFLT_DEC_SHIFT1;  
    ADC_DelSig_1_DEC_SHIFT2 = ADC_DelSig_1_DFLT_DEC_SHIFT2;  
    ADC_DelSig_1_DEC_DR2    = ADC_DelSig_1_DFLT_DEC_DR2;     
    ADC_DelSig_1_DEC_DR2H   = ADC_DelSig_1_DFLT_DEC_DR2H;    
    ADC_DelSig_1_DEC_DR1    = ADC_DelSig_1_DFLT_DEC_DR1;     
    ADC_DelSig_1_DEC_OCOR   = ADC_DelSig_1_DFLT_DEC_OCOR;    
    ADC_DelSig_1_DEC_OCORM  = ADC_DelSig_1_DFLT_DEC_OCORM;   
    ADC_DelSig_1_DEC_OCORH  = ADC_DelSig_1_DFLT_DEC_OCORH;   
    ADC_DelSig_1_DEC_GVAL   = ADC_DelSig_1_DFLT_DEC_GVAL;    
    ADC_DelSig_1_DEC_GCOR   = ADC_DelSig_1_DFLT_DEC_GCOR;    
    ADC_DelSig_1_DEC_GCORH  = ADC_DelSig_1_DFLT_DEC_GCORH;   
    ADC_DelSig_1_DEC_COHER  = ADC_DelSig_1_DFLT_DEC_COHER;   

    ADC_DelSig_1_DSM_CR0  = ADC_DelSig_1_DFLT_DSM_CR0;     
    ADC_DelSig_1_DSM_CR1  = ADC_DelSig_1_DFLT_DSM_CR1;     
    ADC_DelSig_1_DSM_CR2  = ADC_DelSig_1_DFLT_DSM_CR2;     
    ADC_DelSig_1_DSM_CR3  = ADC_DelSig_1_DFLT_DSM_CR3;     
    ADC_DelSig_1_DSM_CR4  = ADC_DelSig_1_DFLT_DSM_CR4;     
    ADC_DelSig_1_DSM_CR5  = ADC_DelSig_1_DFLT_DSM_CR5;     
    ADC_DelSig_1_DSM_CR6  = ADC_DelSig_1_DFLT_DSM_CR6;     
    ADC_DelSig_1_DSM_CR7  = ADC_DelSig_1_DFLT_DSM_CR7;     
    ADC_DelSig_1_DSM_CR8  = ADC_DelSig_1_DFLT_DSM_CR8;     
    ADC_DelSig_1_DSM_CR9  = ADC_DelSig_1_DFLT_DSM_CR9;     
    ADC_DelSig_1_DSM_CR10 = ADC_DelSig_1_DFLT_DSM_CR10;    
    ADC_DelSig_1_DSM_CR11 = ADC_DelSig_1_DFLT_DSM_CR11;    
    ADC_DelSig_1_DSM_CR12 = ADC_DelSig_1_DFLT_DSM_CR12;    
    ADC_DelSig_1_DSM_CR13 = ADC_DelSig_1_DFLT_DSM_CR13;    
    ADC_DelSig_1_DSM_CR14 = ADC_DelSig_1_DFLT_DSM_CR14;    
    ADC_DelSig_1_DSM_CR15 = ADC_DelSig_1_DFLT_DSM_CR15;    
    ADC_DelSig_1_DSM_CR16 = ADC_DelSig_1_DFLT_DSM_CR16;    
    ADC_DelSig_1_DSM_CR17 = ADC_DelSig_1_DFLT_DSM_CR17;    
    ADC_DelSig_1_DSM_REF0 = ADC_DelSig_1_DFLT_DSM_REF0;    
    ADC_DelSig_1_DSM_REF1 = ADC_DelSig_1_DFLT_DSM_REF1;    
    ADC_DelSig_1_DSM_REF2 = ADC_DelSig_1_DFLT_DSM_REF2;    
    ADC_DelSig_1_DSM_REF3 = ADC_DelSig_1_DFLT_DSM_REF3;    

    ADC_DelSig_1_DSM_DEM0 = ADC_DelSig_1_DFLT_DSM_DEM0;    
    ADC_DelSig_1_DSM_DEM1 = ADC_DelSig_1_DFLT_DSM_DEM1;    
    ADC_DelSig_1_DSM_MISC = ADC_DelSig_1_DFLT_DSM_MISC;    
    ADC_DelSig_1_DSM_CLK  |= ADC_DelSig_1_DFLT_DSM_CLK;     

    ADC_DelSig_1_DSM_BUF0 = ADC_DelSig_1_DFLT_DSM_BUF0;    
    ADC_DelSig_1_DSM_BUF1 = ADC_DelSig_1_DFLT_DSM_BUF1;    
    ADC_DelSig_1_DSM_BUF2 = ADC_DelSig_1_DFLT_DSM_BUF2;    
    ADC_DelSig_1_DSM_BUF3 = ADC_DelSig_1_DFLT_DSM_BUF3;    
    ADC_DelSig_1_DSM_OUT0 = ADC_DelSig_1_DFLT_DSM_OUT0;    
    ADC_DelSig_1_DSM_OUT1 = ADC_DelSig_1_DFLT_DSM_OUT1;    

}
/* [] END OF FILE */



