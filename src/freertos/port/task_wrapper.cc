// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#include "task_wrapper.h"

extern "C" inline void RunTaskCode(void *parameters) {
    (static_cast<TaskWrapper *>(parameters))->Run();
}

TaskWrapper::TaskWrapper(const char *task_name, unsigned short stack_depth, char priority) {
    xTaskCreate(RunTaskCode, reinterpret_cast<const signed char *>(task_name), stack_depth, static_cast<void *>(this),
                priority, &task_handle_);
}

TaskWrapper::~TaskWrapper() {
  vTaskDelete(task_handle_);
}
