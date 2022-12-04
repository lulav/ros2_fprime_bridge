// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from dynamics_node:msg/ControlSignal.idl
// generated code does not contain a copyright notice

#ifndef DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__STRUCT_HPP_
#define DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__dynamics_node__msg__ControlSignal __attribute__((deprecated))
#else
# define DEPRECATED__dynamics_node__msg__ControlSignal __declspec(deprecated)
#endif

namespace dynamics_node
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ControlSignal_
{
  using Type = ControlSignal_<ContainerAllocator>;

  explicit ControlSignal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->u = 0.0f;
    }
  }

  explicit ControlSignal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->u = 0.0f;
    }
  }

  // field types and members
  using _u_type =
    float;
  _u_type u;

  // setters for named parameter idiom
  Type & set__u(
    const float & _arg)
  {
    this->u = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dynamics_node::msg::ControlSignal_<ContainerAllocator> *;
  using ConstRawPtr =
    const dynamics_node::msg::ControlSignal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dynamics_node::msg::ControlSignal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dynamics_node::msg::ControlSignal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dynamics_node::msg::ControlSignal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dynamics_node::msg::ControlSignal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dynamics_node::msg::ControlSignal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dynamics_node::msg::ControlSignal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dynamics_node::msg::ControlSignal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dynamics_node::msg::ControlSignal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dynamics_node__msg__ControlSignal
    std::shared_ptr<dynamics_node::msg::ControlSignal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dynamics_node__msg__ControlSignal
    std::shared_ptr<dynamics_node::msg::ControlSignal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ControlSignal_ & other) const
  {
    if (this->u != other.u) {
      return false;
    }
    return true;
  }
  bool operator!=(const ControlSignal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ControlSignal_

// alias to use template instance with default allocator
using ControlSignal =
  dynamics_node::msg::ControlSignal_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace dynamics_node

#endif  // DYNAMICS_NODE__MSG__DETAIL__CONTROL_SIGNAL__STRUCT_HPP_
