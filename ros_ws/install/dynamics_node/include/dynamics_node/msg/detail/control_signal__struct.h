// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dynamics_node:msg/ControlSignal.idl
// generated code does not contain a copyright notice

#ifndef DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__STRUCT_H_
#define DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/ControlSignal in the package dynamics_node.
typedef struct dynamics_node__msg__ControlSignal
{
  float u;
} dynamics_node__msg__ControlSignal;

// Struct for a sequence of dynamics_node__msg__ControlSignal.
typedef struct dynamics_node__msg__ControlSignal__Sequence
{
  dynamics_node__msg__ControlSignal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dynamics_node__msg__ControlSignal__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__STRUCT_H_
