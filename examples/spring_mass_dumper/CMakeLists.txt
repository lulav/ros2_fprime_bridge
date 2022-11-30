cmake_minimum_required (VERSION 3.10)

set(PROJECT "spring_mass_dumper")

project(${PROJECT})

set(SOURCES_DIR "src/")
set(HEADERS_DIR "include/")

file(GLOB SOURCES "${SOURCES_DIR}*.cpp")
file(GLOB HEADERS "${HEADERS_DIR}*.hpp")

add_library(Lib ${SOURCES} ${HEADERS})

add_executable(${PROJECT} main.cpp)

target_link_libraries (${PROJECT} LINK_PUBLIC Lib)