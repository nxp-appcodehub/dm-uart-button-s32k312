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

#include "uart_comm.h"
#include "CDD_Uart.h"
#include <string.h>

/* Function to send a string via UART */
void SendString(const char *str)
{
    Std_ReturnType status;
    Uart_StatusType transmitStatus;
    uint32 bytesRemaining;

    status = Uart_AsyncSend(UART_LPUART_INTERNAL_CHANNEL,
                           (const uint8 *)str,
                           strlen(str));

    if (E_OK == status)
    {
        /* Wait until transmission completes */
        do
        {
            transmitStatus = Uart_GetStatus(UART_LPUART_INTERNAL_CHANNEL,
                                           &bytesRemaining,
                                           UART_SEND);
        } while (UART_STATUS_NO_ERROR != transmitStatus);
    }
}

/* Function to send button press notification via UART */
void SendButtonPressNotification(ButtonType buttonType)
{
	SendString("\r\n");
    switch (buttonType)
    {
        case BUTTON_TYPE_ON:
            SendString("User enabled Green LED using a button\r\n");
            break;

        case BUTTON_TYPE_OFF:
            SendString("User disabled all LED's using a button\r\n");
            break;

        default:
            SendString("Button: Unknown\r\n");
            break;
    }
}
