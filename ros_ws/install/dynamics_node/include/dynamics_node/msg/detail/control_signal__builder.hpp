// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dynamics_node:msg/ControlSignal.idl
// generated code does not contain a copyright notice

#ifndef DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__BUILDER_HPP_
#define DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__BUILDER_HPP_

#include "dynamics_node/msg/detail/control_signal__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace dynamics_node
{

namespace msg
{

namespace builder
{

class Init_ControlSignal_u
{
public:
  Init_ControlSignal_u()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::dynamics_node::msg::ControlSignal u(::dynamics_node::msg::ControlSignal::_u_type arg)
  {
    msg_.u = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dynamics_node::msg::ControlSignal msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dynamics_node::msg::ControlSignal>()
{
  return dynamics_node::msg::builder::Init_ControlSignal_u();
}

}  // namespace dynamics_node

#endif  // DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__BUILDER_HPP_
