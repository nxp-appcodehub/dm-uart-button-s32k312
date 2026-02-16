/*==================================================================================================
* Project : RTD AUTOSAR 4.9
* Platform : CORTEXM
* Peripheral : S32K3XX
* Dependencies : none
*
* Autosar Version : 4.9.0
* Autosar Revision : ASR_REL_4_9_REV_0000
* Autosar Conf.Variant :
* SW Version : 7.0.0
* Build Version : S32K3_RTD_7_0_0_QLP03_D2512_ASR_REL_4_9_REV_0000_20251210
*
* Copyright 2020 - 2026 NXP
*
*   NXP Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#include "utils.h"
#include <string.h>

/* Simple delay function */
void Simple_Delay(uint32 delay_count)
{
    volatile uint32 delay;
    for(delay = 0; delay < delay_count; delay++)
    {
        /* Simple delay loop */
    }
}

/* Helper function to convert character to lowercase */
char ToLower(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + ('a' - 'A');
    }
    return c;
}

/* Helper function to trim whitespace from string */
void TrimString(char *str)
{
    uint8 i = 0, j = 0;
    uint8 len = strlen(str);

    /* Remove leading whitespace */
    while (i < len && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n'))
    {
        i++;
    }

    /* Shift string */
    while (i < len)
    {
        str[j++] = str[i++];
    }
    str[j] = '\0';

    /* Remove trailing whitespace */
    if (j > 0)
    {
        j--;
        while (j > 0 && (str[j] == ' ' || str[j] == '\t' || str[j] == '\r' || str[j] == '\n'))
        {
            str[j--] = '\0';
        }
    }
}
