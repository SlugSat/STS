/*******************************************************************************
* File Name: ADC_DelSig_1.h  
* Version 1.30
*
*  Description:
*    This file contains the function prototypes and constants used in
*    the Delta-Sigma ADC user module.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include "cytypes.h"
#include "cyfitter.h"
#include "cydevice.h"  /* This required until DSM power register control is moved. */

#if !defined(CY_ADC_DELSIG_ADC_DelSig_1_H) 
#define CY_ADC_DELSIG_ADC_DelSig_1_H 

#if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)     
    #if(CYDEV_CHIP_REV_EXPECT <= CYDEV_CHIP_REV_LEOPARD_ES2)      
        #include <intrins.h>
        #define ADC_DelSig_1_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    #endif
#endif    

/***************************************
*        Function Prototypes 
***************************************/

void    ADC_DelSig_1_Start(void);
void    ADC_DelSig_1_Stop(void);
void    ADC_DelSig_1_SetPower(uint8 power);
void    ADC_DelSig_1_SetBufferGain(uint8 gain);
void    ADC_DelSig_1_StartConvert(void);
void    ADC_DelSig_1_StopConvert(void);
uint8   ADC_DelSig_1_IsEndConversion(uint8 retMode);
int8    ADC_DelSig_1_GetResult8(void);
int16   ADC_DelSig_1_GetResult16(void);
int32   ADC_DelSig_1_GetResult32(void);
void    ADC_DelSig_1_SetOffset(int32 offset); 
void    ADC_DelSig_1_SetGain(int32 adcGain); 
int16   ADC_DelSig_1_CountsTo_mVolts( int32 adcCounts); 
float   ADC_DelSig_1_CountsTo_Volts( int32 adcCounts); 
int32   ADC_DelSig_1_CountsTo_uVolts( int32 adcCounts);
void    ADC_DelSig_1_InitRegisters(void);
CY_ISR_PROTO( ADC_DelSig_1_ISR );

/* These functions may not be supported in the released version */
void    ADC_DelSig_1_SetBufferChop(uint8 chopen, uint8 chopFreq);
#define ADC_DelSig_1_IRQ_Enable() CyIntEnable(ADC_DelSig_1_IRQ__INTC_NUMBER ); 
#define ADC_DelSig_1_IRQ_Disable() CyIntDisable(ADC_DelSig_1_IRQ__INTC_NUMBER );

/*******************************************************************************
* The following API?s are to support legacy code.  The IRQ_Start
* And IRQ_Stop routine have been replaced by the library source code
* for interrupts. IRQ_Start() and IRQ_Stop() should not be used in new
* designs
*******************************************************************************/
void     ADC_DelSig_1_IRQ_Start(void);
#define ADC_DelSig_1_IRQ_Stop() CyIntDisable(ADC_DelSig_1_IRQ__INTC_NUMBER )



/**************************************
*           Parameter Defaults        
**************************************/

/* Default config values from user parameters */

#define ADC_DelSig_1_DEFAULT_POWER        1           /* Default power setting */
#define ADC_DelSig_1_DEFAULT_RESOLUTION   8      /* ADC resolution selected with parameters. */
#define ADC_DelSig_1_DEFAULT_RANGE        0     /* ADC Input Range selection. */
#define ADC_DelSig_1_DEFAULT_SRATE        384000         /* Selected sample rate */
#define ADC_DelSig_1_DEFAULT_REFERENCE    0       /* Default reference */
#define ADC_DelSig_1_DEFAULT_BUF_GAIN     1   /* Default buffer gain. */
#define ADC_DelSig_1_DEFAULT_STROBE       0 /* Start of conversion method */
#define ADC_DelSig_1_DEFAULT_INTERNAL_CLK 1           /* Default clock selection */
#define ADC_DelSig_1_DEFAULT_CONV_MODE    2     /* Default conversion method */

/* Priority of the ADC_IRQ interrupt. */
#define ADC_DelSig_1_IRQ_INTC_PRIOR_NUMBER      ADC_DelSig_1_IRQ__INTC_PRIOR_NUM


/**************************************
*           API Constants        
**************************************/

/* Constants for SetPower(), "power" paramter  */
#define ADC_DelSig_1_LOWPOWER              0x00u 
#define ADC_DelSig_1_MEDPOWER              0x01u 
#define ADC_DelSig_1_HIGHPOWER             0x02u 
#define ADC_DelSig_1_HIGHPOWER_1_5         0x03u  /* Reserved */
#define ADC_DelSig_1_HIGHPOWER_2_0         0x04u  /* Reserved */
#define ADC_DelSig_1_HIGHPOWER_2_5         0x07u  /* Reserved */
#define ADC_DelSig_1_POWER_MASK            0x07u 

/*  Constants for SetBufferGain() "gain" paramter  */
#define ADC_DelSig_1_BUF_GAIN_1X           0x00u 
#define ADC_DelSig_1_BUF_GAIN_2X           0x01u 
#define ADC_DelSig_1_BUF_GAIN_4X           0x02u 
#define ADC_DelSig_1_BUF_GAIN_8X           0x03u 
#define ADC_DelSig_1_BUF_GAIN_MASK         0x03u 

/*   Constants for IsEndConversion() "retMode" parameter  */
#define ADC_DelSig_1_RETURN_STATUS         0x01u 
#define ADC_DelSig_1_WAIT_FOR_RESULT       0x00u 


/**************************************
*      Unsupported API Constants        
**************************************/

/*   Constants for SetBuffer() "bufMode" parameter  */   
#define ADC_DelSig_1_BUF_DIFF_MODE         0x00u  /* Differential mode */
#define ADC_DelSig_1_BUF_BYPASS_POS        0x04u  /* Bypass and power down positive channel */
#define ADC_DelSig_1_BUF_BYPASS_NEG        0x08u  /* Bypass and power down negative channel */
#define ADC_DelSig_1_BUF_RAIL_TO_RAIL      0x10u  /* Enables Rail-to-rail mode */
#define ADC_DelSig_1_BUF_FILTER_EN         0x20u  /* Output filter enable */
#define ADC_DelSig_1_BUF_LOW_PWR           0x40u  /* Enable  Low power mode */

/*   Constants for SetInputRange() "inputMode" parameter  */
#define ADC_DelSig_1_INMODE_VSSA_TO_VREF        0x00u 
#define ADC_DelSig_1_INMODE_VSSA_TO_2VREF       0x01u 
#define ADC_DelSig_1_INMODE_VSSA_TO_VDDA        0x02u 
#define ADC_DelSig_1_INMODE_VNEG_PM_VREF_DIFF   0x03u 
#define ADC_DelSig_1_INMODE_VNEG_PM_2VREF_DIFF  0x04u 

/*   Constants for SetBufferChop() "chopen" parameter  */
#define ADC_DelSig_1_BUF_CHOP_ENABLE       0x01u 
#define ADC_DelSig_1_BUF_CHOP_DISABLE      0x00u 

/*   Constants for SetBufferChop() "chopFreq" parameter  */
#define ADC_DelSig_1_BUF_CHOP_FREQ_FS2     0x00u 
#define ADC_DelSig_1_BUF_CHOP_FREQ_FS4     0x01u 
#define ADC_DelSig_1_BUF_CHOP_FREQ_FS8     0x02u 
#define ADC_DelSig_1_BUF_CHOP_FREQ_FS16    0x03u 
#define ADC_DelSig_1_BUF_CHOP_FREQ_FS32    0x04u 
#define ADC_DelSig_1_BUF_CHOP_FREQ_FS64    0x05u 
#define ADC_DelSig_1_BUF_CHOP_FREQ_FS128   0x06u 
#define ADC_DelSig_1_BUF_CHOP_FREQ_FS256   0x07u 



