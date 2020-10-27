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
#include "FirmwareBuildTime.h"
#include "RTC.h"
#include <stdio.h>
#include <stdbool.h>


    #define TIME_HOUR_Default            (0x02u)
    #define TIME_MIN_Default             (0x59u)
    #define TIME_SEC_Default             (0x50u)
    #define HOUR_OFFSET_Default          (16u)
    #define MIN_OFFSET_Default           (8u)


    #define TIME_HR_MIN_SEC_Default     ((uint32)(TIME_HOUR_Default << HOUR_OFFSET_Default) | \
                                (uint32)(TIME_MIN_Default << MIN_OFFSET_Default)    | \
                                 TIME_SEC_Default)
                                


    /* Date: 2020-10-03 */

    #define DATE_MONTH_Default          (RTC_OCTOBER)
    #define DATE_DAY_Default            (0x03u)
    #define DATE_YEAR_Default           (0x2020u)
    #define MONTH_OFFSET_Default        (0u)
    #define DAY_OFFSET_Default          (0u)

    #define DATE_MONTH_DAY_YEAR_Default ((uint32)(DATE_MONTH_Default << MONTH_OFFSET_Default)   | \
                                (uint32)(DATE_DAY_Default << DAY_OFFSET_Default)        | \
                                 DATE_YEAR_Default)
                                
                                
                                
    /*#define TIME_HR_MIN_SEC_BUILD     ((uint32)(TIME_HOUR_BUILD) | \
                            (uint32)(TIME_MIN_BUILD)    | \
                             TIME_SEC_BUILD)
    */ 
    /*                        
    #define DATE_MONTH_DAY_YEAR_BUILD ((uint32)(DATE_MONTH_BUILD<< RTC_YEAR_OFFSET)   | \
                            (uint32)(DATE_DAY_BUILD)        | \
                             DATE_YEAR_BUILD<< RTC_YEAR_OFFSET)                               
    */
                                
    #define TIME_HR_MIN_SEC_BUILD     ((uint32)(TIME_HOUR_BUILD << HOUR_OFFSET_BUILD) | \
                            (uint32)(TIME_MIN_BUILD << MIN_OFFSET_BUILD)    | \
                             TIME_SEC_BUILD)
                           
    #define DATE_MONTH_DAY_YEAR_BUILD ((uint32)(DATE_MONTH_BUILD << MONTH_OFFSET_BUILD)   | \
                            (uint32)(DATE_DAY_BUILD << DAY_OFFSET_BUILD)        | \
                             DATE_YEAR_BUILD)               
                           
                            
    /* Alarm Time: 15:44:00 */
                        
    #define ALARM_HOUR                  (0x04u)
    #define ALARM_MIN                   (0x01u)
    #define ALARM_SEC                   (0x30u)
    #define ALARM_TIME_HR_MIN_SEC       ((uint32)(ALARM_HOUR << HOUR_OFFSET) | \
                                        (uint32)(ALARM_MIN << MIN_OFFSET)    | \
                                         ALARM_SEC)

    /* Alarm Date: 12/18/2014 */
    #define ALARM_DATE_MONTH_DAY_YEAR   (DATE_MONTH_DAY_YEAR)
                                

    #define TICK_EACH_1_HZ      (1u)

    /* Alarm structure declaration */
    RTC_DATE_TIME alarmTimeDate;

    /* Alarm flag initialization */
    //uint32 alarmFlag = 0;     

    uint32 time;
    uint32 date;
    static char timeBuffer[16u];
    static char dateBuffer[16u];
    static char timeDateBuffer[40u];

void initRTC(void);

void setRTCUpdate(void);

void setDefaultTime(void);

void setTimeOfBuild(void);

char *buildTimeString(void);
char *buildDateString(void);

char *getTimeDateString(void);

void myRTC_Update(void);

CY_ISR_PROTO(AlarmIsrHandler);

/* [] END OF FILE */
