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
#include "MyWDT.h"
#include "DIO_0_3.h"
#include "DIO_0_3_aliases.h"


void setAllWDTisr(){
        /* Map the WatchDog_ISR vector to the WDT_ISR */
    isr_WDT_StartEx(WDT_ISR);
}

/*
CY_ISR(WDT_ISR)
{
    // Clear WDT interrupt 
    CySysWdtClearInterrupt();

    // Write WDT_MATCH with current match value + desired match value
    //CySysWdtWriteMatch((uint16)CySysWdtReadMatch()+ILODelayCycles);
}
*/
CY_ISR(WDT_ISR)
{
    UART_PutString("\r\nwdtInterruptHandler\r\n");
    DIO_0_3_Write(!(DIO_0_3_Read()));
    //trigger_Write(1); // Chip is woken up 
    uint32 reason = CySysWdtGetInterruptSource();
    
    if(reason & CY_SYS_WDT_COUNTER0_INT)
        //RED_Write(~RED_Read());
        //EnableRtcOperation();
        //WDT_CHK_ISR0();
        EnableRtcWDT0Operation();
  
    if(reason & CY_SYS_WDT_COUNTER1_INT)
        //GREEN_Write(~GREEN_Read());
  
    if(reason & CY_SYS_WDT_COUNTER2_INT)
        //BLUE_Write(~BLUE_Read());
        //RTC_Update();
        myRTC_Update();
  
    CySysWdtClearInterrupt(reason);  // Clear the WDT Interrupt
    
}

void initWDT0(){
    /* Prepare COUNTER0 to use it by CySysTimerDelay function in
     * "INTERRUPT" mode: disable "clear on match" functionality, configure
     * COUNTER0 to generate interrupts on match.
     */
    CySysWdtSetClearOnMatch(CY_SYS_WDT_COUNTER0, 0u);
    CySysWdtSetMode(CY_SYS_WDT_COUNTER0, CY_SYS_WDT_MODE_INT);
    
    /* Enable WDT COUNTER0 */
    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK);
    
    /* Disable servicing interrupts from WDT_COUNTER0 to prevent
       trigger callback before the CySysTimerDelay() function. */
    CySysWdtDisableCounterIsr(CY_SYS_WDT_COUNTER0);
    
    /* Register EnableRtcOperation() by the COUNTER0. */
    CySysWdtSetInterruptCallback(CY_SYS_WDT_COUNTER0, EnableRtcWDT0Operation);
    
    /* Initiate run the EnableRtcOperation() callback in WCO_STARTUP_DELAY_CYCLES interval. */
    //CySysTimerDelay(CY_SYS_WDT_COUNTER0, CY_SYS_TIMER_INTERRUPT, WCO_STARTUP_DELAY_CYCLES);
    CySysTimerDelay(CY_SYS_WDT_COUNTER0, CY_SYS_TIMER_INTERRUPT, MY_DELAY_CYCLES);
}

/*******************************************************************************
* Function Name: UpdateTimeIsrHandler
********************************************************************************
* Summary: 
*  This interrupt handler is intended to switch LFCLK source from ILO to WCO and
*  enable RTC operation. 
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
//void EnableRtcWDT0Operation(void)
void EnableRtcWDT0Operation(void)
{
    //DIO_0_3_Write(!(DIO_0_3_Read()));
    /* Switch LFCLK source from ILO to WCO. */
    CySysClkSetLfclkSource(CY_SYS_CLK_LFCLK_SRC_WCO);
    
    /* Configure COUNTER0 to generate interrupt every second. */
    CySysWdtDisable(CY_SYS_WDT_COUNTER0_MASK);
    CySysWdtSetClearOnMatch(CY_SYS_WDT_COUNTER0, 1u);
    //^^^^^^^^^^^^Default^^^^^^^^^^^^^^^
    //CySysWdtSetClearOnMatch(CY_SYS_WDT_COUNTER0, 2u);
    //CySysWdtSetMatch(CY_SYS_WDT_COUNTER0, LFCLK_CYCLES_PER_SECOND);
    //^^^^^^^^^^^^Default^^^^^^^^^^^^^^^
    CySysWdtSetMatch(CY_SYS_WDT_COUNTER0, MY_DELAY_CYCLES);
    
    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK);
    
    /* Eegister UpdateTimeIsrHandler() by the COUNTER0. */
    CySysWdtSetInterruptCallback(CY_SYS_WDT_COUNTER0, UpdateTimeIsrWDT0Handler);
    
    /* Enable the COUNTER0 ISR handler. */
    CySysWdtEnableCounterIsr(CY_SYS_WDT_COUNTER0);
    
    /* Configure the LFCLK_Out pin to drive it by LFCLK. */
    //LFCLK_Out_SetDriveMode(LFCLK_Out_DM_STRONG);
}