/* Constants for custom reference mode settings */
#define ADC_DelSig_1_REF_INTREF            0x80u 
#define ADC_DelSig_1_REF_REFMODE_MASK      0x07u 
#define ADC_DelSig_1_INTREF_MASK           0x07u 

#define ADC_DelSig_1_MIN_RES           8 
#define ADC_DelSig_1_MAX_RES           20 



/**************************************
*       Register Constants        
**************************************/


/******************************************/
/* DSM.CR0 Control Register 0 definitions */
/******************************************/

/* Bit Field  DSM_NONOV                   */
#define ADC_DelSig_1_DSM_NONOV_MASK    0x0Cu
#define ADC_DelSig_1_DSM_NONOV_LOW     0x00u
#define ADC_DelSig_1_DSM_NONOV_MED     0x04u
#define ADC_DelSig_1_DSM_NONOV_HIGH    0x08u
#define ADC_DelSig_1_DSM_NONOV_VHIGH   0x0Cu

/* Bit Field  DSM_QLEV                   */
#define ADC_DelSig_1_DSM_QLEV_MASK     0x03u
#define ADC_DelSig_1_DSM_QLEV_2        0x00u
#define ADC_DelSig_1_DSM_QLEV_3        0x01u
#define ADC_DelSig_1_DSM_QLEV_9        0x02u
#define ADC_DelSig_1_DSM_QLEV_9x       0x03u


/******************************************/
/* DSM.CR1 Control Register 1 definitions */
/******************************************/
#define ADC_DelSig_1_DSM_ODET_TH_MASK  0x1Fu
#define ADC_DelSig_1_DSM_ODEN          0x20u
#define ADC_DelSig_1_DSM_DPMODE        0x40u

/******************************************/
/* DSM.CR2 Control Register 2 definitions */
/******************************************/
/* Bit Field  DSM_FCHOP                   */
#define ADC_DelSig_1_DSM_FCHOP_MASK     0x07u
#define ADC_DelSig_1_DSM_FCHOP_DIV2     0x00u
#define ADC_DelSig_1_DSM_FCHOP_DIV4     0x01u
#define ADC_DelSig_1_DSM_FCHOP_DIV8     0x02u
#define ADC_DelSig_1_DSM_FCHOP_DIV16    0x03u
#define ADC_DelSig_1_DSM_FCHOP_DIV32    0x04u
#define ADC_DelSig_1_DSM_FCHOP_DIV64    0x05u
#define ADC_DelSig_1_DSM_FCHOP_DIV128   0x06u
#define ADC_DelSig_1_DSM_FCHOP_DIV256   0x07u

/* Bit Field  DSM_MOD_CHOP_EN                */
#define ADC_DelSig_1_DSM_MOD_CHOP_EN    0x08u

/* Bit Field  DSM_MX_RESET                   */
#define ADC_DelSig_1_DSM_MX_RESET       0x80u

/* Bit Field  DSM_RESET1_EN                  */
#define ADC_DelSig_1_DSM_RESET1_EN      0x10u

/* Bit Field  DSM_RESET2_EN                  */
#define ADC_DelSig_1_DSM_RESET2_EN      0x20u

/* Bit Field  DSM_RESET3_EN                  */
#define ADC_DelSig_1_DSM_RESET3_EN      0x40u

/******************************************/
/* DSM.CR3 Control Register 3 definitions */
/******************************************/
/* Bit Field  DSM_SELECT_MOD_BIT          */
#define ADC_DelSig_1_DSM_MODBITIN_MASK   0x0Fu
#define ADC_DelSig_1_DSM_MODBITIN_LUT0   0x00u
#define ADC_DelSig_1_DSM_MODBITIN_LUT1   0x01u
#define ADC_DelSig_1_DSM_MODBITIN_LUT2   0x02u
#define ADC_DelSig_1_DSM_MODBITIN_LUT3   0x03u
#define ADC_DelSig_1_DSM_MODBITIN_LUT4   0x04u
#define ADC_DelSig_1_DSM_MODBITIN_LUT5   0x05u
#define ADC_DelSig_1_DSM_MODBITIN_LUT6   0x06u
#define ADC_DelSig_1_DSM_MODBITIN_LUT7   0x07u
#define ADC_DelSig_1_DSM_MODBITIN_UDB    0x08u

/* Bit Field  DSM_MODBIT_EN                 */
#define ADC_DelSig_1_DSM_MODBIT_EN      0x10u

/* Bit Field  DSM_MX_DOUT                   */
#define ADC_DelSig_1_DSM_MX_DOUT_8BIT   0x00u
#define ADC_DelSig_1_DSM_MX_DOUT_2SCOMP 0x20u

/* Bit Field  DSM_MODBIT  TBD               */
#define ADC_DelSig_1_DSM_MODBIT         0x40u

/* Bit Field  DSM_SIGN                      */
#define ADC_DelSig_1_DSM_SIGN_NINV      0x00u
#define ADC_DelSig_1_DSM_SIGN_INV       0x80u


/******************************************/
/* DSM.CR4 Control Register 4 definitions */
/******************************************/
/* Bit Field  DSM_SELECT_FCAP_EN            */
#define ADC_DelSig_1_DSM_FCAP1_EN       0x80u
#define ADC_DelSig_1_DSM_FCAP1_DIS      0x00u

/* Bit Field  DSM_SELECT_FCAP1             */
#define ADC_DelSig_1_DSM_FCAP1_MASK     0x7Fu
#define ADC_DelSig_1_DSM_FCAP1_MIN      0x00u
#define ADC_DelSig_1_DSM_FCAP1_MAX      0x7Fu
#define ADC_DelSig_1_DSM_FCAP1_100FF    0x01u
#define ADC_DelSig_1_DSM_FCAP1_200FF    0x02u
#define ADC_DelSig_1_DSM_FCAP1_400FF    0x04u
#define ADC_DelSig_1_DSM_FCAP1_800FF    0x08u
#define ADC_DelSig_1_DSM_FCAP1_1600FF   0x10u
#define ADC_DelSig_1_DSM_FCAP1_3200FF   0x20u
#define ADC_DelSig_1_DSM_FCAP1_6400FF   0x40u

/******************************************/
/* DSM.CR5 Control Register 5 definitions */
/******************************************/
/* Bit Field  DSM_SELECT_IPCAP_EN            */
#define ADC_DelSig_1_DSM_IPCAP1_EN      0x80u
#define ADC_DelSig_1_DSM_IPCAP1_DIS     0x00u

/* Bit Field  DSM_SELECT_IPCAP1             */
#define ADC_DelSig_1_DSM_IPCAP1_MASK    0x7Fu
#define ADC_DelSig_1_DSM_IPCAP1_MIN     0x00u
#define ADC_DelSig_1_DSM_IPCAP1_MAX     0x7Fu
#define ADC_DelSig_1_DSM_IPCAP1_100FF   0x01u
#define ADC_DelSig_1_DSM_IPCAP1_200FF   0x02u
#define ADC_DelSig_1_DSM_IPCAP1_400FF   0x04u
#define ADC_DelSig_1_DSM_IPCAP1_800FF   0x08u
#define ADC_DelSig_1_DSM_IPCAP1_1600FF  0x10u
#define ADC_DelSig_1_DSM_IPCAP1_3200FF  0x20u
#define ADC_DelSig_1_DSM_IPCAP1_6400FF  0x40u


/******************************************/
/* DSM.CR6 Control Register 6 definitions */
/******************************************/
/* Bit Field  DSM_SELECT_DACCAP_EN            */
#define ADC_DelSig_1_DSM_DACCAP_EN      0x40u
#define ADC_DelSig_1_DSM_DACCAP_DIS     0x00u

