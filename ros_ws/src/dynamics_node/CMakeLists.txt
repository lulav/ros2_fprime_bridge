cmake_minimum_required(VERSION 3.5)
project(dynamics_node)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/ControlSignal.msg"
  "msg/State.msg"
)

# add example code generated files
set(EXAMPLE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../examples/spring_mass_dumper/src")
set(EXAMPLE_FILES ${EXAMPLE_DIR}/dynamics.cpp)
add_library(example STATIC ${EXAMPLE_FILES})

add_executable(dynamics src/dynamics_node.cpp)
ament_target_dependencies(dynamics rclcpp)

rosidl_target_interfaces(dynamics ${PROJECT_NAME} "rosidl_typesupport_cpp")

target_link_libraries(dynamics example)

install(TARGETS
  dynamics
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
