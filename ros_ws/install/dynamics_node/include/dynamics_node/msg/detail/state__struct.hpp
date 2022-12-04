// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from dynamics_node:msg/State.idl
// generated code does not contain a copyright notice

#ifndef DYNAMICS_NODE__MSG__DETAIL__STATE__STRUCT_HPP_
#define DYNAMICS_NODE__MSG__DETAIL__STATE__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__dynamics_node__msg__State __attribute__((deprecated))
#else
# define DEPRECATED__dynamics_node__msg__State __declspec(deprecated)
#endif

namespace dynamics_node
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct State_
{
  using Type = State_<ContainerAllocator>;

  explicit State_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->r = 0.0f;
      this->v = 0.0f;
    }
  }

  explicit State_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->r = 0.0f;
      this->v = 0.0f;
    }
  }

  // field types and members
  using _r_type =
    float;
  _r_type r;
  using _v_type =
    float;
  _v_type v;

  // setters for named parameter idiom
  Type & set__r(
    const float & _arg)
  {
    this->r = _arg;
    return *this;
  }
  Type & set__v(
    const float & _arg)
  {
    this->v = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dynamics_node::msg::State_<ContainerAllocator> *;
  using ConstRawPtr =
    const dynamics_node::msg::State_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dynamics_node::msg::State_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dynamics_node::msg::State_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dynamics_node::msg::State_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dynamics_node::msg::State_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dynamics_node::msg::State_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dynamics_node::msg::State_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dynamics_node::msg::State_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dynamics_node::msg::State_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dynamics_node__msg__State
    std::shared_ptr<dynamics_node::msg::State_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dynamics_node__msg__State
    std::shared_ptr<dynamics_node::msg::State_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const State_ & other) const
  {
    if (this->r != other.r) {
      return false;
    }
    if (this->v != other.v) {
      return false;
    }
    return true;
  }
  bool operator!=(const State_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct State_

// alias to use template instance with default allocator
using State =
  dynamics_node::msg::State_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace dynamics_node

#endif  // DYNAMICS_NODE__MSG__DETAIL__STATE__STRUCT_HPP_
