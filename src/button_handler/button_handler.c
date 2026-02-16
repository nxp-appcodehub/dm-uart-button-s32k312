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

#include "button_handler.h"
#include "led_control.h"
#include "uart_comm.h"
#include "utils.h"

/* Button state tracking for debouncing */
static Dio_LevelType lastOnButtonState = STD_HIGH;
static Dio_LevelType lastOffButtonState = STD_HIGH;

static Dio_LevelType onButtonState = STD_LOW;
static Dio_LevelType offButtonState = STD_LOW;

/* Initialize button states to prevent false triggers on startup */
void InitButtons(void)
{
    lastOnButtonState = Dio_ReadChannel(LED_ON_BUTTON);
    lastOffButtonState = Dio_ReadChannel(LED_OFF_BUTTON);
}

/* Handle ON button press - Turn Green ON, Blue OFF */
void HandleOnButton(void)
{
    /* Send notification first */
    SendButtonPressNotification(BUTTON_TYPE_ON);

    /* Change LED states */
    SetLedGreen(STD_HIGH);
    SetLedBlue(STD_LOW);
    ledStatus = TRUE;

    /* Show prompt again */
    SendString(PROMPT_MSG);
}

/* Handle OFF button press - Turn all LEDs OFF */
void HandleOffButton(void)
{
    /* Send notification first */
    SendButtonPressNotification(BUTTON_TYPE_OFF);

    /* Turn off all LEDs */
    SetAllLeds(STD_LOW);
    ledStatus = FALSE;

    /* Show prompt again */
    SendString(PROMPT_MSG);
}

/* Check button states and handle presses with debouncing */
void CheckButtons(void) {
	boolean onButtonPressed = FALSE;
	boolean offButtonPressed = FALSE;

	/* Read button states */
	onButtonState = Dio_ReadChannel(LED_ON_BUTTON);
	offButtonState = Dio_ReadChannel(LED_OFF_BUTTON);

	if (lastOnButtonState == STD_HIGH && onButtonState == STD_LOW) {
		onButtonPressed = TRUE;
	}

	if (lastOffButtonState == STD_HIGH && offButtonState == STD_LOW) {
		offButtonPressed = TRUE;
	}

	/* Handle button presses */
	if (onButtonPressed)
    {
        Simple_Delay(DEBOUNCE_DELAY);  /* Debounce delay */
        HandleOnButton();
    }
    if (offButtonPressed)
    {
        Simple_Delay(DEBOUNCE_DELAY);  /* Debounce delay */
        HandleOffButton();
    }

    /* Update last button states */
    lastOnButtonState = onButtonState;
    lastOffButtonState = offButtonState;
}
