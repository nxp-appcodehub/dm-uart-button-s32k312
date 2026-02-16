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

#include "led_control.h"

/* Global LED state variables */
boolean greenLedOn = FALSE;
boolean blueLedOn = FALSE;
boolean ledStatus = FALSE;

/* Set individual LED with active-low handling */
void SetLed(Dio_ChannelType channelId, Dio_LevelType level)
{
    Dio_LevelType actualLevel;

#if (LED_ACTIVE_LOW == 1)
    /* Invert for active-low LEDs */
    actualLevel = (level == STD_HIGH) ? STD_LOW : STD_HIGH;
#else
    actualLevel = level;
#endif
    Dio_WriteChannel(channelId, actualLevel);
}

/* Function to control green LED */
void SetLedGreen(Dio_LevelType level)
{
    SetLed(LED_GREEN, level);
    greenLedOn = (level == STD_HIGH) ? TRUE : FALSE;
}

/* Function to control blue LED */
void SetLedBlue(Dio_LevelType level)
{
    SetLed(LED_BLUE, level);
    blueLedOn = (level == STD_HIGH) ? TRUE : FALSE;
}

/* Function to control all LEDs */
void SetAllLeds(Dio_LevelType level)
{
    SetLedBlue(level);
    SetLedGreen(level);
    ledStatus = (level == STD_HIGH) ? TRUE : FALSE;
}
