# Copyright (C) 2022-2023 Intel Corporation
# Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM Exceptions.
# See LICENSE.TXT
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

if(NOT CMAKE_SYSTEM_NAME STREQUAL Darwin)
  return()
endif()

execute_process(
  COMMAND sw_vers -productVersion
  OUTPUT_VARIABLE macOSVersion
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "Apple macOS Version: ${macOSVersion}")

if(macOSVersion VERSION_GREATER_EQUAL 12.0 AND macOSVersion VERSION_LESS 13.0)
  set(metalCppUrl metal-cpp_macOS12_iOS15)
elseif(macOSVersion VERSION_GREATER_EQUAL 13.0 AND macOSVersion VERSION_LESS 13.3)
  set(metalCppUrl metal-cpp_macOS13_iOS16)
elseif(macOSVersion VERSION_GREATER_EQUAL 13.3 AND macOSVersion VERSION_LESS 14.0)
  set(metalCppUrl metal-cpp_macOS13.3_iOS16.4)
elseif(macOSVersion VERSION_GREATER_EQUAL 14.0 AND macOSVersion VERSION_LESS 14.2)
  set(metalCppUrl metal-cpp_macOS14_iOS17-beta)
elseif(macOSVersion VERSION_GREATER_EQUAL 14.2 AND macOSVersion VERSION_LESS 15.0)
  set(metalCppUrl metal-cpp_macOS14.2_iOS17.2)
else()
  message(FATAL_ERROR "Apple macOS Version ${CMAKE_SYSTEM_VERSION} not supported.")
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
  context.hpp context.cpp
  ddi.cpp
  device.hpp device.cpp
  platform.hpp platform.cpp
  ${PROJECT_SOURCE_DIR}/source/ur/ur.hpp ${PROJECT_SOURCE_DIR}/source/ur/ur.cpp
)
target_compile_definitions(ur_adapter_metal PRIVATE
  UR_ADAPTER_METAL_MACOS_VERSION="${macOSVersion}"
)
target_compile_options(ur_adapter_metal PRIVATE
  -fcolor-diagnostics
)
target_include_directories(ur_adapter_metal PRIVATE
  ${PROJECT_SOURCE_DIR}/source
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
