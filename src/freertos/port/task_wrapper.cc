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

}  // namespace freertos
