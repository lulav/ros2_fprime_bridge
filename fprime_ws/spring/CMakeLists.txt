
cmake_minimum_required(VERSION 3.13)
cmake_policy(SET CMP0048 NEW)
project(spring VERSION 1.0.0 LANGUAGES C CXX)

#include("${CMAKE_CURRENT_LIST_DIR}/../cmake/FPrime.cmake")
include("/app/fprime/cmake/FPrime.cmake")
# NOTE: register custom targets between these two lines
#include("${CMAKE_CURRENT_LIST_DIR}/../cmake/FPrime-Code.cmake")
include("/app/fprime/cmake/FPrime-Code.cmake")

# Add component subdirectories
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/spring_types/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/spring_ports/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/controller/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ros2_bridge/")

# Add Topology subdirectory
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")

set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/Top/Main.cpp")
set(MOD_DEPS ${PROJECT_NAME}/Top)

register_fprime_deployment()
# The following compile options will only apply to the deployment executable.
# The extra warnings trigger in core F Prime so we don't apply them there.
target_compile_options("${PROJECT_NAME}" PUBLIC -Wall)
target_compile_options("${PROJECT_NAME}" PUBLIC -Wextra)
target_compile_options("${PROJECT_NAME}" PUBLIC -Werror)
#target_compile_options("${PROJECT_NAME}" PUBLIC -Wshadow)
target_compile_options("${PROJECT_NAME}" PUBLIC -Wconversion)
target_compile_options("${PROJECT_NAME}" PUBLIC -Wsign-conversion)
target_compile_options("${PROJECT_NAME}" PUBLIC -Wformat-security)
target_compile_options("${PROJECT_NAME}" PUBLIC -Wnon-virtual-dtor)
target_compile_options("${PROJECT_NAME}" PUBLIC -Wold-style-cast)
target_compile_options("${PROJECT_NAME}" PUBLIC -Woverloaded-virtual)
target_compile_options("${PROJECT_NAME}" PUBLIC -Wno-unused-parameter)
target_compile_options("${PROJECT_NAME}" PUBLIC -Wundef)
set_property(TARGET "${PROJECT_NAME}" PROPERTY CXX_STANDARD 11)
