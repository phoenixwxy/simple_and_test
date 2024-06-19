
add_library(simple_third SHARED SimpleThirdLib.cpp)
target_include_directories(simple_third PUBLIC SimpleThirdLib.h)
target_link_libraries(simple_third log)