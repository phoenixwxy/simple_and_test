cmake_minimum_required(VERSION 3.22.1)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/vcpkg.cmake)

project(cpp_module CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17 -frtti -fexceptions")

add_subdirectory(stl_learn)
add_subdirectory(os_learn)

add_executable(cpp_module test.cpp)
