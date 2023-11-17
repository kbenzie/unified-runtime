//===--------- device.hpp - Metal Adapter ---------------------------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef UR_ADADTER_METAL_DEVICE_HPP_INCLUDED
#define UR_ADADTER_METAL_DEVICE_HPP_INCLUDED

#include "common.hpp"
#include "ur_api.h"
#include <Metal/Metal.hpp>

struct ur_device_handle_t_ : ur::refcount {
  ur_platform_handle_t platform = nullptr;
  MTL::Device *mDevice = nullptr;
};

#endif // UR_ADADTER_METAL_DEVICE_HPP_INCLUDED
