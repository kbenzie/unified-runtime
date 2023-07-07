# Copyright (C) 2022-2023 Intel Corporation
# Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM Exceptions.
# See LICENSE.TXT
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

if(NOT CMAKE_SYSTEM_NAME STREQUAL Darwin)
    return()
endif()

if(CMAKE_SYSTEM_VERSION VERSION_GREATER_EQUAL 21.0.0 AND
        CMAKE_SYSTEM_VERSION VERSION_LESS 22.0.0)
    set(metalCppUrl metal-cpp_macOS12_iOS15)
    set(macOSRelease Monterey)
elseif(CMAKE_SYSTEM_VERSION VERSION_GREATER_EQUAL 22.0.0 AND
        CMAKE_SYSTEM_VERSION VERSION_LESS 23.0.0)
    set(metalCppUrl metal-cpp_macOS13_iOS16)
    set(macOSRelease Ventura)
else()
    message(FATAL_ERROR
        "Darwin v${CMAKE_SYSTEM_VERSION} not supported.")
endif()

cmake_policy(SET CMP0135 NEW)
FetchContent_Declare(metal-cpp
    URL https://developer.apple.com/metal/cpp/files/${metalCppUrl}.zip
)
FetchContent_MakeAvailable(metal-cpp)

add_library(metal-cpp STATIC metal.cpp)
target_include_directories(metal-cpp SYSTEM PUBLIC ${metal-cpp_SOURCE_DIR})
target_link_libraries(metal-cpp INTERFACE
    "-framework AppKit"
    "-framework Foundation"
    "-framework Metal"
    "-framework MetalKit"
    "-framework QuartzCore"
)

add_library(ur_adapter_metal SHARED
    adapter.hpp adapter.cpp
    ddi.cpp
    device.hpp device.cpp
    platform.hpp platform.cpp
)
target_compile_definitions(ur_adapter_metal PRIVATE
    UR_ADAPTER_METAL_MACOS_RELEASE="${macOSRelease}"
)
target_link_libraries(ur_adapter_metal PRIVATE
    unified-runtime::headers
    unified-runtime::common
    metal-cpp
)
set_target_properties(ur_adapter_metal PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