/* Bit Field  DSM_SELECT_DACCAP             */
#define ADC_DelSig_1_DSM_DACCAP_MASK    0x3Fu
#define ADC_DelSig_1_DSM_DACCAP_MIN     0x00u
#define ADC_DelSig_1_DSM_DACCAP_MAX     0x3Fu
#define ADC_DelSig_1_DSM_DACCAP_96FF    0x01u
#define ADC_DelSig_1_DSM_DACCAP_192FF   0x02u
#define ADC_DelSig_1_DSM_DACCAP_400FF   0x04u
#define ADC_DelSig_1_DSM_DACCAP_800FF   0x08u
#define ADC_DelSig_1_DSM_DACCAP_1600FF  0x10u
#define ADC_DelSig_1_DSM_DACCAP_3200FF  0x20u


/******************************************/
/* DSM.CR7 Control Register 7 definitions */
/******************************************/
/* Bit Field  DSM_SELECT_RESCAP_EN            */
#define ADC_DelSig_1_DSM_RESCAP_EN      0x08u
#define ADC_DelSig_1_DSM_RESCAP_DIS     0x00u

/* Bit Field  DSM_SELECT_RESCAP             */
#define ADC_DelSig_1_DSM_RESCAP_MASK    0x07u
#define ADC_DelSig_1_DSM_RESCAP_MIN     0x00u
#define ADC_DelSig_1_DSM_RESCAP_MAX     0x07u
#define ADC_DelSig_1_DSM_RESCAP_12FF    0x00u
#define ADC_DelSig_1_DSM_RESCAP_24FF    0x01u
#define ADC_DelSig_1_DSM_RESCAP_36FF    0x02u
#define ADC_DelSig_1_DSM_RESCAP_48FF    0x03u
#define ADC_DelSig_1_DSM_RESCAP_60FF    0x04u
#define ADC_DelSig_1_DSM_RESCAP_72FF    0x05u
#define ADC_DelSig_1_DSM_RESCAP_84FF    0x06u
#define ADC_DelSig_1_DSM_RESCAP_96FF    0x07u

#define ADC_DelSig_1_DSM_FCAP2_DIS      0x00u
#define ADC_DelSig_1_DSM_FCAP2_EN       0x80u

#define ADC_DelSig_1_DSM_FCAP3_DIS      0x00u
#define ADC_DelSig_1_DSM_FCAP3_EN       0x40u

#define ADC_DelSig_1_DSM_IPCAP1OFFSET   0x20u
#define ADC_DelSig_1_DSM_FPCAP1OFFSET   0x10u


/******************************************/
/* DSM.CR8 Control Register 8 definitions */
/******************************************/
#define ADC_DelSig_1_DSM_IPCAP2_EN      0x80u

#define ADC_DelSig_1_DSM_IPCAP2_MASK    0x70u
#define ADC_DelSig_1_DSM_IPCAP2_0_FF    0x00u
#define ADC_DelSig_1_DSM_IPCAP2_50_FF   0x10u
#define ADC_DelSig_1_DSM_IPCAP2_100_FF  0x20u
#define ADC_DelSig_1_DSM_IPCAP2_150_FF  0x30u
#define ADC_DelSig_1_DSM_IPCAP2_200_FF  0x40u
#define ADC_DelSig_1_DSM_IPCAP2_250_FF  0x50u
#define ADC_DelSig_1_DSM_IPCAP2_300_FF  0x60u
#define ADC_DelSig_1_DSM_IPCAP2_350_FF  0x70u

#define ADC_DelSig_1_DSM_FCAP2_MASK     0x0Fu
#define ADC_DelSig_1_DSM_FCAP2_0_FF     0x00u
#define ADC_DelSig_1_DSM_FCAP2_50_FF    0x01u
#define ADC_DelSig_1_DSM_FCAP2_100_FF   0x02u
#define ADC_DelSig_1_DSM_FCAP2_150_FF   0x03u
#define ADC_DelSig_1_DSM_FCAP2_200_FF   0x04u
#define ADC_DelSig_1_DSM_FCAP2_250_FF   0x05u
#define ADC_DelSig_1_DSM_FCAP2_300_FF   0x06u
#define ADC_DelSig_1_DSM_FCAP2_350_FF   0x07u
#define ADC_DelSig_1_DSM_FCAP2_400_FF   0x08u
#define ADC_DelSig_1_DSM_FCAP2_450_FF   0x09u
#define ADC_DelSig_1_DSM_FCAP2_500_FF   0x0Au
#define ADC_DelSig_1_DSM_FCAP2_550_FF   0x0Bu
#define ADC_DelSig_1_DSM_FCAP2_600_FF   0x0Cu
#define ADC_DelSig_1_DSM_FCAP2_650_FF   0x0Du
#define ADC_DelSig_1_DSM_FCAP2_700_FF   0x0Eu
#define ADC_DelSig_1_DSM_FCAP2_750_FF   0x0Fu

/******************************************/
/* DSM.CR9 Control Register 9 definitions */
/******************************************/
#define ADC_DelSig_1_DSM_IPCAP3_EN      0x80u

#define ADC_DelSig_1_DSM_IPCAP3_MASK    0x70u
#define ADC_DelSig_1_DSM_IPCAP3_0_FF    0x00u
#define ADC_DelSig_1_DSM_IPCAP3_50_FF   0x10u
#define ADC_DelSig_1_DSM_IPCAP3_100_FF  0x20u
#define ADC_DelSig_1_DSM_IPCAP3_150_FF  0x30u
#define ADC_DelSig_1_DSM_IPCAP3_200_FF  0x40u
#define ADC_DelSig_1_DSM_IPCAP3_250_FF  0x50u
#define ADC_DelSig_1_DSM_IPCAP3_300_FF  0x60u
#define ADC_DelSig_1_DSM_IPCAP3_350_FF  0x70u

#define ADC_DelSig_1_DSM_FCAP3_MASK     0x0Fu
#define ADC_DelSig_1_DSM_FCAP3_0_FF     0x00u
#define ADC_DelSig_1_DSM_FCAP3_50_FF    0x01u
#define ADC_DelSig_1_DSM_FCAP3_100_FF   0x02u
#define ADC_DelSig_1_DSM_FCAP3_150_FF   0x03u
#define ADC_DelSig_1_DSM_FCAP3_200_FF   0x04u
#define ADC_DelSig_1_DSM_FCAP3_250_FF   0x05u
#define ADC_DelSig_1_DSM_FCAP3_300_FF   0x06u
#define ADC_DelSig_1_DSM_FCAP3_350_FF   0x07u
#define ADC_DelSig_1_DSM_FCAP3_400_FF   0x08u
#define ADC_DelSig_1_DSM_FCAP3_450_FF   0x09u
#define ADC_DelSig_1_DSM_FCAP3_500_FF   0x0Au
#define ADC_DelSig_1_DSM_FCAP3_550_FF   0x0Bu
#define ADC_DelSig_1_DSM_FCAP3_600_FF   0x0Cu
#define ADC_DelSig_1_DSM_FCAP3_650_FF   0x0Du
#define ADC_DelSig_1_DSM_FCAP3_700_FF   0x0Eu
#define ADC_DelSig_1_DSM_FCAP3_750_FF   0x0Fu


/********************************************/
/* DSM.CR10 Control Register 10 definitions */
/********************************************/
#define ADC_DelSig_1_DSM_SUMCAP1_EN      0x80u
#define ADC_DelSig_1_DSM_SUMCAP2_EN      0x08u

#define ADC_DelSig_1_DSM_SUMCAP1_MASK    0x70u
#define ADC_DelSig_1_DSM_SUMCAP1_0_FF    0x00u
#define ADC_DelSig_1_DSM_SUMCAP1_50_FF   0x10u
#define ADC_DelSig_1_DSM_SUMCAP1_100_FF  0x20u
#define ADC_DelSig_1_DSM_SUMCAP1_150_FF  0x30u
#define ADC_DelSig_1_DSM_SUMCAP1_200_FF  0x40u
#define ADC_DelSig_1_DSM_SUMCAP1_250_FF  0x50u
#define ADC_DelSig_1_DSM_SUMCAP1_300_FF  0x60u
#define ADC_DelSig_1_DSM_SUMCAP1_350_FF  0x70u

