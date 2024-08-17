cmake_minimum_required(VERSION 3.22.1)

find_package(GTest REQUIRED)

file(GLOB SOURCE_FILES "*.cpp")
add_executable(os_learn ${SOURCE_FILES})
target_link_libraries(os_learn GTest::GTest GTest::Main)