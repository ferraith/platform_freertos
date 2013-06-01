// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#include "freertos/port/kernel_wrapper.h"

namespace freertos {

namespace kernel {

  SchedulerState GetSchedulerState() {
    switch (xTaskGetSchedulerState()) {
    case taskSCHEDULER_NOT_STARTED:
      return SchedulerState::kNotStarted;
    case taskSCHEDULER_RUNNING:
      return SchedulerState::kRunning;
    case taskSCHEDULER_SUSPENDED:
      return SchedulerState::kSuspended;
    default:
      return SchedulerState::kUnknown;
    }
  }

}  // namespace kernel

}  // namespace freertos