#define ADC_DelSig_1_DSM_SUMCAP2_MASK    0x07u
#define ADC_DelSig_1_DSM_SUMCAP2_0_FF    0x00u
#define ADC_DelSig_1_DSM_SUMCAP2_50_FF   0x01u
#define ADC_DelSig_1_DSM_SUMCAP2_100_FF  0x02u
#define ADC_DelSig_1_DSM_SUMCAP2_150_FF  0x03u
#define ADC_DelSig_1_DSM_SUMCAP2_200_FF  0x04u
#define ADC_DelSig_1_DSM_SUMCAP2_250_FF  0x05u
#define ADC_DelSig_1_DSM_SUMCAP2_300_FF  0x06u
#define ADC_DelSig_1_DSM_SUMCAP2_350_FF  0x07u

/********************************************/
/* DSM.CR11 Control Register 11 definitions */
/********************************************/
#define ADC_DelSig_1_DSM_SUMCAP3_EN       0x08u

#define ADC_DelSig_1_DSM_SUMCAP3_MASK     0x70u
#define ADC_DelSig_1_DSM_SUMCAP3_0_FF     0x00u
#define ADC_DelSig_1_DSM_SUMCAP3_50_FF    0x10u
#define ADC_DelSig_1_DSM_SUMCAP3_100_FF   0x20u
#define ADC_DelSig_1_DSM_SUMCAP3_150_FF   0x30u
#define ADC_DelSig_1_DSM_SUMCAP3_200_FF   0x40u
#define ADC_DelSig_1_DSM_SUMCAP3_250_FF   0x50u
#define ADC_DelSig_1_DSM_SUMCAP3_300_FF   0x60u
#define ADC_DelSig_1_DSM_SUMCAP3_350_FF   0x70u

#define ADC_DelSig_1_DSM_SUMCAPFB_MASK    0x07u
#define ADC_DelSig_1_DSM_SUMCAPFB_0_FF    0x00u
#define ADC_DelSig_1_DSM_SUMCAPFB_50_FF   0x01u
#define ADC_DelSig_1_DSM_SUMCAPFB_100_FF  0x02u
#define ADC_DelSig_1_DSM_SUMCAPFB_150_FF  0x03u
#define ADC_DelSig_1_DSM_SUMCAPFB_200_FF  0x04u
#define ADC_DelSig_1_DSM_SUMCAPFB_250_FF  0x05u
#define ADC_DelSig_1_DSM_SUMCAPFB_300_FF  0x06u
#define ADC_DelSig_1_DSM_SUMCAPFB_350_FF  0x07u
#define ADC_DelSig_1_DSM_SUMCAPFB_400_FF  0x08u
#define ADC_DelSig_1_DSM_SUMCAPFB_450_FF  0x09u
#define ADC_DelSig_1_DSM_SUMCAPFB_500_FF  0x0Au
#define ADC_DelSig_1_DSM_SUMCAPFB_550_FF  0x0Bu
#define ADC_DelSig_1_DSM_SUMCAPFB_600_FF  0x0Cu
#define ADC_DelSig_1_DSM_SUMCAPFB_650_FF  0x0Du
#define ADC_DelSig_1_DSM_SUMCAPFB_700_FF  0x0Eu
#define ADC_DelSig_1_DSM_SUMCAPFB_750_FF  0x0Fu

/********************************************/
/* DSM.CR12 Control Register 12 definitions */
/********************************************/
#define ADC_DelSig_1_DSM_SUMCAPFB_EN      0x40u
#define ADC_DelSig_1_DSM_SUMCAPIN_EN      0x20u

#define ADC_DelSig_1_DSM_SUMCAPIN_MASK    0x1Fu
#define ADC_DelSig_1_DSM_SUMCAPIN_0_FF    0x00u
#define ADC_DelSig_1_DSM_SUMCAPIN_50_FF   0x01u
#define ADC_DelSig_1_DSM_SUMCAPIN_100_FF  0x02u
#define ADC_DelSig_1_DSM_SUMCAPIN_150_FF  0x03u
#define ADC_DelSig_1_DSM_SUMCAPIN_200_FF  0x04u
#define ADC_DelSig_1_DSM_SUMCAPIN_250_FF  0x05u
#define ADC_DelSig_1_DSM_SUMCAPIN_300_FF  0x06u
#define ADC_DelSig_1_DSM_SUMCAPIN_350_FF  0x07u
#define ADC_DelSig_1_DSM_SUMCAPIN_400_FF  0x08u
#define ADC_DelSig_1_DSM_SUMCAPIN_450_FF  0x09u
#define ADC_DelSig_1_DSM_SUMCAPIN_500_FF  0x0Au
#define ADC_DelSig_1_DSM_SUMCAPIN_550_FF  0x0Bu
#define ADC_DelSig_1_DSM_SUMCAPIN_600_FF  0x0Cu
#define ADC_DelSig_1_DSM_SUMCAPIN_650_FF  0x0Du
#define ADC_DelSig_1_DSM_SUMCAPIN_700_FF  0x0Eu
#define ADC_DelSig_1_DSM_SUMCAPIN_750_FF  0x0Fu
#define ADC_DelSig_1_DSM_SUMCAPIN_800_FF  0x10u
#define ADC_DelSig_1_DSM_SUMCAPIN_850_FF  0x11u
#define ADC_DelSig_1_DSM_SUMCAPIN_900_FF  0x12u
#define ADC_DelSig_1_DSM_SUMCAPIN_950_FF  0x13u
#define ADC_DelSig_1_DSM_SUMCAPIN_1000_FF 0x14u
#define ADC_DelSig_1_DSM_SUMCAPIN_1050_FF 0x15u
#define ADC_DelSig_1_DSM_SUMCAPIN_1100_FF 0x16u
#define ADC_DelSig_1_DSM_SUMCAPIN_1150_FF 0x17u
#define ADC_DelSig_1_DSM_SUMCAPIN_1200_FF 0x18u
#define ADC_DelSig_1_DSM_SUMCAPIN_1250_FF 0x19u
#define ADC_DelSig_1_DSM_SUMCAPIN_1300_FF 0x1Au
#define ADC_DelSig_1_DSM_SUMCAPIN_1350_FF 0x1Bu
#define ADC_DelSig_1_DSM_SUMCAPIN_1400_FF 0x1Cu
#define ADC_DelSig_1_DSM_SUMCAPIN_1450_FF 0x1Du
#define ADC_DelSig_1_DSM_SUMCAPIN_1500_FF 0x1Eu
#define ADC_DelSig_1_DSM_SUMCAPIN_1550_FF 0x15u


/********************************************/
/* DSM.CR13 Control Register 13 definitions */
/********************************************/
#define ADC_DelSig_1_DSM_CR13_RSVD        0xFFu

/********************************************/
/* DSM.CR14 Control Register 14 definitions */
/********************************************/

/* Bit Field  DSM_POWER1                    */
#define ADC_DelSig_1_DSM_POWER1_MASK      0x07u

#define ADC_DelSig_1_DSM_POWER1_0         0x00u
#define ADC_DelSig_1_DSM_POWER1_1         0x01u
#define ADC_DelSig_1_DSM_POWER1_2         0x02u
#define ADC_DelSig_1_DSM_POWER1_3         0x03u
#define ADC_DelSig_1_DSM_POWER1_4         0x04u
#define ADC_DelSig_1_DSM_POWER1_5         0x05u
#define ADC_DelSig_1_DSM_POWER1_6         0x06u
#define ADC_DelSig_1_DSM_POWER1_7         0x07u
  
