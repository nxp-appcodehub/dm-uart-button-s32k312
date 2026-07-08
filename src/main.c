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

/**
*   @file main.c
*
*   @addtogroup main_module main module documentation
*   @{
*/

/* Driver includes */
#include "Mcl.h"
#include "Mcu.h"
#include "CDD_Uart.h"
#include "Port.h"
#include "Platform.h"
#include "Dio.h"
#include "Lpuart_Uart_Ip_Irq.h"

/* Application includes */
#include "led_control.h"
#include "button_handler.h"
#include "uart_comm.h"
#include "command_processor.h"
#include "utils.h"

#include <string.h>

/* Buffer size for receiving commands */
#define RX_BUFFER_SIZE 64

/* Global variables */
static uint8 rxBuffer[RX_BUFFER_SIZE];

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
    Uart_StatusType receiveStatus;
    uint32 bytesRemaining;

    /* Initialize the Mcu driver */
    Mcu_Init(NULL_PTR);
    Mcu_InitClock(0);

#if (MCU_NO_PLL == STD_OFF)
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus() )
    {
        /* Busy wait until the System PLL is locked */
    }
    Mcu_DistributePllClock();
#endif

    Mcu_SetMode(0);
    Mcl_Init(NULL_PTR);
    Port_Init(NULL_PTR);
    Platform_Init(NULL_PTR);
    Uart_Init(NULL_PTR);

    /* Initialize all LEDs to OFF */
    ledStatus = FALSE;
    SetAllLeds(STD_LOW);

    /* Initialize button states to prevent false triggers */
    InitButtons();

    /* Send welcome message */
    Simple_Delay(100000);  /* Small delay for UART stabilization */
    SendString(WELCOME_MSG);
    SendString(HELP_MSG);
    SendString(PROMPT_MSG);

    /* Initialize UART receive once before main loop */
    Uart_AsyncReceive(UART_LPUART_INTERNAL_CHANNEL, rxBuffer, 1);

    /* Main command processing loop */
    while(1)
    {
        /* Check for button presses - this runs continuously */
        CheckButtons();

        /* Check if UART data is available (non-blocking) */
        receiveStatus = Uart_GetStatus(UART_LPUART_INTERNAL_CHANNEL,
                                       &bytesRemaining,
                                       UART_RECEIVE);

        if (receiveStatus == UART_STATUS_NO_ERROR)
        {
            /* Data was received, process it */

            /* Echo the received character */
            Uart_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, rxBuffer, 1);
            do
            {
                Uart_StatusType sendStatus = Uart_GetStatus(UART_LPUART_INTERNAL_CHANNEL,
                                              &bytesRemaining,
                                              UART_SEND);
                if (sendStatus == UART_STATUS_NO_ERROR) break;
            } while (1);

            /* Process received character */
            if (rxBuffer[0] == '\r' || rxBuffer[0] == '\n')
            {
                /* End of command - send newline and process */
                SendString("\r\n");
                ProcessCommand();
            }
            else if (rxBuffer[0] == '\b' || rxBuffer[0] == 127)  /* Backspace */
            {
                if (cmdIndex > 0)
                {
                    cmdIndex--;
                    cmdBuffer[cmdIndex] = '\0';
                    /* Send backspace sequence to terminal */
                    SendString("\b \b");
                }
            }
            else if (cmdIndex < CMD_BUFFER_SIZE - 1)
            {
                /* Add character to command buffer */
                cmdBuffer[cmdIndex++] = rxBuffer[0];
                cmdBuffer[cmdIndex] = '\0';
            }

            /* Start new receive for next character */
            Uart_AsyncReceive(UART_LPUART_INTERNAL_CHANNEL, rxBuffer, 1);
        }
        else if (receiveStatus == UART_STATUS_OPERATION_ONGOING)
        {
            /* Still waiting for data - that's OK, continue loop */
        }
        else
        {
            /* Error or no operation - start a new receive */
            Uart_AsyncReceive(UART_LPUART_INTERNAL_CHANNEL, rxBuffer, 1);
        }

        /* Small delay to prevent CPU hogging */
        Simple_Delay(100);
    }

    return (0U);
}