/*******************************************************************************
* Function Name: UpdateTimeIsrWDT0Handler
********************************************************************************
* Summary: 
*  The interrupt handler for WDT counter 0 interrupts. Toggles the LED_WdtIsr 
*  pin.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimeIsrWDT0Handler(void)
{
    //DIO_0_0_Write(!(DIO_0_0_Read()));
    /* Toggle pin state */
    //LED_WdtIsr_Write((uint8)~(LED_WdtIsr_Read()));
    myRTC_Update();
    
    DIO_0_3_Write(!(DIO_0_3_Read()));
}



void initWDT1(){
        /* Prepare COUNTER0 to use it by CySysTimerDelay function in
     * "INTERRUPT" mode: disable "clear on match" functionality, configure
     * COUNTER0 to generate interrupts on match.
     */
    CySysWdtSetClearOnMatch(CY_SYS_WDT_COUNTER1, 0u);
    CySysWdtSetMode(CY_SYS_WDT_COUNTER1, CY_SYS_WDT_MODE_INT);
    
    /* Enable WDT COUNTER0 */
    CySysWdtEnable(CY_SYS_WDT_COUNTER1_MASK);
    
    /* Disable servicing interrupts from WDT_COUNTER0 to prevent
       trigger callback before the CySysTimerDelay() function. */
    CySysWdtDisableCounterIsr(CY_SYS_WDT_COUNTER1);
    
    /* Register EnableRtcOperation() by the COUNTER0. */
    CySysWdtSetInterruptCallback(CY_SYS_WDT_COUNTER1, EnableRtcWDT0Operation);
    
    /* Initiate run the EnableRtcOperation() callback in WCO_STARTUP_DELAY_CYCLES interval. */
    //CySysTimerDelay(CY_SYS_WDT_COUNTER0, CY_SYS_TIMER_INTERRUPT, WCO_STARTUP_DELAY_CYCLES);
    CySysTimerDelay(CY_SYS_WDT_COUNTER1, CY_SYS_TIMER_INTERRUPT, MY_DELAY_CYCLES);
}

/*******************************************************************************
* Function Name: UpdateTimeIsrHandler
********************************************************************************
* Summary: 
*  This interrupt handler is intended to switch LFCLK source from ILO to WCO and
*  enable RTC operation. 
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EnableRtcWDT1Operation(void)
{
    //DIO_0_3_Write(!(DIO_0_3_Read()));
    /* Switch LFCLK source from ILO to WCO. */
    CySysClkSetLfclkSource(CY_SYS_CLK_LFCLK_SRC_WCO);
    
    /* Configure COUNTER0 to generate interrupt every second. */
    CySysWdtDisable(CY_SYS_WDT_COUNTER1_MASK);
    CySysWdtSetClearOnMatch(CY_SYS_WDT_COUNTER1, 1u);
    //^^^^^^^^^^^^Default^^^^^^^^^^^^^^^
    //CySysWdtSetClearOnMatch(CY_SYS_WDT_COUNTER0, 2u);
    //CySysWdtSetMatch(CY_SYS_WDT_COUNTER0, LFCLK_CYCLES_PER_SECOND);
    //^^^^^^^^^^^^Default^^^^^^^^^^^^^^^
    CySysWdtSetMatch(CY_SYS_WDT_COUNTER1, MY_DELAY_CYCLES);
    
    CySysWdtEnable(CY_SYS_WDT_COUNTER1_MASK);
    
    /* Eegister UpdateTimeIsrHandler() by the COUNTER0. */
    CySysWdtSetInterruptCallback(CY_SYS_WDT_COUNTER1, UpdateTimeIsrWDT1Handler);
    
    /* Enable the COUNTER0 ISR handler. */
    CySysWdtEnableCounterIsr(CY_SYS_WDT_COUNTER1);
    
    /* Configure the LFCLK_Out pin to drive it by LFCLK. */
    //LFCLK_Out_SetDriveMode(LFCLK_Out_DM_STRONG);
}