#define ADC_DelSig_1_DSM_POWER1_44UA      0x00u
#define ADC_DelSig_1_DSM_POWER1_123UA     0x01u
#define ADC_DelSig_1_DSM_POWER1_492UA     0x02u
#define ADC_DelSig_1_DSM_POWER1_750UA     0x03u
#define ADC_DelSig_1_DSM_POWER1_1MA       0x04u

/* Bit Field  DSM_OPAMP1_BW                 */
#define ADC_DelSig_1_DSM_OPAMP1_BW_MASK   0xF0u
#define ADC_DelSig_1_DSM_OPAMP1_BW_0      0x00u
#define ADC_DelSig_1_DSM_OPAMP1_BW_1      0x10u
#define ADC_DelSig_1_DSM_OPAMP1_BW_2      0x20u
#define ADC_DelSig_1_DSM_OPAMP1_BW_3      0x30u
#define ADC_DelSig_1_DSM_OPAMP1_BW_4      0x40u
#define ADC_DelSig_1_DSM_OPAMP1_BW_5      0x50u
#define ADC_DelSig_1_DSM_OPAMP1_BW_6      0x60u
#define ADC_DelSig_1_DSM_OPAMP1_BW_7      0x70u
#define ADC_DelSig_1_DSM_OPAMP1_BW_8      0x80u
#define ADC_DelSig_1_DSM_OPAMP1_BW_9      0x90u
#define ADC_DelSig_1_DSM_OPAMP1_BW_A      0xA0u
#define ADC_DelSig_1_DSM_OPAMP1_BW_B      0xB0u
#define ADC_DelSig_1_DSM_OPAMP1_BW_C      0xC0u
#define ADC_DelSig_1_DSM_OPAMP1_BW_D      0xD0u
#define ADC_DelSig_1_DSM_OPAMP1_BW_E      0xE0u
#define ADC_DelSig_1_DSM_OPAMP1_BW_F      0xF0u

/********************************************/
/* DSM.CR15 Control Register 15 definitions */
/********************************************/

/* Bit Field  DSM_POWER2_3                  */
#define ADC_DelSig_1_DSM_POWER2_3_MASK   0x07u

#define ADC_DelSig_1_DSM_POWER2_3_LOW    0x00u
#define ADC_DelSig_1_DSM_POWER2_3_MED    0x01u
#define ADC_DelSig_1_DSM_POWER2_3_HIGH   0x02u
#define ADC_DelSig_1_DSM_POWER2_3_IP5X   0x03u
#define ADC_DelSig_1_DSM_POWER2_3_2X     0x04u
#define ADC_DelSig_1_DSM_POWER2_3_HIGH_5 0x05u
#define ADC_DelSig_1_DSM_POWER2_3_HIGH_6 0x06u
#define ADC_DelSig_1_DSM_POWER2_3_HIGH_7 0x07u

/* Bit Field  DSM_POWER_COMP                */
#define ADC_DelSig_1_DSM_POWER_COMP_MASK 0x30u

#define ADC_DelSig_1_DSM_POWER_VERYLOW   0x00u
#define ADC_DelSig_1_DSM_POWER_NORMAL    0x10u
#define ADC_DelSig_1_DSM_POWER_6MHZ      0x20u
#define ADC_DelSig_1_DSM_POWER_12MHZ     0x30u

/********************************************/
/* DSM.CR16 Control Register 16 definitions */
/********************************************/

/* Bit Field  DSM_POWER_SUM                 */
#define ADC_DelSig_1_DSM_POWER_SUM_MASK   0x70u

#define ADC_DelSig_1_DSM_POWER_SUM_LOW    0x00u
#define ADC_DelSig_1_DSM_POWER_SUM_MED    0x10u
#define ADC_DelSig_1_DSM_POWER_SUM_HIGH   0x20u
#define ADC_DelSig_1_DSM_POWER_SUM_IP5X   0x30u
#define ADC_DelSig_1_DSM_POWER_SUM_2X     0x40u
#define ADC_DelSig_1_DSM_POWER_SUM_HIGH_5 0x50u
#define ADC_DelSig_1_DSM_POWER_SUM_HIGH_6 0x60u
#define ADC_DelSig_1_DSM_POWER_SUM_HIGH_7 0x70u

#define ADC_DelSig_1_DSM_CP_ENABLE         0x08u
#define ADC_DelSig_1_DSM_CP_PWRCTL_MASK    0x07u
#define ADC_DelSig_1_DSM_CP_PWRCTL_DEFAULT 0x0Au

/********************************************/
/* DSM.CR17 Control Register 17 definitions */
/********************************************/

/* Bit Field  DSM_EN_BUF                    */
#define ADC_DelSig_1_DSM_EN_BUF_VREF        0x01u
#define ADC_DelSig_1_DSM_EN_BUF_VCM         0x02u

#define ADC_DelSig_1_DSM_PWR_CTRL_VREF_MASK 0x0Cu
#define ADC_DelSig_1_DSM_PWR_CTRL_VREF_0    0x00u
#define ADC_DelSig_1_DSM_PWR_CTRL_VREF_1    0x04u
#define ADC_DelSig_1_DSM_PWR_CTRL_VREF_2    0x08u
#define ADC_DelSig_1_DSM_PWR_CTRL_VREF_3    0x0Cu

#define ADC_DelSig_1_DSM_PWR_CTRL_VCM_MASK  0x30u
#define ADC_DelSig_1_DSM_PWR_CTRL_VCM_0     0x00u
#define ADC_DelSig_1_DSM_PWR_CTRL_VCM_1     0x10u
#define ADC_DelSig_1_DSM_PWR_CTRL_VCM_2     0x20u
#define ADC_DelSig_1_DSM_PWR_CTRL_VCM_3     0x30u

#define ADC_DelSig_1_DSM_PWR_CTRL_VREF_INN_MASK  0xC0u
#define ADC_DelSig_1_DSM_PWR_CTRL_VREF_INN_0     0x00u
#define ADC_DelSig_1_DSM_PWR_CTRL_VREF_INN_1     0x40u
#define ADC_DelSig_1_DSM_PWR_CTRL_VREF_INN_2     0x80u
#define ADC_DelSig_1_DSM_PWR_CTRL_VREF_INN_3     0xC0u

/*********************************************/
/* DSM.REF0 Reference Register 0 definitions */
/*********************************************/

#define ADC_DelSig_1_DSM_REFMUX_MASK     0x07u
#define ADC_DelSig_1_DSM_REFMUX_NONE     0x00u
#define ADC_DelSig_1_DSM_REFMUX_UVCM     0x01u
#define ADC_DelSig_1_DSM_REFMUX_VDA_4    0x02u
#define ADC_DelSig_1_DSM_REFMUX_VDAC0    0x03u
#define ADC_DelSig_1_DSM_REFMUX_1_024V   0x04u
#define ADC_DelSig_1_DSM_REFMUX_1_20V    0x05u

#define ADC_DelSig_1_DSM_EN_BUF_VREF_INN 0x08u
#define ADC_DelSig_1_DSM_VREF_RES_DIV_EN 0x10u
#define ADC_DelSig_1_DSM_VCM_RES_DIV_EN  0x20u
#define ADC_DelSig_1_DSM_VCMSEL_MASK     0xC0u
#define ADC_DelSig_1_DSM_VCMSEL_NOSEL    0x00u
#define ADC_DelSig_1_DSM_VCMSEL_0_8V     0x40u
#define ADC_DelSig_1_DSM_VCMSEL_0_7V     0x80u
#define ADC_DelSig_1_DSM_VCMSEL_VPWRA_2  0xC0u

/*********************************************/
/* DSM.REF1 Reference Register 1 definitions */
/*********************************************/
#define ADC_DelSig_1_DSM_REF1_MASK     0xFFu

