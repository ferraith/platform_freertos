// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

///
/// @brief         This function is an error handler that is invoked when a pure virtual function is called.
/// @return        None
///
extern "C" void __cxa_pure_virtual() {
  while (true);
}
