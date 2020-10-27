/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "UART.h"
#include "CyLFClk.h"
#include "CyLib.h"
#include "isr_WDT.h"

#include <stdio.h>
#include <stdbool.h>

#include "MyTime.h"

#define LFCLK_CYCLES_PER_SECOND     (32768u)
#define WCO_STARTUP_DELAY_CYCLES    (LFCLK_CYCLES_PER_SECOND)

#define MY_DELAY_CYCLES             (65534u)
                          

/* Interrupt prototypes */
CY_ISR_PROTO(EnableRtcWDT0Operation);
CY_ISR_PROTO(UpdateTimeIsrWDT0Handler);

CY_ISR_PROTO(EnableRtcWDT1Operation);
CY_ISR_PROTO(UpdateTimeIsrWDT1Handler);

CY_ISR_PROTO(WDT_ISR);


void setAllWDTisr(void);

void initWDT0(void);
void initWDT1(void);
void initWDT2(void);


void getALL_WDT_Values(void);


/* [] END OF FILE */
