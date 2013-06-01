// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#ifndef FREERTOS_PORT_KERNEL_WRAPPER_H_
#define FREERTOS_PORT_KERNEL_WRAPPER_H_

#include "common/class_helper.h"
#include "freertos/Freertos.h"
#include "freertos/task.h"

namespace freertos {

///
/// @brief         Wraps all functionality to control the kernel and to retrieve status information about it which
///                are provided by FreeRTOS.
///
namespace kernel {

  /// Possible states of the scheduler
  enum class SchedulerState {
    kNotStarted,
    kRunning,
    kSuspended,
    kUnknown
  };

  ///
  /// @brief         Enables all maskable interrupts.
  /// @return        None
  ///
  inline void EnableInterrupts() { taskENABLE_INTERRUPTS(); }
  ///
  /// @brief         Stops the RTOS kernel tick. All created tasks will be automatically deleted and multitasking will
  ///                stop.
  /// @return        None
  ///
  inline void EndScheduler() { vTaskEndScheduler(); }
  ///
  /// @brief         Start of a critical code region. Preemptive context switches cannot occur when in a critical
  ///                region.
  /// @return        None
  ///
  inline void EnterCriticalSection() { taskENTER_CRITICAL(); }
  ///
  /// @brief         End of a critical code region. Preemptive context switches cannot occur when in a critical
  ///                region.
  /// @return        None
  ///
  inline void ExitCriticalSection() { taskEXIT_CRITICAL(); }
  ///
  /// @brief         Disables all maskable interrupts.
  /// @return        None
  ///
  inline void DisableInterrupts() { taskDISABLE_INTERRUPTS(); }
#if (INCLUDE_xTaskGetCurrentTaskHandle  == 1)
  ///
  /// @brief         Returns the handle of the currently running (calling) task.
  /// @return        The handle of the currently running task
  ///
  inline xTaskHandle GetCurrentTaskHandle() { return xTaskGetCurrentTaskHandle(); }
#endif
#if (INCLUDE_xTaskGetIdleTaskHandle  == 1)
  ///
  /// @brief         Returns the task handle associated with the Idle task.
  /// @return        The task handle associated with the Idle task
  ///
  inline xTaskHandle GetIdleTaskHandle() { return xTaskGetIdleTaskHandle(); }
#endif
  ///
  /// @brief         Returns the number of tasks which are currently managed by the RTOS kernel.
  /// @return        The number of tasks
  ///
  inline uint32_t GetNumberOfTasks() { return uxTaskGetNumberOfTasks(); }
#if (configGENERATE_RUN_TIME_STATS  == 1)
  ///
  /// @brief         Returns run time statistics about each task managed by the RTOS kernel.
  /// @param[in]     writer_buffer  A buffer into which the execution times will be written, in ASCII form. This buffer
  ///                is assumed to be large enough to contain the generated report.
  /// @return        None
  ///
  inline void GetRunTimeStats(char *write_buffer) {
    vTaskGetRunTimeStats(reinterpret_cast<signed char *>(write_buffer));
  }
#endif
  ///
  /// @brief         Returns the current state of the scheduler.
  /// @return        The state of the scheduler
  ///
  SchedulerState GetSchedulerState();
#if (configUSE_TRACE_FACILITY == 1)
  ///
  /// @brief         Lists all the current tasks, along with their current state and stack usage high water mark.
  /// @param[in]     write_buffer  A buffer into which the above mentioned details will be written, in ASCII form. This
  ///                buffer is assumed to be large enough to contain the generated report.
  /// @return        None
  ///
  inline void GetTaskList(char *write_buffer) { vTaskList(reinterpret_cast<signed char *>(write_buffer)); }
#endif
  ///
  /// @brief         Obtains the count of ticks since scheduler was started.
  /// @return        The count of ticks
  ///
  inline uint32_t GetTickCount() {
    if (portIS_ISR_ACTIVE()) {
      return xTaskGetTickCountFromISR();
    } else {
      return xTaskGetTickCount();
    }
  }
  ///
  /// @brief         Resumes real time kernel activity.
  /// @return        If resuming the scheduler caused a context switch then true is returned, otherwise false is
  ///                returned.
  ///
  inline bool ResumeAllTasks() { return xTaskResumeAll() != pdFALSE; }
  ///
  /// @brief         Starts the RTOS kernel tick processing. After calling the RTOS kernel has control over which tasks
  ///                are executed and when.
  /// @return        None
  ///
  inline void StartScheduler() { vTaskStartScheduler(); }
  ///
  /// @brief         If the RTOS is configured to use tickless idle functionality then the tick interrupt will be
  ///                stopped, and the microcontroller placed into a low power state, whenever the Idle task is the only
  ///                task able to execute. Upon exiting the low power state the tick count value must be corrected to
  ///                account for the time that passed while it was stopped.
  /// @param[in]     The number of RTOS ticks that have passed since the tick interrupt was stopped. For correct
  ///                operation the parameter must be less than or equal to the portSUPPRESS_TICKS_AND_SLEEP() parameter.
  /// @return        None
  ///
#if (configUSE_16_BIT_TICKS == 1)
  inline void StepTick(uint16_t ticks_to_jump) { vTaskStepTick(ticks_to_jump); }
#else
  inline void StepTick(uint32_t ticks_to_jump) { vTaskStepTick(ticks_to_jump); }
#endif
  ///
  /// @brief         Suspends all real time kernel activity while keeping interrupts enabled.
  /// @return        None
  ///
  inline void SuspendAllTasks() { vTaskSuspendAll(); }
  ///
  /// @brief         Forces a context switch.
  /// @return        None
  ///
  inline void Yield() { taskYIELD(); }

}  // namespace kernel

}  // namespace freertos

#endif  // FREERTOS_PORT_KERNEL_WRAPPER_H_
