// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#include <cstddef>

#include "freertos/FreeRTOS.h"

<<<<<<< HEAD
using std::size_t;

=======
>>>>>>> 97fb2a1a2c8afda158ad4c1257642b9f75cc105b
///
/// @brief         Allocates requested number of bytes. This allocation function is called by new-expressions to
///                allocate memory in which a new object would then be initialized.
/// @param[in]     Size  Number of bytes to allocate
/// @return        Pointer to allocated memory area
///
<<<<<<< HEAD
void *operator new(size_t size) throw() {
=======
void *operator new(std::size_t size) throw() {
>>>>>>> 97fb2a1a2c8afda158ad4c1257642b9f75cc105b
  return pvPortMalloc(size);
}

///
/// @brief         Allocates requested number of bytes. This allocation function is called by new-expressions to
///                allocate memory in which an array of new objects would then be initialized.
/// @param[in]     size  Number of bytes to allocate
/// @return        Pointer to allocated memory area
///
<<<<<<< HEAD
void *operator new[](size_t size) throw() {
=======
void *operator new[](std::size_t size) throw() {
>>>>>>> 97fb2a1a2c8afda158ad4c1257642b9f75cc105b
  return pvPortMalloc(size);
}
