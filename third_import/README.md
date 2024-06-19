# 3rd party module import

在源码目录添加对应的路径，然后在CmakeLists.txt中添加

将动态库放在对应版本路径下。
```shell
import_lib/libs/arm64-v8a
```

添加对应引入的三方库名，用于编译时使用，可以和应用的库同名
```cmake
add_library(import_lib SHARED IMPORTED)
set_target_properties(import_lib PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libsimple_third.so)
```

目标中直接应用该库和其头文件
```cmake
add_library(import_simple SHARED ImportSimple.cpp)
target_link_libraries(import_simple import_lib log)
target_include_directories(import_simple PRIVATE libs/include)
target_include_directories(import_simple PUBLIC ImportSimple.h)
```