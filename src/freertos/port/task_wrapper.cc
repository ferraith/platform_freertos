// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#include "freertos/port/task_wrapper.h"

namespace freertos {

extern "C" inline void RunTaskCode(void *parameters) {
    (static_cast<TaskWrapper *>(parameters))->Run();
}

bool TaskWrapper::Create(uint32_t priority) {
    return xTaskCreate(RunTaskCode, reinterpret_cast<const signed char *>(kTaskName), kStackDepth,
                       static_cast<void *>(this), priority, &task_handle_) != pdFALSE;
}

#if (INCLUDE_eTaskGetState == 1)
TaskWrapper::TaskState TaskWrapper::task_state() const {
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
