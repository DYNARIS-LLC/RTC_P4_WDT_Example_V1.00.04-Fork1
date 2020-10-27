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

#include <stdio.h>
#include <stdbool.h>

#include "project.h"



#define DIE_MASK            (0xFFu)

#if(CY_PSOC4)
    #define DIE0_LOT0       (0u)
    #define DIE0_LOT1       (8u)
    #define DIE0_LOT2       (16u)
    #define DIE1_SORT       (16u)
    #define DIE1_MINOR      (24u)
#else
    #define DIE0_LOT_LSB    (0u)
    #define DIE0_LOT_MSB    (8u)
    #define DIE0_REV_ID     (16u)
    #define DIE1_WRK_WK     (16u)
    #define DIE1_FAB_YR     (24u)
#endif  /* (CY_PSOC4) */

#define DIE0_WAFER          (24u)
#define DIE1_X              (0u)
#define DIE1_Y              (8u)


    /* Pointer to a two element 32-bit unsigned integer array */
    uint32 uniqueId[2];
    char commonUniqueIdInfo[60u];
    char uniqueUniqueIdInfo[80u];
    //char uartString[0x40] = {' '};

/* Pointer to a two element 32-bit unsigned integer array */
uint32 uniqueId[2];

void printDIEinfo(void);

/* [] END OF FILE */
