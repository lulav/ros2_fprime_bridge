// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from dynamics_node:msg/ControlSignal.idl
// generated code does not contain a copyright notice

#ifndef DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__FUNCTIONS_H_
#define DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "dynamics_node/msg/rosidl_generator_c__visibility_control.h"

#include "dynamics_node/msg/detail/control_signal__struct.h"

/// Initialize msg/ControlSignal message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * dynamics_node__msg__ControlSignal
 * )) before or use
 * dynamics_node__msg__ControlSignal__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamics_node
bool
dynamics_node__msg__ControlSignal__init(dynamics_node__msg__ControlSignal * msg);

/// Finalize msg/ControlSignal message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamics_node
void
dynamics_node__msg__ControlSignal__fini(dynamics_node__msg__ControlSignal * msg);

/// Create msg/ControlSignal message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * dynamics_node__msg__ControlSignal__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamics_node
dynamics_node__msg__ControlSignal *
dynamics_node__msg__ControlSignal__create();

/// Destroy msg/ControlSignal message.
/**
 * It calls
 * dynamics_node__msg__ControlSignal__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamics_node
void
dynamics_node__msg__ControlSignal__destroy(dynamics_node__msg__ControlSignal * msg);

/// Check for msg/ControlSignal message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamics_node
bool
dynamics_node__msg__ControlSignal__are_equal(const dynamics_node__msg__ControlSignal * lhs, const dynamics_node__msg__ControlSignal * rhs);

/// Copy a msg/ControlSignal message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamics_node
bool
dynamics_node__msg__ControlSignal__copy(
  const dynamics_node__msg__ControlSignal * input,
  dynamics_node__msg__ControlSignal * output);

/// Initialize array of msg/ControlSignal messages.
/**
 * It allocates the memory for the number of elements and calls
 * dynamics_node__msg__ControlSignal__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamics_node
bool
dynamics_node__msg__ControlSignal__Sequence__init(dynamics_node__msg__ControlSignal__Sequence * array, size_t size);

/// Finalize array of msg/ControlSignal messages.
/**
 * It calls
 * dynamics_node__msg__ControlSignal__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamics_node
void
dynamics_node__msg__ControlSignal__Sequence__fini(dynamics_node__msg__ControlSignal__Sequence * array);

/// Create array of msg/ControlSignal messages.
/**
 * It allocates the memory for the array and calls
 * dynamics_node__msg__ControlSignal__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamics_node
dynamics_node__msg__ControlSignal__Sequence *
dynamics_node__msg__ControlSignal__Sequence__create(size_t size);

/// Destroy array of msg/ControlSignal messages.
/**
 * It calls
 * dynamics_node__msg__ControlSignal__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamics_node
void
dynamics_node__msg__ControlSignal__Sequence__destroy(dynamics_node__msg__ControlSignal__Sequence * array);

/// Check for msg/ControlSignal message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamics_node
bool
dynamics_node__msg__ControlSignal__Sequence__are_equal(const dynamics_node__msg__ControlSignal__Sequence * lhs, const dynamics_node__msg__ControlSignal__Sequence * rhs);

/// Copy an array of msg/ControlSignal messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamics_node
bool
dynamics_node__msg__ControlSignal__Sequence__copy(
  const dynamics_node__msg__ControlSignal__Sequence * input,
  dynamics_node__msg__ControlSignal__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__FUNCTIONS_H_
