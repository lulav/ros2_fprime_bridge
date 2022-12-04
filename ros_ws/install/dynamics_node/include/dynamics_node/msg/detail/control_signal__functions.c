// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from dynamics_node:msg/ControlSignal.idl
// generated code does not contain a copyright notice
#include "dynamics_node/msg/detail/control_signal__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
dynamics_node__msg__ControlSignal__init(dynamics_node__msg__ControlSignal * msg)
{
  if (!msg) {
    return false;
  }
  // u
  return true;
}

void
dynamics_node__msg__ControlSignal__fini(dynamics_node__msg__ControlSignal * msg)
{
  if (!msg) {
    return;
  }
  // u
}

bool
dynamics_node__msg__ControlSignal__are_equal(const dynamics_node__msg__ControlSignal * lhs, const dynamics_node__msg__ControlSignal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // u
  if (lhs->u != rhs->u) {
    return false;
  }
  return true;
}

bool
dynamics_node__msg__ControlSignal__copy(
  const dynamics_node__msg__ControlSignal * input,
  dynamics_node__msg__ControlSignal * output)
{
  if (!input || !output) {
    return false;
  }
  // u
  output->u = input->u;
  return true;
}

dynamics_node__msg__ControlSignal *
dynamics_node__msg__ControlSignal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dynamics_node__msg__ControlSignal * msg = (dynamics_node__msg__ControlSignal *)allocator.allocate(sizeof(dynamics_node__msg__ControlSignal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dynamics_node__msg__ControlSignal));
  bool success = dynamics_node__msg__ControlSignal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dynamics_node__msg__ControlSignal__destroy(dynamics_node__msg__ControlSignal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dynamics_node__msg__ControlSignal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dynamics_node__msg__ControlSignal__Sequence__init(dynamics_node__msg__ControlSignal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dynamics_node__msg__ControlSignal * data = NULL;

  if (size) {
    data = (dynamics_node__msg__ControlSignal *)allocator.zero_allocate(size, sizeof(dynamics_node__msg__ControlSignal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dynamics_node__msg__ControlSignal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dynamics_node__msg__ControlSignal__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
dynamics_node__msg__ControlSignal__Sequence__fini(dynamics_node__msg__ControlSignal__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      dynamics_node__msg__ControlSignal__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

dynamics_node__msg__ControlSignal__Sequence *
dynamics_node__msg__ControlSignal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dynamics_node__msg__ControlSignal__Sequence * array = (dynamics_node__msg__ControlSignal__Sequence *)allocator.allocate(sizeof(dynamics_node__msg__ControlSignal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dynamics_node__msg__ControlSignal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dynamics_node__msg__ControlSignal__Sequence__destroy(dynamics_node__msg__ControlSignal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dynamics_node__msg__ControlSignal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dynamics_node__msg__ControlSignal__Sequence__are_equal(const dynamics_node__msg__ControlSignal__Sequence * lhs, const dynamics_node__msg__ControlSignal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dynamics_node__msg__ControlSignal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dynamics_node__msg__ControlSignal__Sequence__copy(
  const dynamics_node__msg__ControlSignal__Sequence * input,
  dynamics_node__msg__ControlSignal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dynamics_node__msg__ControlSignal);
    dynamics_node__msg__ControlSignal * data =
      (dynamics_node__msg__ControlSignal *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dynamics_node__msg__ControlSignal__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          dynamics_node__msg__ControlSignal__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dynamics_node__msg__ControlSignal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
