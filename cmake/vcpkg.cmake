# Get the current file's path
get_filename_component(CURRENT_FILE_PATH "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)
#message("PhoenixDebug 111 Current file path: ${CURRENT_FILE_PATH}")

set(ROOT_PATH "${CURRENT_FILE_PATH}/..")

# local cache path
set(PROJECT_CACHE_PATH ${ROOT_PATH}/.cache)
if (NOT EXISTS ${PROJECT_CACHE_PATH})
    message("create build path:${PROJECT_CACHE_PATH}")
    execute_process(COMMAND mkdir -p ${PROJECT_CACHE_PATH})
endif ()

# local not set ${VCPKG_ROOT} or no vcpkg
if (NOT DEFINED ENV{VCPKG_ROOT})
    if (NOT EXISTS ${PROJECT_CACHE_PATH}/vcpkg)
        message("VCPKG downloading")
        execute_process(COMMAND bash ${ROOT_PATH}/scripts/proxy.sh
                COMMAND git clone https://github.com/microsoft/vcpkg
                WORKING_DIRECTORY ${PROJECT_CACHE_PATH}
                COMMAND_ECHO STDOUT)
    elseif (VCPKG_UPDATE)
        message("VCPKG updating")
        execute_process(COMMAND bash ${ROOT_PATH}scripts/proxy.sh
                COMMAND git pull .
                WORKING_DIRECTORY ${PROJECT_CACHE_PATH}
                COMMAND_ECHO STDOUT)
    endif ()

    if (VCPKG_UPDATE OR (NOT EXISTS ${PROJECT_CACHE_PATH}/vcpkg/vcpkg))
        message("VCPKG bootstrap")
        if (WIN32)
            execute_process(COMMAND bootstrap-vcpkg.bat
                    WORKING_DIRECTORY ${PROJECT_CACHE_PATH}/vcpkg)
        else ()
            execute_process(COMMAND bash bootstrap-vcpkg.sh
                    WORKING_DIRECTORY ${PROJECT_CACHE_PATH}/vcpkg)
        endif ()
    endif ()

    set(VCPKG_ROOT ${PROJECT_CACHE_PATH}/vcpkg)
else ()
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
endif ()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Android")
    message("This is Android platform")
    set(VCPKG_TARGET_ANDROID ON)
    if (DEFINED ANDROID_NDK)
        set(ENV{ANDROID_NDK_HOME} ${ANDROID_NDK})
    elseif (DEFINED CMAKE_ANDROID_NDK)
        set(ENV{ANDROID_NDK_HOME} ${CMAKE_ANDROID_NDK})
    else ()
        message(FATAL_ERROR "
                Please set an environment variable ANDROID_NDK_HOME
                For example:
                export ANDROID_NDK_HOME=/home/your-account/Android/Sdk/ndk-bundle
                Or:
                export ANDROID_NDK_HOME=/home/your-account/Android/android-ndk-r21b
                ")
    endif ()

    if (ANDROID_ABI MATCHES "arm64-v8a")
        set(VCPKG_TARGET_TRIPLET "arm64-android" CACHE STRING "" FORCE)
    elseif (ANDROID_ABI MATCHES "armeabi-v7a")
        set(VCPKG_TARGET_TRIPLET "arm-android" CACHE STRING "" FORCE)
    elseif (ANDROID_ABI MATCHES "x86_64")
        set(VCPKG_TARGET_TRIPLET "x64-android" CACHE STRING "" FORCE)
    elseif (ANDROID_ABI MATCHES "x86")
        set(VCPKG_TARGET_TRIPLET "x86-android" CACHE STRING "" FORCE)
    else ()
        message(FATAL_ERROR "
                Please specify ANDROID_ABI
                For example
                cmake ... -DANDROID_ABI=armeabi-v7a

                Possible ABIs are: arm64-v8a, armeabi-v7a, x64-android, x86-android
                ")
    endif ()

    set(VCPKG_CHAINLOAD_TOOLCHAIN_FILE $ENV{ANDROID_NDK_HOME}/build/cmake/android.toolchain.cmake)
endif ()

#    "--binarysource=default,readwrite"
set(ENV{VCPKG_BINARY_SOURCES} "clear;files,${VCPKG_ROOT}/archives,readwrite;")
set(VCPKG_INSTALL_OPTIONS "--allow-unsupported")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

message("CMAKE_TOOLCHAIN_FILE was set to ${CMAKE_TOOLCHAIN_FILE}")
message("VCPKG_CHAINLOAD_TOOLCHAIN_FILE was set to ${VCPKG_CHAINLOAD_TOOLCHAIN_FILE}")
