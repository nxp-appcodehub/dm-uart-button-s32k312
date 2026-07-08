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

#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include "Dio.h"

/* Button Definitions */
#define LED_OFF_BUTTON DioConf_DioChannel_PTB_19
#define LED_ON_BUTTON DioConf_DioChannel_PTB_26

/* Debounce settings */
#define DEBOUNCE_DELAY 50000

/* Function prototypes */
void CheckButtons(void);
void HandleOnButton(void);
void HandleOffButton(void);
void InitButtons(void);

#endif /* BUTTON_HANDLER_H */
