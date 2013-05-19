// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lpc17xx/lpc17xx_clkpwr.h"
#include "lpc17xx/lpc17xx_timer.h"

#if (configGENERATE_RUN_TIME_STATS == 1)
///
/// @brief         This function configures a timer that is used as the time base when collecting run time statistical
///                information - basically the percentage of CPU time that each task is utilizing. It is called
///                automatically when the scheduler is started.
/// @return        None
///
void vConfigureTimerForRunTimeStats() {
  TIM_TIMERCFG_Type config = {
    .PrescaleOption = TIM_PRESCALE_TICKVAL,
    .PrescaleValue = (configCPU_CLOCK_HZ / (configTICK_RATE_HZ * 10))
  };

  // Configure Timer 0
  TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &config);
  // Increase timer clock to CPU clock to improve measurement precision
  CLKPWR_SetPCLKDiv(CLKPWR_PCLKSEL_TIMER0, CLKPWR_PCLKSEL_CCLK_DIV_1);
  // Start Timer 0
  TIM_Cmd(LPC_TIM0, ENABLE);
}
#endif


///
/// @brief         This function will get called if a task overflows its stack.
/// @param[in]     pxTask      The handle of the task which overflows its stack
/// @param[in]     pcTaskName  The name of the task which overflows its stack
/// @return        None
///
void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName) {
  (void) pxTask;
  (void) pcTaskName;

  for (;;);
}
