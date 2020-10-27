/*******************************************************************************
* File Name: main.c
*
* Version: 1.00
*
* Description:
*  This is the source code for the example project of the RTC_P4 component.
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>
#include <stdio.h>
#include <stdbool.h>
#include "MyTime.h"
#include "MyWDT.h"
#include "MyBuild.h"








/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  The main() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()
{
    DIO_0_0_Write(false);
    DIO_0_3_Write(false);
    char uartString[0x40] = {' '};
    char compileTimeString[0x40] = {' '};
    
    uint32 myLoop = 0;
    uint32 myLoopTotal = 200;
    /* Start RTC component */
    initRTC();
    setRTCUpdate();
    /* Set Date and Time */
    setTimeOfBuild();
    
        /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    sprintf(uartString, "\x1b[2J\x1b[;H");
    UART_PutString(uartString);
    sprintf(uartString, "\r\n\r\n\r\nRTC_P4_WDT_Example_V1.00.04-Fork1 \r\nCompile Time: ");
    UART_PutString(uartString);
    strcpy(compileTimeString,getTimeDateString());
    UART_PutString(compileTimeString);
    
    sprintf(uartString, "\r\nInitialization\r\n\r\n");
    UART_PutString(uartString);
    //Print Processor Info
    printDIEinfo();
    sprintf(uartString, "\r\n\r\n\r\n");
    UART_PutString(uartString);
    
    getALL_WDT_Values();


    /* Enable WCO */
    CySysClkWcoStart();
    
    /* Enable global interrupts */
    CyGlobalIntEnable;

    /* Alarm structure initialization */
    //alarmTimeDate.time = ALARM_TIME_HR_MIN_SEC;
    //alarmTimeDate.date = ALARM_DATE_MONTH_DAY_YEAR;
    
    initWDT0();
    
    getALL_WDT_Values();


    sprintf(uartString, "\r\nEntering Main Loop\r\n\r\n\r\n");
    UART_PutString(uartString);

    DIO_0_0_Write(!(DIO_0_0_Read()));
    while(myLoop <= myLoopTotal)
    {
        
        /* Get Date and Time from RTC */
        UART_PutString(getTimeDateString());


        /*if (alarmFlag == 1u)
        {
            UART_PutString("Alarm ");
            alarmFlag  = 0u;
        }
        else
        {*/
        //    UART_PutString("No-alarm");
        //}

        UART_PutString("\r");

        /* Switch to Sleep Mode */
        CySysWatchdogFeed(0);
        CySysPmDeepSleep();
        DIO_0_0_Write(!(DIO_0_0_Read()));
        if(myLoop == 3){
            getALL_WDT_Values();
        }
        myLoop++;
    }
    sprintf(uartString, "\r\n\r\n\r\nProgram finished running:  %lu .\r\n", myLoop);
    UART_PutString(uartString);
    UART_PutString(compileTimeString);
    UART_PutString("_");
    UART_PutString(getTimeDateString());
    sprintf(uartString, "_Consol-LOG\r\n\r\n\r\n");
    UART_PutString(uartString);
}





/* [] END OF FILE */