/*********************************************/
/* DSM.REF2 Reference Register 2 definitions */
/*********************************************/
#define ADC_DelSig_1_DSM_REF2_MASK     0xFFu
#define ADC_DelSig_1_DSM_REF2_S0_EN    0x01u
#define ADC_DelSig_1_DSM_REF2_S1_EN    0x02u
#define ADC_DelSig_1_DSM_REF2_S2_EN    0x04u
#define ADC_DelSig_1_DSM_REF2_S3_EN    0x08u
#define ADC_DelSig_1_DSM_REF2_S4_EN    0x10u
#define ADC_DelSig_1_DSM_REF2_S5_EN    0x20u
#define ADC_DelSig_1_DSM_REF2_S6_EN    0x40u
#define ADC_DelSig_1_DSM_REF2_S7_EN    0x80u

/*********************************************/
/* DSM.REF3 Reference Register 3 definitions */
/*********************************************/
#define ADC_DelSig_1_DSM_REF3_MASK     0xFFu
#define ADC_DelSig_1_DSM_REF2_S8_EN    0x01u
#define ADC_DelSig_1_DSM_REF2_S9_EN    0x02u
#define ADC_DelSig_1_DSM_REF2_S10_EN   0x04u
#define ADC_DelSig_1_DSM_REF2_S11_EN   0x08u
#define ADC_DelSig_1_DSM_REF2_S12_EN   0x10u
#define ADC_DelSig_1_DSM_REF2_S13_EN   0x20u


/************************************************/
/* DSM.DEM0 Dynamic Element Matching Register 0 */
/************************************************/
#define ADC_DelSig_1_DSM_EN_SCRAMBLER0 0x01u
#define ADC_DelSig_1_DSM_EN_SCRAMBLER1 0x02u
#define ADC_DelSig_1_DSM_EN_DEM        0x04u
#define ADC_DelSig_1_DSM_ADC_TEST_EN   0x08u
#define ADC_DelSig_1_DSM_DEMTEST_SRC   0x10u

/************************************************/
/* DSM.DEM1 Dynamic Element Matching Register 1 */
/************************************************/
#define ADC_DelSig_1_DSM_DEM1_MASK     0xFF


/***********************************************/
/* DSM.BUF0 Buffer Register 0                  */
/***********************************************/
#define ADC_DelSig_1_DSM_ENABLE_P      0x01u
#define ADC_DelSig_1_DSM_BYPASS_P      0x02u
#define ADC_DelSig_1_DSM_RAIL_RAIL_EN  0x04u

#define ADC_DelSig_1_DSM_BUFSEL        0x08u
#define ADC_DelSig_1_DSM_BUFSEL_A      0x00u
#define ADC_DelSig_1_DSM_BUFSEL_B      0x08u


/***********************************************/
/* DSM.BUF1 Buffer Register 1                  */
/***********************************************/
#define ADC_DelSig_1_DSM_ENABLE_N      0x01u
#define ADC_DelSig_1_DSM_BYPASS_N      0x02u
#define ADC_DelSig_1_DSM_GAIN_MASK     0x0Cu

/***********************************************/
/* DSM.BUF2 Buffer Register 2                  */
/***********************************************/
#define ADC_DelSig_1_DSM_LOWPOWER_EN   0x01u
#define ADC_DelSig_1_DSM_ADD_EXTRA_RC  0x02u

/***********************************************/
/* DSM.BUF3 Buffer Register 3                  */
/***********************************************/
#define ADC_DelSig_1_DSM_BUF_CHOP_EN     0x08u

#define ADC_DelSig_1_DSM_BUF_FCHOP_MASK  0x07u
#define ADC_DelSig_1_DSM_BUF_FCHOP_FS2   0x00u
#define ADC_DelSig_1_DSM_BUF_FCHOP_FS4   0x01u
#define ADC_DelSig_1_DSM_BUF_FCHOP_FS8   0x02u
#define ADC_DelSig_1_DSM_BUF_FCHOP_FS16  0x03u
#define ADC_DelSig_1_DSM_BUF_FCHOP_FS32  0x04u
#define ADC_DelSig_1_DSM_BUF_FCHOP_FS64  0x05u
#define ADC_DelSig_1_DSM_BUF_FCHOP_FS128 0x06u
#define ADC_DelSig_1_DSM_BUF_FCHOP_FS256 0x07u

/***********************************************/
/* DSM.MISC Delta Sigma Misc Register          */
/***********************************************/
#define ADC_DelSig_1_DSM_SEL_ICLK_CP   0x01u

/************************************************/
/* DSM.CLK Delta Sigma Clock selection Register */
/************************************************/
#define ADC_DelSig_1_DSM_CLK_MX_CLK_MSK  0x07u
#define ADC_DelSig_1_DSM_CLK_CLK_EN      0x08u
#define ADC_DelSig_1_DSM_CLK_BYPASS_SYNC 0x10u


/***********************************************/
/* DSM.OUT0 Output Register 0                  */
/***********************************************/
#define ADC_DelSig_1_DSM_DOUT0           0xFFu


/***********************************************/
/* DSM.OUT1 Output Register 1                  */
/***********************************************/
#define ADC_DelSig_1_DSM_DOUT2SCOMP_MASK 0x0Fu
#define ADC_DelSig_1_DSM_OVDFLAG         0x10u
#define ADC_DelSig_1_DSM_OVDCAUSE        0x20u


/***********************************************/
/*          Decimator                          */
/***********************************************/


/***********************************************/
/* DEC.CR Control Register 0                   */
/***********************************************/
#define ADC_DelSig_1_DEC_SAT_EN          0x80u /* Enable post process offset correction */
#define ADC_DelSig_1_DEC_FIR_EN          0x40u /* Post process FIR enable  */
#define ADC_DelSig_1_DEC_OCOR_EN         0x20u /* Offest correction enable */
#define ADC_DelSig_1_DEC_GCOR_EN         0x10u /* Enable gain correction feature */

#define ADC_DelSig_1_MODE_MASK           0x0Cu /* Conversion Mode */
#define ADC_DelSig_1_MODE_SINGLE_SAMPLE  0x00u
#define ADC_DelSig_1_MODE_FAST_FILTER    0x04u
#define ADC_DelSig_1_MODE_CONTINUOUS     0x08u
#define ADC_DelSig_1_MODE_FAST_FIR       0x0Cu

#define ADC_DelSig_1_DEC_XSTART_EN       0x02u /* Enables external start signal */
#define ADC_DelSig_1_DEC_START_CONV      0x01u /* A write to this bit starts a conversion */


/***********************************************/
/* DEC.SR Status and Control Register 0        */
/***********************************************/
#define ADC_DelSig_1_DEC_CORECLK_DISABLE 0x20u /* Controls gating of the Core clock */
#define ADC_DelSig_1_DEC_INTR_PULSE      0x10u /* Controls interrupt mode */ 
#define ADC_DelSig_1_DEC_OUT_ALIGN       0x08u /* Controls 8-bit shift of SAMP registers */
#define ADC_DelSig_1_DEC_INTR_CLEAR      0x04u /* A write to this bit clears bit0 */
#define ADC_DelSig_1_DEC_INTR_MASK       0x02u /* Controls the generation of the conversion comp. INTR */
#define ADC_DelSig_1_DEC_CONV_DONE       0x01u /* Bit set if conversion has completed  */

/***********************************************/
/* DEC.SHIFT1 Decimator Input Shift Register 1 */
/***********************************************/
#define ADC_DelSig_1_DEC_SHIFT1_MASK     0x1Fu /* Input shift1 control */

/***********************************************/
/* DEC.SHIFT2 Decimator Input Shift Register 2 */
/***********************************************/
#define ADC_DelSig_1_DEC_SHIFT2_MASK     0x0Fu /* Input shift2 control */

/****************************************************************/
/* DEC.DR2 Decimator Decimation Rate of FIR Filter Low Register */
/****************************************************************/
#define ADC_DelSig_1_DEC_DR2_MASK        0xFFu 

