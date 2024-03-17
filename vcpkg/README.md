# VCPKG

[VCPKG github url](https://github.com/microsoft/vcpkg)

[vcpkg cmake config file](./demo_vcpkg/src/main/cpp/cmake/vcpkg.cmake)

可以快速引入已经包含在VCPKG的三方二进制库，同时可以配置选择动/静态，Debug/Release版本。
同时，也支持配置引入动态保存位置，以及是否是本地保存或单项目配置。

下载及设置vcpkg路径
```cmake
execute_process(COMMAND git clone https://github.com/microsoft/vcpkg
                WORKING_DIRECTORY ${PROJECT_CACHE_PATH}
                COMMAND_ECHO STDOUT)

set(VCPKG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
```

配置文件保存位置
```cmake
set(VCPKG_OVERLAY_TRIPLETS ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/triplets)
```

设置平台类型配置文件名字，可以创建自己的配置文件名字，或者修改vcpkg仓库中的配置文件。
本例子为 `x64-osx`
```cmake
set(VCPKG_TARGET_TRIPLET x64-osx)
```
`x64-osx`文件内容
```cmake
set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)

set(VCPKG_CMAKE_SYSTEM_NAME Darwin)
set(VCPKG_OSX_ARCHITECTURES x86_64)

set(VCPKG_BUILD_TYPE release)
```

对于特殊需要配置编译工具链的编译选项
```cmake
set(VCPKG_CHAINLOAD_TOOLCHAIN_FILE $ENV{ANDROID_NDK_HOME}/build/cmake/android.toolchain.cmake)
```

当使用单独项目配置(manifest)时，防止每次引入vcpkg，每次都要重新编译可以进行如下配置。
另外配置vcpkg自己配置的工具链选项。

```cmake
 set(ENV{VCPKG_BINARY_SOURCES} "clear;files,${VCPKG_ROOT}/archives,readwrite;")
 set(VCPKG_INSTALL_OPTIONS "--allow-unsupported")
 set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
```

**需要注意，使用时修改里面的代理设置和脚本**

cmake和其他命令标准输出的位置。因为Android Studio默认cmake在执行时不输出debug信息。

`build/intermediates/cxx/Debug/l1h1x62h/logs/arm64-v8a/configure_stdout.txt`