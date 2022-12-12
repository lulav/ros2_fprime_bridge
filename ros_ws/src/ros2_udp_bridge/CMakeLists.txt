cmake_minimum_required(VERSION 3.5)
project(ros2_udp_bridge)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(dynamics_node REQUIRED)
find_package(Protobuf REQUIRED)

# build the protobuf messages
set(SCHEMAS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../common/autogen/schemas/spring")
set(PROTO_VERSION "proto3")

set(PROTO_DYN "${SCHEMAS_DIR}/${PROTO_VERSION}/*.proto")

file(GLOB_RECURSE ProtoFiles "${PROTO_DYN}")
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${ProtoFiles})
add_library(proto STATIC ${ProtoSources} ${ProtoHeaders})
target_link_libraries(proto ${PROTOBUF_LIBRARY})

# add udp files
set(UDP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../common/lulav_comm/udp/src")
set(UDP_FILES ${UDP_DIR}/udp_client.cpp ${UDP_DIR}/udp_server.cpp)
add_library(udp STATIC ${UDP_FILES})

add_executable(bridge src/bridge.cpp)
ament_target_dependencies(bridge rclcpp std_msgs dynamics_node)

target_link_libraries(bridge udp)
target_link_libraries(bridge proto)

install(TARGETS
  bridge
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
