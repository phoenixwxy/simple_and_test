cmake_minimum_required(VERSION 3.22.1)

find_package(GTest REQUIRED)

add_executable(stl_learn stl_learn.cpp)
target_link_libraries(stl_learn GTest::GTest GTest::Main)
#gtest_add_tests(TARGET stl_learn SOURCES stl_learn.cpp)

#add_executable(my_test_target test_main.cpp my_tests.cpp)
#target_link_libraries(my_test_target GTest::GTest GTest::Main)