/*******************************************************************************
* Function Name: UpdateTimeIsrWDT0Handler
********************************************************************************
* Summary: 
*  The interrupt handler for WDT counter 0 interrupts. Toggles the LED_WdtIsr 
*  pin.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimeIsrWDT1Handler(void)
{
    //DIO_0_0_Write(!(DIO_0_0_Read()));
    /* Toggle pin state */
    //LED_WdtIsr_Write((uint8)~(LED_WdtIsr_Read()));
    //myRTC_Update();
    
    //DIO_0_3_Write(!(DIO_0_3_Read()));
}

void initWDT2(){
    
}


void getALL_WDT_Values(){

    CyDelay(50u);
    char uartString2[0x40];
    
    int32 WcoEnabledValue;
    int32 WdtGetCascadeValue;
    int32 WdtGetToggleBitValue;
    //cyWdtCallback WdtGetInterruptSourceValue;
    //int32 Value;
    
    int32 WdtGetModeValue0;
    int32 WdtGetModeValue1;
    int32 WdtGetModeValue2;
    
    int32 WdtGetEnabledStatusValue0;
    int32 WdtGetEnabledStatusValue1;
    int32 WdtGetEnabledStatusValue2;
    
    int32 WdtGetClearOnMatchValue0;
    int32 WdtGetClearOnMatchValue1;
    int32 WdtGetClearOnMatchValue2;
    
    int32 WdtGetMatchValue0;
    int32 WdtGetMatchValue1;
    int32 WdtGetMatchValue2;

    int32 WdtGetCountValue0;
    int32 WdtGetCountValue1;
    int32 WdtGetCountValue2;    

    int32 WdtGetInterruptCallbackValue0;
    int32 WdtGetInterruptCallbackValue1;
    int32 WdtGetInterruptCallbackValue2;    
    

    CyDelay(50u);
    WcoEnabledValue = CySysClkWcoEnabled();
    sprintf(uartString2, "\r\n\r\nWcoEnabledValue:  %lu .", WcoEnabledValue);
    UART_PutString(uartString2);
    CyDelay(50u);
    
    WdtGetCascadeValue = CySysWdtGetCascade();
    sprintf(uartString2, "\r\nWdtGetCascadeValue:  %lu .", WdtGetCascadeValue);
    UART_PutString(uartString2);
    CyDelay(50u);
    
    WdtGetToggleBitValue = CySysWdtGetToggleBit();
    //WdtGetInterruptSourceValue = CySysWdtGetInterruptSource();
    CyDelay(50u);


    sprintf(uartString2, "\r\nWdtGetToggleBitValue:  %lu .\r\n", WdtGetToggleBitValue);
     UART_PutString(uartString2);
    CyDelay(50u);
    //WdtGetInterruptSourceValue:  %lu .");
    
    CyDelay(50u);
    WdtGetModeValue0 = CySysWdtGetMode(0);
    sprintf(uartString2, "\r\nWdtGetModeValue0:  %lu .", WdtGetModeValue0);
    UART_PutString(uartString2);
    //CyDelay(50u);
    
    WdtGetEnabledStatusValue0 = CySysWdtGetEnabledStatus(0);
    sprintf(uartString2, "\r\nWdtGetEnabledStatusValue0:  %lu .", WdtGetEnabledStatusValue0);
    UART_PutString(uartString2);
    //CyDelay(50u);
    
    WdtGetClearOnMatchValue0 = CySysWdtGetClearOnMatch(0);
    
    sprintf(uartString2, "\r\nWdtGetClearOnMatchValue0:  %lu .", WdtGetClearOnMatchValue0);
    UART_PutString(uartString2);
    //CyDelay(50u);
    
    WdtGetMatchValue0 = CySysWdtGetMatch(0);
    sprintf(uartString2, "\r\nWdtGetMatchValue0:  %lu .", WdtGetMatchValue0);
    UART_PutString(uartString2);
    //CyDelay(50u);
    
    WdtGetCountValue0 = CySysWdtGetCount(0);
    sprintf(uartString2, "\r\nWdtGetCountValue0:  %lu .", WdtGetCountValue0);
    UART_PutString(uartString2);
    //CyDelay(50u);
    
    WdtGetInterruptCallbackValue0 = (uint32)CySysWdtGetInterruptCallback(0);
    CyDelay(50u);
    sprintf(uartString2, "\r\nWdtGetInterruptCallbackValue0:  %lu .\r\n", WdtGetInterruptCallbackValue0);
     UART_PutString(uartString2);
    //CyDelay(50u);

    WdtGetModeValue1 = CySysWdtGetMode(1);
    sprintf(uartString2, "\r\nWdtGetModeValue1:  %lu .", WdtGetModeValue1);
    UART_PutString(uartString2);
    //CyDelay(50u);
    
    WdtGetEnabledStatusValue1 = CySysWdtGetEnabledStatus(1);
    sprintf(uartString2, "\r\nWdtGetEnabledStatusValue1:  %lu .", WdtGetEnabledStatusValue1);
    UART_PutString(uartString2);
    //CyDelay(50u);    
    
    WdtGetClearOnMatchValue1 = CySysWdtGetClearOnMatch(1);
    sprintf(uartString2, "\r\nWdtGetClearOnMatchValue1:  %lu .", WdtGetClearOnMatchValue1);
    UART_PutString(uartString2);
    //CyDelay(50u);    
    
    WdtGetMatchValue1 = CySysWdtGetMatch(1);
    sprintf(uartString2, "\r\nWdtGetMatchValue1:  %lu .", WdtGetMatchValue1);
    UART_PutString(uartString2);
    //CyDelay(50u);    
    
    WdtGetCountValue1 = CySysWdtGetCount(1);
    sprintf(uartString2, "\r\nWdtGetCountValue1:  %lu .", WdtGetCountValue1);
    UART_PutString(uartString2);
    //CyDelay(50u);
    
    WdtGetInterruptCallbackValue1 = (uint32)CySysWdtGetInterruptCallback(1);
    sprintf(uartString2, "\r\nWdtGetInterruptCallbackValue1:  %lu .\r\n", WdtGetInterruptCallbackValue1);
    UART_PutString(uartString2);
    //CyDelay(50u);
    CyDelay(50u);
    
    CySysWatchdogFeed(0);
    CySysWatchdogFeed(1);
    CyDelay(50u);

    WdtGetModeValue2 = CySysWdtGetMode(2);
    sprintf(uartString2, "\r\nWdtGetModeValue2:  %lu .", WdtGetModeValue2);
    UART_PutString(uartString2);
    //CyDelay(50u);
    
    WdtGetEnabledStatusValue2 = CySysWdtGetEnabledStatus(2);
    sprintf(uartString2, "\r\nWdtGetEnabledStatusValue2:  %lu .", WdtGetEnabledStatusValue2);
    UART_PutString(uartString2);
    //CyDelay(50u);
    
    /*
    WdtGetClearOnMatchValue2 = CySysWdtGetClearOnMatch(2);
    sprintf(uartString2, "\r\nWdtGetClearOnMatchValue2:  %lu .", WdtGetClearOnMatchValue2);
     UART_PutString(uartString2);
    CyDelay(50u);
    
    
    WdtGetMatchValue2 = CySysWdtGetMatch(2);
    sprintf(uartString2, "\r\nWdtGetMatchValue2:  %lu .", WdtGetMatchValue2);
     UART_PutString(uartString2);
    CyDelay(50u);
    */
    
    WdtGetCountValue2 = CySysWdtGetCount(2);
    sprintf(uartString2, "\r\nWdtGetCountValue2:  %lu .", WdtGetCountValue2);
    UART_PutString(uartString2);
    //CyDelay(50u);
    
    
    WdtGetInterruptCallbackValue2 = (uint32)CySysWdtGetInterruptCallback(2);
    sprintf(uartString2, "\r\nWdtGetInterruptCallbackValue2:  %lu .\r\n", WdtGetInterruptCallbackValue2);
    UART_PutString(uartString2);
    
    CyDelay(50u);
    
}

/* [] END OF FILE */
