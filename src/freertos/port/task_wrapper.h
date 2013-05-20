// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#ifndef FREERTOS_PORT_TASK_WRAPPER_H_
#define FREERTOS_PORT_TASK_WRAPPER_H_

#include "common/class_helper.h"
#include "freertos/Freertos.h"
#include "freertos/task.h"

namespace freertos {

///
/// @brief         TaskWrapper.
///
class TaskWrapper {
 public:
  /// Possible states that a task can exist in
  enum class TaskState {
    kReady,
    kRunning,
    kBlocked,
    kSuspended,
    kDeleted,
    kUnknown
  };

  ///
  /// @brief         Constructor
  ///
  TaskWrapper() : task_handle_(nullptr) {}
  ///
  /// @brief         Destructor
  ///
  virtual ~TaskWrapper() {
    if (task_handle_ != nullptr) {
      Delete();
    }
  }

#if (INCLUDE_vTaskDelay == 1)
  ///
  /// @brief         Delay a task for a given amount of time.
  /// @param[in]     delay_time  The amount of time, in milliseconds, that the calling task should block
  /// @return        None
  ///
  static void Delay(uint16_t delay_time) {
    vTaskDelay(delay_time / portTICK_RATE_MS);
}
#endif
#if (INCLUDE_vTaskDelayUntil == 1)
  ///
  /// @brief         Delay a task until a specified time. This method can be used by cyclic tasks to ensure a constant
  ///                execution frequency.
  /// @param[in]     previous_wake_time  Pointer to a variable that holds the time at which the task was last unblocked
  /// @param[in]     time_increment  The cycle time period in milliseconds - the task will be unblocked at time
  ///                (previous_wake_time + time_increment)
  /// @return        None
  ///
  static void DelayUntil(uint32_t *previous_wake_time, uint32_t time_increment) {
    vTaskDelayUntil(previous_wake_time, time_increment / portTICK_RATE_MS);
  }
#endif
#if (INCLUDE_uxTaskPriorityGet == 1)
  ///
  /// @brief         Obtains the priority of the task.
  /// @return        The priority of the task
  ///
  uint32_t GetPriority() {
    return uxTaskPriorityGet(task_handle_);
  }
#endif
#if (INCLUDE_pcTaskGetTaskName == 1)
  ///
  /// @brief         Obtains the name of the task.
  /// @return        A pointer to the subject tasks name, which is a standard NULL terminated C string
  ///
  signed char *GetName() {
    return pcTaskGetTaskName(task_handle_);
  }
#endif
#if (INCLUDE_eTaskGetState == 1)
  ///
  /// @brief         Obtains the current state of the task.
  /// @return        The state in which the task existed at the time GetState() was executed
  ///
  TaskState GetState();
#endif
  ///
  /// @brief         Obtains the count of ticks since vTaskStartScheduler was called.
  /// @return        The count of ticks
  ///
  static uint32_t GetTickCount() {
    return xTaskGetTickCount();
  }
  ///
  /// @brief         Obtains the count of ticks since vTaskStartScheduler was called that can be called from within an
  ///                ISR.
  /// @return        The count of ticks
  ///
  static uint32_t GetTickCountFromISR() {
    return xTaskGetTickCountFromISR();
  }
#if (INCLUDE_vTaskSuspend == 1)
  ///
  /// @brief         Resumes the suspended task.
  /// @return        None
  ///
  void Resume() {
    vTaskResume(task_handle_);
  }
#endif
#if ((INCLUDE_xTaskResumeFromISR == 1) && (INCLUDE_vTaskSuspend == 1))
  ///
  /// @brief         Resumes the suspended task that can be called from within an ISR.
  /// @return        True if resuming the task should result in a context switch, otherwise false. This is used by the
  ///                ISR to determine if a context switch may be required following the ISR.
  ///
  bool ResumeFromISR() {
    return xTaskResumeFromISR(task_handle_) != pdFALSE;
  }
#endif
  ///
  /// @brief         Contains in an inherited class the code which will be executed in the task. Tasks must be
  ///                implemented to never return.
  /// @return        None
  ///
  virtual void Run() = 0;
#if (INCLUDE_vTaskPrioritySet == 1)
  ///
  /// @brief         Set the priority of the task. A context switch will occur before the method returns if the
  ///                priority being set is higher than the currently executing task.
  /// @param[in]     new_priority  The priority to which the task will be set
  /// @return        None
  ///
  void SetPriority(uint32_t new_priority) {
    vTaskPrioritySet(task_handle_, new_priority);
  }
#endif
#if (INCLUDE_vTaskSuspend == 1)
  ///
  /// @brief         Suspend the task. When suspended the task will never get any microcontroller processing time, no
  ///                matter what its priority.
  /// @return        None
  void Suspend() {
    vTaskSuspend(task_handle_);
  }
#endif

 protected:
  ///
  /// @brief         Creates a new task and add it to the list of tasks that are ready to run.
  /// @param[in]     task_name  Descriptive name for the task
  /// @param[in]     stack_depth  Size of the task stack specified as the number of variables the stack can hold -
  ///                not the number of bytes
  /// @param[in]     priority  Priority at which the task should run
  /// @return        True if the task was successfully created and added to a ready list, otherwise an error code
  ///                defined in the file projdefs.h
  ///
  bool Create(const char *task_name, uint16_t stack_depth, uint32_t priority);
#if (INCLUDE_vTaskDelete == 1)
  ///
  /// @brief         Removes a task from the RTOS kernels management. The task being deleted will be removed from all
  ///                ready, blocked, suspended and event lists.
  /// @return        None
  ///
  void Delete() {
    vTaskDelete(task_handle_);
    task_handle_ = NULL;
  }
#endif

 private:
  /// Handle of the created task
  xTaskHandle task_handle_;
  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(TaskWrapper);
};

}  // namespace freertos

#endif  // FREERTOS_PORT_TASK_WRAPPER_H_
