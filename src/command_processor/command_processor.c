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

#include "command_processor.h"
#include "led_control.h"
#include "uart_comm.h"
#include "utils.h"
#include <string.h>

/* Global command buffer */
uint8 cmdBuffer[CMD_BUFFER_SIZE];
uint8 cmdIndex = 0;

/* Handle 'led on' command */
void HandleUARTLedOn(void)
{
    SetLedBlue(STD_HIGH);
    SetLedGreen(STD_LOW);
    ledStatus = TRUE;
    SendString(LED_ON_MSG);
}

/* Handle 'led off' command */
void HandleLedOff(void)
{
    SetAllLeds(STD_LOW);
    ledStatus = FALSE;
    SendString(LED_OFF_MSG);
}

/* Handle 'status' command */
void HandleStatus(void)
{
    char statusMsg[100];

    strcpy(statusMsg, "\r\nLED Status:\r\n");
    SendString(statusMsg);

    if (greenLedOn)
    {
        SendString("\tGreen LED: ON\r\n");
    }
    else
    {
        SendString("\tGreen LED: OFF\r\n");
    }

    if (blueLedOn)
    {
        SendString("\tBlue LED: ON\r\n");
    }
    else
    {
        SendString("\tBlue LED: OFF\r\n");
    }
    SendString("\r\n");
}

/* Handle 'help' command */
void HandleHelp(void)
{
    SendString(HELP_MSG);
}

/* Process received command */
void ProcessCommand(void)
{
    char lowerCmd[CMD_BUFFER_SIZE];
    uint8 i;

    /* Convert command to lowercase for case-insensitive comparison */
    for (i = 0; i < cmdIndex && i < CMD_BUFFER_SIZE - 1; i++)
    {
        lowerCmd[i] = ToLower(cmdBuffer[i]);
    }
    lowerCmd[i] = '\0';

    /* Trim whitespace */
    TrimString(lowerCmd);

    /* Parse and execute command */
    if (strcmp(lowerCmd, "led on") == 0)
    {
        HandleUARTLedOn();
    }
    else if (strcmp(lowerCmd, "led off") == 0)
    {
        HandleLedOff();
    }
    else if (strcmp(lowerCmd, "status") == 0)
    {
        HandleStatus();
    }
    else if (strcmp(lowerCmd, "help") == 0)
    {
        HandleHelp();
    }
    else if (strlen(lowerCmd) > 0)  /* Ignore empty commands */
    {
        SendString(UNKNOWN_CMD_MSG);
    }

    /* Reset command buffer */
    cmdIndex = 0;
    memset(cmdBuffer, 0, CMD_BUFFER_SIZE);

    /* Show prompt */
    SendString(PROMPT_MSG);
}
