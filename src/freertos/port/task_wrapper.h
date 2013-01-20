// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#ifndef PORT_TASK_WRAPPER_H_
#define PORT_TASK_WRAPPER_H_

#include "common/class_helper.h"
#include "freertos/Freertos.h"
#include "freertos/task.h"

class TaskWrapper {
 public:
  ///
  ///
  ///
  TaskWrapper(const char *task_name, unsigned short stack_depth, char priority);
  ///
  ///
  ///
  virtual ~TaskWrapper();
  ///
  ///
  ///
  virtual void Run() = 0;

 private:
  ///
  xTaskHandle task_handle_;
};

#endif  // PORT_TASK_WRAPPER_H_