/******************************************************************/
/* DEC.DR2H Decimator Decimation Rate of FIR Filter High Register */
/******************************************************************/
#define ADC_DelSig_1_DEC_DR2H_MASK       0x03u 

/***********************************************/
/* DEC.COHR Decimator Coherency Register       */
/***********************************************/
#define ADC_DelSig_1_DEC_GCOR_KEY_MASK   0x30u 
#define ADC_DelSig_1_DEC_GCOR_KEY_OFF    0x00u 
#define ADC_DelSig_1_DEC_GCOR_KEY_LOW    0x10u 
#define ADC_DelSig_1_DEC_GCOR_KEY_MID    0x20u 
#define ADC_DelSig_1_DEC_GCOR_KEY_HIGH   0x30u 

#define ADC_DelSig_1_DEC_OCOR_KEY_MASK   0x0Cu
#define ADC_DelSig_1_DEC_OCOR_KEY_OFF    0x00u 
#define ADC_DelSig_1_DEC_OCOR_KEY_LOW    0x04u 
#define ADC_DelSig_1_DEC_OCOR_KEY_MID    0x08u 
#define ADC_DelSig_1_DEC_OCOR_KEY_HIGH   0x0Cu 

#define ADC_DelSig_1_DEC_SAMP_KEY_MASK   0x03u 
#define ADC_DelSig_1_DEC_SAMP_KEY_OFF    0x00u 
#define ADC_DelSig_1_DEC_SAMP_KEY_LOW    0x01u 
#define ADC_DelSig_1_DEC_SAMP_KEY_MID    0x02u 
#define ADC_DelSig_1_DEC_SAMP_KEY_HIGH   0x03u 

/* PM_ACT_CFG (Active Power Mode CFG Register)     */ 
#define ADC_DelSig_1_ACT_PWR_DEC_EN   ADC_DelSig_1_DEC__PM_ACT_MSK /* Power enable mask */
#define ADC_DelSig_1_ACT_PWR_DSM_EN   0x01u /* Power enable mask */

#if(ADC_DelSig_1_DEFAULT_INTERNAL_CLK)
#define ADC_DelSig_1_ACT_PWR_CLK_EN   ADC_DelSig_1_theACLK__PM_ACT_MSK /* Power enable mask */
#endif

/***********************************************/
/* DSM.SW3 DSM Analog Routing Register 3       */
/***********************************************/
#define ADC_DelSig_1_DSM_VP_VSSA       0x04u 
#define ADC_DelSig_1_DSM_VN_AMX        0x10u 
#define ADC_DelSig_1_DSM_VN_VREF       0x20u 
#define ADC_DelSig_1_DSM_VN_VSSA       0x40u 
#define ADC_DelSig_1_DSM_VN_REF_MASK   0x60u 


/***********************************************/
/* ANIF.PUMP.CR1 Pump Configuration Register 1 */
/***********************************************/
#define ADC_DelSig_1_PUMP_CR1  (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

#define ADC_DelSig_1_PUMP_CR1_CLKSEL  0x04
#define ADC_DelSig_1_PUMP_CR1_FORCE   0x02
#define ADC_DelSig_1_PUMP_CR1_AUTO    0x01


/***************************************
*              Registers        
***************************************/


/* Decimator (DEC) Registers */
#define ADC_DelSig_1_DEC_CR     (* (reg8 *) ADC_DelSig_1_DEC__CR )
#define ADC_DelSig_1_DEC_SR     (* (reg8 *) ADC_DelSig_1_DEC__SR )
#define ADC_DelSig_1_DEC_SHIFT1 (* (reg8 *) ADC_DelSig_1_DEC__SHIFT1 )
#define ADC_DelSig_1_DEC_SHIFT2 (* (reg8 *) ADC_DelSig_1_DEC__SHIFT2 )

#define ADC_DelSig_1_DEC_DR2    (* (reg8 *) ADC_DelSig_1_DEC__DR2 )
#define ADC_DelSig_1_DEC_DR2H   (* (reg8 *) ADC_DelSig_1_DEC__DR2H )
#define ADC_DelSig_1_DEC_DR1    (* (reg8 *) ADC_DelSig_1_DEC__DR1 )
#define ADC_DelSig_1_DEC_OCOR   (* (reg8 *) ADC_DelSig_1_DEC__OCOR )
#define ADC_DelSig_1_DEC_OCORM  (* (reg8 *) ADC_DelSig_1_DEC__OCORM )
#define ADC_DelSig_1_DEC_OCORH  (* (reg8 *) ADC_DelSig_1_DEC__OCORH )
#define ADC_DelSig_1_DEC_GVAL   (* (reg8 *) ADC_DelSig_1_DEC__GVAL )
#define ADC_DelSig_1_DEC_GCOR   (* (reg8 *) ADC_DelSig_1_DEC__GCOR )
#define ADC_DelSig_1_DEC_GCORH  (* (reg8 *) ADC_DelSig_1_DEC__GCORH )
#define ADC_DelSig_1_DEC_SAMP   (* (reg8 *) ADC_DelSig_1_DEC__OUTSAMP )
#define ADC_DelSig_1_DEC_SAMPM  (* (reg8 *) ADC_DelSig_1_DEC__OUTSAMPM )
#define ADC_DelSig_1_DEC_SAMPH  (* (reg8 *) ADC_DelSig_1_DEC__OUTSAMPH )
#define ADC_DelSig_1_DEC_COHER  (* (reg8 *) ADC_DelSig_1_DEC__COHER )
#define ADC_DelSig_1_PWRMGR_DEC (* (reg8 *) ADC_DelSig_1_DEC__PM_ACT_CFG )     /* Decimator Power manager Reg */

