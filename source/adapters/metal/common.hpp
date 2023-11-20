//===--------- common.hpp - Metal Adapter ---------------------------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef UR_ADPATER_METAL_COMMON_HPP_INCLUDED
#define UR_ADPATER_METAL_COMMON_HPP_INCLUDED

#include <atomic>

namespace ur {
struct refcount {
  uint32_t retain() {
    return ++refCount;
  }
  uint32_t release() {
    return --refCount;
  }
  uint32_t getRefCount() const {
    return refCount;
  }

private:
  std::atomic_uint32_t refCount = 1;
};
} // namespace ur

#endif  // UR_ADPATER_METAL_COMMON_HPP_INCLUDED
