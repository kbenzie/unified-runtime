//===--------- platform.hpp - Metal Adapter -------------------------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef UR_ADAPTER_METAL_PLATFORM_HPP_INCLUDED
#define UR_ADAPTER_METAL_PLATFORM_HPP_INCLUDED

#include "ur_api.h"

#include <string>

// UR_MAKE_VERSION(_major, _minor) ((_major << 16) | (_minor & 0x0000ffff))
namespace ur {
inline std::string getVersionStr(ur_api_version_t version) {
  return std::to_string((version & 0xffff0000) >> 16) + "." +
         std::to_string(version & 0x0000ffff);
}
} // namespace ur

struct ur_platform_handle_t_ {
  // TODO: Support multi-device configs.
  ur_device_handle_t device = nullptr;

  // ur_platform_info_t
  std::string name = "Apple macOS";
  std::string vendorName = "Apple";
  std::string version = ur::getVersionStr(UR_API_VERSION_CURRENT);
  std::string extensions = "";
  std::string profile = "FULL PROFILE";
};

#endif // UR_ADAPTER_METAL_PLATFORM_HPP_INCLUDED