/* Delta Sigma Modulator (DSM) Registers */  
#define ADC_DelSig_1_DSM_CR0    (* (reg8 *) ADC_DelSig_1_DSM__CR0 )
#define ADC_DelSig_1_DSM_CR1    (* (reg8 *) ADC_DelSig_1_DSM__CR1 )
#define ADC_DelSig_1_DSM_CR2    (* (reg8 *) ADC_DelSig_1_DSM__CR2 )
#define ADC_DelSig_1_DSM_CR3    (* (reg8 *) ADC_DelSig_1_DSM__CR3 )
#define ADC_DelSig_1_DSM_CR4    (* (reg8 *) ADC_DelSig_1_DSM__CR4 )
#define ADC_DelSig_1_DSM_CR5    (* (reg8 *) ADC_DelSig_1_DSM__CR5 )
#define ADC_DelSig_1_DSM_CR6    (* (reg8 *) ADC_DelSig_1_DSM__CR6 )
#define ADC_DelSig_1_DSM_CR7    (* (reg8 *) ADC_DelSig_1_DSM__CR7 )
#define ADC_DelSig_1_DSM_CR8    (* (reg8 *) ADC_DelSig_1_DSM__CR8 )
#define ADC_DelSig_1_DSM_CR9    (* (reg8 *) ADC_DelSig_1_DSM__CR9 )
#define ADC_DelSig_1_DSM_CR10   (* (reg8 *) ADC_DelSig_1_DSM__CR10 )
#define ADC_DelSig_1_DSM_CR11   (* (reg8 *) ADC_DelSig_1_DSM__CR11 )
#define ADC_DelSig_1_DSM_CR12   (* (reg8 *) ADC_DelSig_1_DSM__CR12 )
#define ADC_DelSig_1_DSM_CR13   (* (reg8 *) ADC_DelSig_1_DSM__CR13 )
#define ADC_DelSig_1_DSM_CR14   (* (reg8 *) ADC_DelSig_1_DSM__CR14 )
#define ADC_DelSig_1_DSM_CR15   (* (reg8 *) ADC_DelSig_1_DSM__CR15 )
#define ADC_DelSig_1_DSM_CR16   (* (reg8 *) ADC_DelSig_1_DSM__CR16 )
#define ADC_DelSig_1_DSM_CR17   (* (reg8 *) ADC_DelSig_1_DSM__CR17 )
#define ADC_DelSig_1_DSM_REF0   (* (reg8 *) ADC_DelSig_1_DSM__REF0 )
#define ADC_DelSig_1_DSM_REF1   (* (reg8 *) ADC_DelSig_1_DSM__REF1 )
#define ADC_DelSig_1_DSM_REF2   (* (reg8 *) ADC_DelSig_1_DSM__REF2 )
#define ADC_DelSig_1_DSM_REF3   (* (reg8 *) ADC_DelSig_1_DSM__REF3 )
#define ADC_DelSig_1_DSM_DEM0   (* (reg8 *) ADC_DelSig_1_DSM__DEM0 )
#define ADC_DelSig_1_DSM_DEM1   (* (reg8 *) ADC_DelSig_1_DSM__DEM1 )
#define ADC_DelSig_1_DSM_MISC   (* (reg8 *) ADC_DelSig_1_DSM__MISC )
#define ADC_DelSig_1_DSM_CLK    (* (reg8 *) ADC_DelSig_1_DSM__CLK )
#define ADC_DelSig_1_DSM_TST0   (* (reg8 *) ADC_DelSig_1_DSM__TST0 )
#define ADC_DelSig_1_DSM_TST1   (* (reg8 *) ADC_DelSig_1_DSM__TST1 )
#define ADC_DelSig_1_DSM_BUF0   (* (reg8 *) ADC_DelSig_1_DSM__BUF0 )
#define ADC_DelSig_1_DSM_BUF1   (* (reg8 *) ADC_DelSig_1_DSM__BUF1 )
#define ADC_DelSig_1_DSM_BUF2   (* (reg8 *) ADC_DelSig_1_DSM__BUF2 )
#define ADC_DelSig_1_DSM_BUF3   (* (reg8 *) ADC_DelSig_1_DSM__BUF3 )
#define ADC_DelSig_1_DSM_OUT0   (* (reg8 *) ADC_DelSig_1_DSM__OUT0 )
#define ADC_DelSig_1_DSM_OUT1   (* (reg8 *) ADC_DelSig_1_DSM__OUT1 )
#define ADC_DelSig_1_DSM_SW0    (* (reg8 *) ADC_DelSig_1_DSM__SW0 )
#define ADC_DelSig_1_DSM_SW2    (* (reg8 *) ADC_DelSig_1_DSM__SW2 )
#define ADC_DelSig_1_DSM_SW3    (* (reg8 *) ADC_DelSig_1_DSM__SW3 )
#define ADC_DelSig_1_DSM_SW4    (* (reg8 *) ADC_DelSig_1_DSM__SW4 )
#define ADC_DelSig_1_DSM_SW6    (* (reg8 *) ADC_DelSig_1_DSM__SW6 )


//:TODO This definition will be changed when the register location moves
#define ADC_DelSig_1_PWRMGR_DSM (* (reg8 *) CYDEV_PM_AVAIL_CR5 )  /* Modulator Power manager */


/* This is only valid if there is an internal clock */
#if(ADC_DelSig_1_DEFAULT_INTERNAL_CLK)
#define ADC_DelSig_1_PWRMGR_CLK (* (reg8 *) ADC_DelSig_1_theACLK__PM_ACT_CFG )  /* Clock Power manager Reg */
#endif



/* Default register settings for the following configuration */
/* Sample Rate: 384000 Samples per Second */
/* Conversion Mode: 2 */
/* Input Buffer Gain: 1   */
/* ADC Reference: 0 */
/* ADC Input Range: 0  */
/* ADC Resolution: 8 bits */
/* ADC Clock: 6144000 Hz */

#define ADC_DelSig_1_DFLT_DEC_CR       0x28u
#define ADC_DelSig_1_DFLT_DEC_SR       0x14u
#define ADC_DelSig_1_DFLT_DEC_SHIFT1   0x04u
#define ADC_DelSig_1_DFLT_DEC_SHIFT2   0x06u
#define ADC_DelSig_1_DFLT_DEC_DR2      0x00u
#define ADC_DelSig_1_DFLT_DEC_DR2H     0x00u
#define ADC_DelSig_1_DFLT_DEC_DR1      0x0Fu
#define ADC_DelSig_1_DFLT_DEC_OCOR     0x00u
#define ADC_DelSig_1_DFLT_DEC_OCORM    0x00u
#define ADC_DelSig_1_DFLT_DEC_OCORH    0x00u
#define ADC_DelSig_1_DFLT_DEC_GVAL     0x00u
#define ADC_DelSig_1_DFLT_DEC_GCOR     0x00u
#define ADC_DelSig_1_DFLT_DEC_GCORH    0x00u
#define ADC_DelSig_1_DFLT_DEC_COHER    0x01u

#define ADC_DelSig_1_DFLT_DSM_CR0      0x0Au
#define ADC_DelSig_1_DFLT_DSM_CR1      0x00u
#define ADC_DelSig_1_DFLT_DSM_CR2      0x7Au
#define ADC_DelSig_1_DFLT_DSM_CR3      0x00u
#define ADC_DelSig_1_DFLT_DSM_CR4      0x14u
#define ADC_DelSig_1_DFLT_DSM_CR5      0x0Bu
#define ADC_DelSig_1_DFLT_DSM_CR6      0x0Bu
#define ADC_DelSig_1_DFLT_DSM_CR7      0x00u
#define ADC_DelSig_1_DFLT_DSM_CR8      0x11u
#define ADC_DelSig_1_DFLT_DSM_CR9      0x13u
#define ADC_DelSig_1_DFLT_DSM_CR10     0x11u
#define ADC_DelSig_1_DFLT_DSM_CR11     0x12u
#define ADC_DelSig_1_DFLT_DSM_CR12     0x01u
#define ADC_DelSig_1_DFLT_DSM_CR13     0x00u
#define ADC_DelSig_1_DFLT_DSM_CR14     0x01u
#define ADC_DelSig_1_DFLT_DSM_CR15     0x31u
#define ADC_DelSig_1_DFLT_DSM_CR16     0x1Au
#define ADC_DelSig_1_DFLT_DSM_CR17     0xABu
#define ADC_DelSig_1_DFLT_DSM_REF0     0x44u
#define ADC_DelSig_1_DFLT_DSM_REF1     0x00u
#define ADC_DelSig_1_DFLT_DSM_REF2     0x58u
#define ADC_DelSig_1_DFLT_DSM_REF3     0x00u

#define ADC_DelSig_1_DFLT_DSM_DEM0     0x07u
#define ADC_DelSig_1_DFLT_DSM_DEM1     0x00u
#define ADC_DelSig_1_DFLT_DSM_MISC     0x01u
#define ADC_DelSig_1_DFLT_DSM_CLK      0x18u

#define ADC_DelSig_1_DFLT_DSM_BUF0     0x05u
#define ADC_DelSig_1_DFLT_DSM_BUF1     0x02u
#define ADC_DelSig_1_DFLT_DSM_BUF2     0x00u
#define ADC_DelSig_1_DFLT_DSM_BUF3     0x00u
#define ADC_DelSig_1_DFLT_DSM_OUT0     0x00u
#define ADC_DelSig_1_DFLT_DSM_OUT1     0x00u

#define ADC_DelSig_1_DFLT_DSM_SW3      0x40u
#define ADC_DelSig_1_CLOCKS_PER_SAMPLE 0x0010u
#define ADC_DelSig_1_DFLT_CLOCK_FREQ   6144000

#define ADC_DelSig_1_REFERENCE_VOLTAGE    1.0240
#define ADC_DelSig_1_DFLT_COUNTS_PER_VOLT 250


#endif /* CY_ADC_DELSIG_ADC_DelSig_1_H */
/* [] END OF FILE */


