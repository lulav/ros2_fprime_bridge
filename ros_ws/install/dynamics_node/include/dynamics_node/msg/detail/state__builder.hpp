// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dynamics_node:msg/State.idl
// generated code does not contain a copyright notice

#ifndef DYNAMICS_NODE__MSG__DETAIL__STATE__BUILDER_HPP_
#define DYNAMICS_NODE__MSG__DETAIL__STATE__BUILDER_HPP_

#include "dynamics_node/msg/detail/state__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace dynamics_node
{

namespace msg
{

namespace builder
{

class Init_State_v
{
public:
  explicit Init_State_v(::dynamics_node::msg::State & msg)
  : msg_(msg)
  {}
  ::dynamics_node::msg::State v(::dynamics_node::msg::State::_v_type arg)
  {
    msg_.v = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dynamics_node::msg::State msg_;
};

class Init_State_r
{
public:
  Init_State_r()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_State_v r(::dynamics_node::msg::State::_r_type arg)
  {
    msg_.r = std::move(arg);
    return Init_State_v(msg_);
  }

private:
  ::dynamics_node::msg::State msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dynamics_node::msg::State>()
{
  return dynamics_node::msg::builder::Init_State_r();
}

}  // namespace dynamics_node

#endif  // DYNAMICS_NODE__MSG__DETAIL__STATE__BUILDER_HPP_
