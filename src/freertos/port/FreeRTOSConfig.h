// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#ifndef FREERTOS_PORT_FREERTOSCONFIG_H_
#define FREERTOS_PORT_FREERTOSCONFIG_H_

#include "cmsis_core_lpc17xx/LPC17xx.h"

// Application specific definitions. These definitions should be adjusted for your particular hardware and
// application requirements.
#define configUSE_PREEMPTION                  1
#define configUSE_IDLE_HOOK                   0
#define configMAX_PRIORITIES                  ((unsigned portBASE_TYPE) 5)
#define configUSE_TICK_HOOK                   0
#define configCPU_CLOCK_HZ                    ((uint32_t) 120000000)
#define configTICK_RATE_HZ                    ((portTickType) 1000)
#define configMINIMAL_STACK_SIZE              ((uint16_t) 27)
#define configTOTAL_HEAP_SIZE                 ((size_t) (3 * 1024))
#define configHEAP_MEMORY_SECTION             ".rtos_heap"
#define configMAX_TASK_NAME_LEN               18
#define configUSE_TRACE_FACILITY              0
#define configUSE_16_BIT_TICKS                0
#define configIDLE_SHOULD_YIELD               0
#define configUSE_CO_ROUTINES                 0
#define configUSE_MUTEXES                     1

#define configMAX_CO_ROUTINE_PRIORITIES       2

#define configUSE_COUNTING_SEMAPHORES         0
#define configUSE_ALTERNATIVE_API             0
#define configCHECK_FOR_STACK_OVERFLOW        2
#define configUSE_RECURSIVE_MUTEXES           0
#define configQUEUE_REGISTRY_SIZE             0
#define configGENERATE_RUN_TIME_STATS         1

// Set the following definitions to 1 to include the API function
#define INCLUDE_vTaskPrioritySet              1
#define INCLUDE_uxTaskPriorityGet             1
#define INCLUDE_vTaskDelete                   1
#define INCLUDE_vTaskCleanUpResources         1
#define INCLUDE_vTaskSuspend                  1
#define INCLUDE_xTaskResumeFromISR            1
#define INCLUDE_vTaskDelayUntil               1
#define INCLUDE_vTaskDelay                    1
#define INCLUDE_uxTaskGetStackHighWaterMark   1
#define INCLUDE_pcTaskGetTaskName             1
#define INCLUDE_eTaskGetState                 1

// Number of Bits used for Priority Levels
#define configPRIO_BITS                       __NVIC_PRIO_BITS

// The lowest priority
#define configKERNEL_INTERRUPT_PRIORITY       (31 << (8 - configPRIO_BITS))
// Priority 5, or 160 as only the top three bits are implemented.
// !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
// See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html.
#define configMAX_SYSCALL_INTERRUPT_PRIORITY  (5 << (8 - configPRIO_BITS))

// Macros required to setup the timer for the run time stats.
#if (configGENERATE_RUN_TIME_STATS == 1)
extern void vConfigureTimerForRunTimeStats();
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()
#define portGET_RUN_TIME_COUNTER_VALUE() LPC_TIM0->TC
#endif

#endif  // FREERTOS_PORT_FREERTOSCONFIG_H_
