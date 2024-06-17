cmake_minimum_required(VERSION 3.22.1)


# debug and print for env
message("PhoenixDebug CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("PhoenixDebug CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")

include(${CMAKE_CURRENT_SOURCE_DIR}/../../../../cmake/vcpkg.cmake)

project("demo_vcpkg")


add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        demo_vcpkg.cpp)


target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        android
        log)


add_subdirectory(terminal)