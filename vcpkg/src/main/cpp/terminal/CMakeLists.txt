
cmake_minimum_required(VERSION 3.22.1)

enable_testing()

find_package(GTest CONFIG REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(AllTestsInMain main)