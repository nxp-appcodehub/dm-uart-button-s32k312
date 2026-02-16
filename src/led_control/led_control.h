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

#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "Dio.h"

/* LED Definitions */
#define LED_BLUE   DioConf_DioChannel_PTA_31
#define LED_GREEN  DioConf_DioChannel_PTA_30

/* Active-low LEDs (typical for eval boards) */
#define LED_ACTIVE_LOW  1

/* LED state tracking */
extern boolean greenLedOn;
extern boolean blueLedOn;
extern boolean ledStatus;

/* Function prototypes */
void SetLed(Dio_ChannelType channelId, Dio_LevelType level);
void SetLedGreen(Dio_LevelType level);
void SetLedBlue(Dio_LevelType level);
void SetAllLeds(Dio_LevelType level);

#endif /* LED_CONTROL_H */
