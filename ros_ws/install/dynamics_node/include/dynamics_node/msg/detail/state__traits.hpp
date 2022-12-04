// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from dynamics_node:msg/State.idl
// generated code does not contain a copyright notice

#ifndef DYNAMICS_NODE__MSG__DETAIL__STATE__TRAITS_HPP_
#define DYNAMICS_NODE__MSG__DETAIL__STATE__TRAITS_HPP_

#include "dynamics_node/msg/detail/state__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<dynamics_node::msg::State>()
{
  return "dynamics_node::msg::State";
}

template<>
inline const char * name<dynamics_node::msg::State>()
{
  return "dynamics_node/msg/State";
}

template<>
struct has_fixed_size<dynamics_node::msg::State>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<dynamics_node::msg::State>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<dynamics_node::msg::State>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DYNAMICS_NODE__MSG__DETAIL__STATE__TRAITS_HPP_
