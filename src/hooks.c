/*
 * hooks.c
 *
 *  Created on: 20.12.2012
 *      Author: andreas
 */

#include "FreeRTOS.h"
#include "LPC17xx.h"
#include "task.h"

///
/// @brief This function configures a timer that is used as the time base when collecting run time statistical
///        information - basically the percentage of CPU time that each task is utilizing.  It is called automatically
///        when the scheduler is started (assuming configGENERATE_RUN_TIME_STATS is set to 1).
///
void vConfigureTimerForRunTimeStats(void) {
  const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00, TCR_COUNT_ENABLE = 0x01;

  // Power up and feed the timer.
  LPC_SC->PCONP |= 0x02UL;
  LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 & (~(0x3<<2))) | (0x01 << 2);

  // Reset Timer 0
  LPC_TIM0->TCR = TCR_COUNT_RESET;

  // Just count up
  LPC_TIM0->CTCR = CTCR_CTM_TIMER;

  // Prescale to a frequency that is good enough to get a decent resolution, but not too fast so as to overflow all
  // the time.
  LPC_TIM0->PR =  ( configCPU_CLOCK_HZ / 10000UL ) - 1UL;

  // Start the counter.
  LPC_TIM0->TCR = TCR_COUNT_ENABLE;
}


///
/// @brief This function will get called if a task overflows its stack.
///
void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName)
{
  (void) pxTask;
  (void) pcTaskName;

  for(;;);
}