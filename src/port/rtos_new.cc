// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#include <cstddef>

#include "freertos/FreeRTOS.h"


///
/// @brief         Allocates requested number of bytes. This allocation function is called by new-expressions to
///                allocate memory in which a new object would then be initialized.
/// @param[in]     Size  Number of bytes to allocate
/// @return        Pointer to allocated memory area
///
void *operator new(std::size_t size) throw() {
  return pvPortMalloc(size);
}


///
/// @brief         Allocates requested number of bytes. This allocation function is called by new-expressions to
///                allocate memory in which an array of new objects would then be initialized.
/// @param[in]     size  Number of bytes to allocate
/// @return        Pointer to allocated memory area
///
void *operator new[](std::size_t size) throw() {
  return pvPortMalloc(size);
}
