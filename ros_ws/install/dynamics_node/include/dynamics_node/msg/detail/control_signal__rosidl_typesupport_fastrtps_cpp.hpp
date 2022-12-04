// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from dynamics_node:msg/ControlSignal.idl
// generated code does not contain a copyright notice

#ifndef DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "dynamics_node/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "dynamics_node/msg/detail/control_signal__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace dynamics_node
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dynamics_node
cdr_serialize(
  const dynamics_node::msg::ControlSignal & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dynamics_node
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  dynamics_node::msg::ControlSignal & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dynamics_node
get_serialized_size(
  const dynamics_node::msg::ControlSignal & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dynamics_node
max_serialized_size_ControlSignal(
  bool & full_bounded,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace dynamics_node

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dynamics_node
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, dynamics_node, msg, ControlSignal)();

#ifdef __cplusplus
}
#endif

#endif  // DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
