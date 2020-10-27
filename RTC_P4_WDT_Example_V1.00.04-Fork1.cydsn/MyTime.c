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
#include "MyTime.h"

void setDefaultTime(){
   
    RTC_SetDateAndTime(TIME_HR_MIN_SEC_Default,DATE_MONTH_DAY_YEAR_Default);
}
void setTimeOfBuild(){
    RTC_SetDateAndTime(TIME_HR_MIN_SEC_BUILD,DATE_MONTH_DAY_YEAR_BUILD);
}

void initRTC(){
    RTC_Start();
}

void myRTC_Update(){
    RTC_Update();
}

void setRTCUpdate(){
    /* Set RTC time update period */
    //RTC_SetPeriod(1u, TICK_EACH_1_HZ);
    // Default ^^^^^^^^^
    RTC_SetPeriod(32768, 32768);
}

char *buildTimeString(){
        /* Get Date and Time from RTC */
    time = RTC_GetTime();

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */

    /* Print Date and Time to UART */
    sprintf(timeBuffer, "%02lu-%02lu-%02lu", RTC_GetHours(time), RTC_GetMinutes(time), RTC_GetSecond(time));
    return timeBuffer;
}

char *buildDateString(){
    date = RTC_GetDate();
        //sprintf(dateBuffer, "%02lu/%02lu/%02lu", RTC_GetMonth(date), RTC_GetDay(date), RTC_GetYear(date));
    sprintf(dateBuffer, "%02lu-%02lu-%02lu", RTC_GetYear(date), RTC_GetMonth(date), RTC_GetDay(date));
    return dateBuffer;
}

char *getTimeDateString(){
    date = RTC_GetDate();
        //sprintf(dateBuffer, "%02lu/%02lu/%02lu", RTC_GetMonth(date), RTC_GetDay(date), RTC_GetYear(date));
    sprintf(timeDateBuffer, "%2s_%2s", buildDateString(), buildTimeString());
    
    /*
    UART_PutString(buildDateString());
    UART_PutString("_");
    UART_PutString(buildTimeString());
    */
    return timeDateBuffer;
}

void initDefaultAlarm(){
    
    /* Ignore second mask to call alarm */
    RTC_SetAlarmMask((uint32)~RTC_ALARM_SEC_MASK);
    
    /* Set Alarm Date and Time */
    RTC_SetAlarmDateAndTime(&alarmTimeDate);

    /* Set function AlarmIsrHandler to be called when alarm triggers */
    RTC_SetAlarmHandler(AlarmIsrHandler);
}


/*******************************************************************************
* Function Name: AlarmIsrHandler
********************************************************************************
* Summary:
*  The interrupt handler for Alarm interrupts. Toggles the LED_WdtInt pin.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void AlarmIsrHandler(void)
{
    //alarmFlag = 1u;

    /* Toggle pin state */
     //LED_Alarm_Write((uint8)~(LED_Alarm_Read()));

    /* Clear interrupts state */
    RTC_ClearAlarmStatus();
}

/* [] END OF FILE */
