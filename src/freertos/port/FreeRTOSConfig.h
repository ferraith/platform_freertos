/*
    FreeRTOS V7.3.0 - Copyright (C) 2012 Real Time Engineers Ltd.

    FEATURES AND PORTS ARE ADDED TO FREERTOS ALL THE TIME.  PLEASE VISIT 
    http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!
    
    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    
    http://www.FreeRTOS.org - Documentation, training, latest versions, license 
    and contact details.  
    
    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell 
    the code with commercial support, indemnification, and middleware, under 
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under 
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/

#ifndef PORT_FREERTOSCONFIG_H_
#define PORT_FREERTOSCONFIG_H_

#include "cmsis_core_lpc17xx/LPC17xx.h"

// Application specific definitions. These definitions should be adjusted for your particular hardware and
// application requirements.
#define configUSE_PREEMPTION                  1
#define configUSE_IDLE_HOOK                   0
#define configMAX_PRIORITIES                  ((unsigned portBASE_TYPE) 5)
#define configUSE_TICK_HOOK                   0
#define configCPU_CLOCK_HZ                    ((unsigned long) 120000000)
#define configTICK_RATE_HZ                    ((portTickType) 100000)
#define configMINIMAL_STACK_SIZE              ((unsigned short) 27)
#define configTOTAL_HEAP_SIZE                 ((size_t) (3 * 1024))
#define configHEAP_MEMORY_SECTION             ".rtos_heap"
#define configMAX_TASK_NAME_LEN               10
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
#define configGENERATE_RUN_TIME_STATS         0

// Set the following definitions to 1 to include the API function, or zero to exclude the API function.
#define INCLUDE_vTaskPrioritySet              1
#define INCLUDE_uxTaskPriorityGet             1
#define INCLUDE_vTaskDelete                   1
#define INCLUDE_vTaskCleanUpResources         1
#define INCLUDE_vTaskSuspend                  1
#define INCLUDE_xTaskResumeFromISR            1
#define INCLUDE_vTaskDelayUntil               1
#define INCLUDE_vTaskDelay                    1
#define INCLUDE_uxTaskGetStackHighWaterMark   1
#define INCLUDE_eTaskStateGet                 1

// Use the system definition, if there is one
#ifdef __NVIC_PRIO_BITS
    #define configPRIO_BITS                   __NVIC_PRIO_BITS
#else
    #define configPRIO_BITS                   5  // 32 priority levels
#endif

// The lowest priority.
#define configKERNEL_INTERRUPT_PRIORITY       (31 << (8 - configPRIO_BITS))
// Priority 5, or 160 as only the top three bits are implemented.
// !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
// See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html.
#define configMAX_SYSCALL_INTERRUPT_PRIORITY  (5 << (8 - configPRIO_BITS))

// Macros required to setup the timer for the run time stats.
extern void vConfigureTimerForRunTimeStats(void);
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()
#define portGET_RUN_TIME_COUNTER_VALUE() LPC_TIM0->TC

#endif  // PORT_FREERTOSCONFIG_H_
