// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#include <cstddef>

#include "freertos/FreeRTOS.h"

///
/// @brief         Deallocates storage. This allocation function is called by delete-expressions to deallocate memory
///                after destructing a scalar object.
/// @param[in]     ptr  Pointer to a memory area to deallocate or a null pointer.
/// @return        None
///
void operator delete(void *ptr) throw() {
  vPortFree(ptr);
}

///
/// @brief         Deallocates storage. This allocation function are called by delete-expressions to deallocate memory
///                after destructing an array of dynamic objects.
/// @param[in]     ptr  Pointer to a memory area to deallocate or a null pointer.
/// @return        None
///
void operator delete[](void *ptr) throw() {
  vPortFree(ptr);
}
