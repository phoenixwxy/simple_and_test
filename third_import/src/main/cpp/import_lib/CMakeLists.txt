
add_library(import_lib SHARED IMPORTED)
set_target_properties(import_lib PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libsimple_third.so)


add_executable(test_import test_import.cpp)
target_link_libraries(test_import import_lib)
target_include_directories(test_import PRIVATE libs/include)

add_library(import_simple SHARED ImportSimple.cpp)
target_link_libraries(import_simple import_lib log)
target_include_directories(import_simple PRIVATE libs/include)
target_include_directories(import_simple PUBLIC ImportSimple.h)