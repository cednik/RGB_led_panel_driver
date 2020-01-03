/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    RGB_led_panel_driver.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"

#include "FreeRTOS.h"
#include "task.h"

#define STACK_SIZE 1024

#include "print.hpp"

void task_blink_r(void*) {
	BOARD_LED_RED_GPIO_PORT->PCR[BOARD_LED_RED_GPIO_PIN] = PORT_PCR_MUX(kPORT_MuxAsGpio);
	LED_RED_INIT(LOGIC_LED_ON);
	for(;;) {
		vTaskDelay(500/portTICK_PERIOD_MS);
		LED_RED_TOGGLE();
		print("red {}\n", GPIO_PinRead(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN));
	}
}

void task_blink_b(void*) {
	BOARD_LED_BLUE_GPIO_PORT->PCR[BOARD_LED_BLUE_GPIO_PIN] = PORT_PCR_MUX(kPORT_MuxAsGpio);
	LED_BLUE_INIT(LOGIC_LED_ON);
	for(;;) {
		vTaskDelay(333/portTICK_PERIOD_MS);
		LED_BLUE_TOGGLE();
		print("blue {}\n", GPIO_PinRead(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN));
	}
}

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    print("\nRGB led panel driver\n\t{} {}\n", __DATE__, __TIME__);

    xTaskCreate(task_blink_r, "blinkR", STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(task_blink_b, "blinkB", STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

	vTaskStartScheduler();

	/* Should never get here! */
	for(;;);
    return 0;
}
