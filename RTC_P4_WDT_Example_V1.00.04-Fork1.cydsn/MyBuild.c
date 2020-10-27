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
#include "MyBuild.h"

void printDIEinfo(){
    /* Gets unique id of the device */
    CyGetUniqueId(uniqueId);
    /* Sends formatted output to a string pointed to by commonUniqueIdInfo */
    sprintf(commonUniqueIdInfo,"\rWafer=%03lu XPos=%03lu YPos=%03lu",
        (uniqueId[0] >> DIE0_WAFER) & DIE_MASK,
        (uniqueId[1] >> DIE1_X)     & DIE_MASK,
        (uniqueId[1] >> DIE1_Y)     & DIE_MASK);

    /* Print common Unique ID information to UART */
    UART_PutString(commonUniqueIdInfo);

    /* Sends formatted output to a string pointed to by uniqueUniqueIdInfo */
    #if (CY_PSOC4)
    sprintf(uniqueUniqueIdInfo,"\n\rRevID=%03lu Lot0=%03lu Lot1=%03lu Lot2=%03lu Sort=%03lu",
        (uniqueId[1] >> DIE1_MINOR) & DIE_MASK,
        (uniqueId[0] >> DIE0_LOT0)  & DIE_MASK,
        (uniqueId[0] >> DIE0_LOT1)  & DIE_MASK,
        (uniqueId[0] >> DIE0_LOT2)  & DIE_MASK,
        (uniqueId[1] >> DIE1_SORT)  & DIE_MASK);
    #else
    sprintf(uniqueUniqueIdInfo,"\n\r RevID=%03lu\n\r LotLSB=%03lu\n\r LotMSB=%03lu\n\r Ww=%03lu\n\r YearFab=%03lu",
        (uniqueId[0] >> DIE0_REV_ID)   & DIE_MASK,
        (uniqueId[0] >> DIE0_LOT_LSB)  & DIE_MASK,
        (uniqueId[0] >> DIE0_LOT_MSB)  & DIE_MASK,
        (uniqueId[1] >> DIE1_WRK_WK)   & DIE_MASK,
        (uniqueId[1] >> DIE1_FAB_YR)   & DIE_MASK);
    #endif /* (CY_PSOC3 || CY_PSOC5) */

    /* Print unique Unique ID information to UART */
    UART_PutString(uniqueUniqueIdInfo);

    
}
/* [] END OF FILE */
