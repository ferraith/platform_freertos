// FreeRTOS Library
// Copyright (C) ferraith. All rights reserved.

#ifndef FREERTOS_PORT_QUEUE_WRAPPER_H_
#define FREERTOS_PORT_QUEUE_WRAPPER_H_

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

namespace freertos {

///
/// @brief         QueueWrapper.
///
class QueueWrapper {
 public:
  ///
  /// @brief         Constructor
  ///
  QueueWrapper() : queue_handle_(nullptr) {}
  ///
  /// @brief         Destructor
  ///
  ~QueueWrapper() {
    if (queue_handle_ != nullptr) {
      Delete();
    }
  }

  ///
  /// @brief         Creates a new queue and allocates the storage required by the new queue.
  /// @param[in]     queue_length  The maximum number of items that the queue can contain.
  /// @param[in]     item_size  The number of bytes each item in the queue will require.
  /// @return        True if the queue was successfully.
  ///
  bool Create(uint32_t queue_length, uint32_t item_size) {
    queue_handle_ = xQueueCreate(queue_length, item_size);
    if (queue_handle_ != nullptr) {
      return true;
    } else {
      return false;
    }
  }
  ///
  /// @brief         Deletes a queue and frees all the memory allocated for storing of items placed on the queue.
  /// @return        None
  ///
  void Delete() {
    vQueueDelete(queue_handle_);
    queue_handle_ = nullptr;
  }
  ///
  /// @brief         Receive an item from a queue. The item is received by copy so a buffer of adequate size must be
  ///                provided.
  /// @param[in]     buffer  Pointer to the buffer into which the received item will be copied.
  /// @param[in]     ticks_to_wait  The maximum amount of time the task should block waiting for an item to receive
  ///                should the queue be empty at the time of the call.
  /// @return        True if an item was successfully received from the queue.
  ///
  bool Receive(void *buffer, uint16_t ticks_to_wait) {
    return xQueueReceive(queue_handle_, buffer, ticks_to_wait) != pdFALSE;
  }
  ///
  /// @brief         Post an item to the back of a queue. The item is queued by copy, not by reference.
  /// @param[in]     item_to_queue  A pointer to the item that is to be placed on the queue.
  /// @param[in]     ticks_to_wait  The maximum amount of time the task should block waiting for space to become
  ///                available on the queue, should it already be full.
  /// @return        True if the item was successfully posted.
  ///
  bool SendToBack(const void *item_to_queue, uint16_t ticks_to_wait) {
    return xQueueSendToBack(queue_handle_, item_to_queue, ticks_to_wait) != pdFALSE;
  }
  ///
  /// @brief         Post an item to the front of a queue. The item is queued by copy, not by reference.
  /// @param[in]     item_to_queue  A pointer to the item that is to be placed on the queue.
  /// @param[in]     ticks_to_wait  The maximum amount of time the task should block waiting for space to become
  ///                available on the queue, should it already be full.
  /// @return        True if the item was successfully posted.
  ///
  bool SendToFront(const void *item_to_queue, uint16_t ticks_to_wait) {
    return xQueueSendToFront(queue_handle_, item_to_queue, ticks_to_wait) != pdFALSE;
  }

 private:
  /// Handle of the created queue
  xQueueHandle queue_handle_;
};

}  // namespace freertos

#endif  // FREERTOS_PORT_QUEUE_WRAPPER_H_
