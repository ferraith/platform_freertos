// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#include "freertos/port/task_wrapper.h"

namespace freertos {

extern "C" inline void RunTaskCode(void *parameters) {
    (static_cast<TaskWrapper *>(parameters))->Run();
}

bool TaskWrapper::Create(const char *task_name, uint16_t stack_depth, uint32_t priority) {
    return xTaskCreate(RunTaskCode, reinterpret_cast<const signed char *>(task_name), stack_depth,
                       static_cast<void *>(this), priority, &task_handle_) != pdFALSE;
}

#if (INCLUDE_eTaskGetState == 1)
TaskWrapper::TaskState TaskWrapper::GetState() {
  switch (eTaskGetState(task_handle_)) {
  case eReady:
    return TaskState::kReady;
  case eRunning:
    return TaskState::kRunning;
  case eBlocked:
    return TaskState::kBlocked;
  case eSuspended:
    return TaskState::kSuspended;
  case eDeleted:
    return TaskState::kDeleted;
  default:
    return TaskState::kUnknown;
  }
}
#endif

}  // namespace freertos
