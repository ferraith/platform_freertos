// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#ifndef FREERTOS_PORT_TASK_WRAPPER_H_
#define FREERTOS_PORT_TASK_WRAPPER_H_

#include "common/class_helper.h"
#include "freertos/Freertos.h"
#include "freertos/task.h"

namespace freertos {

///
/// @brief         Wraps all functionality of task creation and handling provided by FreeRTOS.
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

#if (configUSE_APPLICATION_TASK_TAG == 1)
  ///
  /// @brief         Calls the hook function associated with the task.
  /// @param[in]     param  The value to pass to the hook function. This can be a pointer to a structure, or simply a
  ///                numeric value
  /// @return        A value which is returned from the hook function. The meaning of the value depends on the
  ///                implementation of the hook function.
  ///
  uint32_t CallApplicationTaskHook(void *param) { return xTaskCallApplicationTaskHook(task_handle_, param); }
#endif
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
#if ((INCLUDE_xTaskResumeFromISR == 1) && (INCLUDE_vTaskSuspend == 1))
  ///
  /// @brief         Resumes the suspended task.
  /// @return        True if resuming the task should result in a context switch, otherwise false. This is used by the
  ///                ISR to determine if a context switch may be required following the ISR.
  ///
  bool Resume() {
    if (portIS_ISR_ACTIVE()) {
      return xTaskResumeFromISR(task_handle_) != pdFALSE;
    } else {
      vTaskResume(task_handle_);
      return false;
    }
  }
#endif
  ///
  /// @brief         Contains in an inherited class the code which will be executed in the task. Tasks must be
  ///                implemented to never return.
  /// @return        None
  ///
  virtual void Run() = 0;
#if (INCLUDE_vTaskSuspend == 1)
  ///
  /// @brief         Suspend the task. When suspended the task will never get any microcontroller processing time, no
  ///                matter what its priority.
  /// @return        None
  void Suspend() {
    vTaskSuspend(task_handle_);
  }
#endif

#if (configUSE_APPLICATION_TASK_TAG == 1)
  ///
  /// @brief         Returns the tag value associated with the task.
  /// @return        The tag value of the task
  ///
  pdTASK_HOOK_CODE application_task_tag() const { return xTaskGetApplicationTaskTag(task_handle_); }
#endif
#if (configUSE_APPLICATION_TASK_TAG == 1)
  ///
  /// @brief         Assigns a tag value to the task.
  /// @param[in]     The value being assigned to the task tag
  /// @return        None
  ///
  void set_application_task_tag(pdTASK_HOOK_CODE tag_value) const {
    vTaskSetApplicationTaskTag(task_handle_, tag_value);
  }
#endif
#if (INCLUDE_uxTaskGetStackHighWaterMark == 1)
  ///
  /// @brief         Returns the minimum amount of remaining stack space that was available to the task since the task
  ///                started executing.
  /// @return        The value returned is the high water mark in words
  ///
  uint32_t stack_high_water_mark() const { return uxTaskGetStackHighWaterMark(task_handle_); }
#endif
#if (INCLUDE_pcTaskGetTaskName == 1)
  ///
  /// @brief         Obtains the name of the task.
  /// @return        A pointer to the subject tasks name, which is a standard NULL terminated C string
  ///
  char *task_name() const { return reinterpret_cast<char *>(pcTaskGetTaskName(task_handle_)); }
#endif
#if (INCLUDE_uxTaskPriorityGet == 1)
  ///
  /// @brief         Obtains the priority of the task.
  /// @return        The priority of the task
  ///
  uint32_t task_priority() const { return uxTaskPriorityGet(task_handle_); }
#endif
#if (INCLUDE_vTaskPrioritySet == 1)
  ///
  /// @brief         Set the priority of the task. A context switch will occur before the method returns if the
  ///                priority being set is higher than the currently executing task.
  /// @param[in]     new_task_priority  The priority to which the task will be set
  /// @return        None
  ///
  void set_task_priority(uint32_t new_task_priority) const { vTaskPrioritySet(task_handle_, new_task_priority); }
#endif
#if (INCLUDE_eTaskGetState == 1)
  ///
  /// @brief         Obtains the current state of the task.
  /// @return        The state in which the task existed at the time GetState() was executed
  ///
  TaskState task_state() const;
#endif

 protected:
  ///
  /// @brief         Constructor.
  /// @param[in]     task_name  Descriptive name for the task
  ///
  explicit TaskWrapper(const char *task_name) : kTaskName(task_name), task_handle_(nullptr) {}
  ///
  /// @brief         Destructor.
  ///
  virtual ~TaskWrapper() {
    if (task_handle_ != nullptr) {
      Delete();
    }
  }

  ///
  /// @brief         Creates a new task and add it to the list of tasks that are ready to run.
  /// @param[in]     priority  Priority at which the task should run
  /// @param[in]     stack_depth  Size of the task stack specified as the number of variables the stack can hold
  /// @return        True if the task was successfully created and added to a ready list, otherwise an error code
  ///                defined in the file projdefs.h
  ///
  bool Create(uint32_t priority, uint16_t stack_depth);
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
  /// Descriptive name for the task
  const char *kTaskName;
  /// Handle of the created task
  xTaskHandle task_handle_;
  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(TaskWrapper);
};

}  // namespace freertos

#endif  // FREERTOS_PORT_TASK_WRAPPER_H_
