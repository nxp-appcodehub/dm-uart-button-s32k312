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

#ifndef UART_COMM_H
#define UART_COMM_H

#include "Std_Types.h"

/* Button type enumeration */
typedef enum
{
    BUTTON_TYPE_ON = 0,
    BUTTON_TYPE_OFF
} ButtonType;

/* UART channel definition */
#define UART_LPUART_INTERNAL_CHANNEL  0

/* Messages */
#define WELCOME_MSG "\r\n=== LED Control System ===\r\n"
#define PROMPT_MSG "Enter command (type 'help' for available commands): "
#define HELP_MSG "\r\nAvailable Commands:\r\n" \
                 "  led on  - Turn on all LEDs\r\n" \
                 "  led off - Turn off all LEDs\r\n" \
                 "  status  - Display current LED status\r\n" \
                 "  help    - Display this help message\r\n\r\n"
#define UNKNOWN_CMD_MSG "Unknown command. Type 'help' for available commands.\r\n"
#define LED_ON_MSG "Blue LED turned ON using UART\r\n"
#define LED_OFF_MSG "All LEDs turned OFF using UART\r\n"

/* Function prototypes */
void SendString(const char *str);
void SendButtonPressNotification(ButtonType buttonType);

#endif /* UART_COMM_H */
