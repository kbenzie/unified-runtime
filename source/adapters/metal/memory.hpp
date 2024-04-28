//===--------- memory.hpp - Metal Adapter ---------------------------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef UR_ADAPTER_METAL_MEMORY_HPP_INCLUDED
#define UR_ADAPTER_METAL_MEMORY_HPP_INCLUDED

#include "common.hpp"
#include "ur_api.h"
#include <Metal/MTLResource.hpp>
#include <Metal/Metal.hpp>

struct ur_mem_handle_t_ : ur::refcount {
  ur_context_handle_t context = nullptr;
  const ur_mem_flags_t flags = 0;
  const enum mem_type {
    BUFFER,
    PARTITION,
    IMAGE,
  } type;

  ur_mem_handle_t_(ur_context_handle_t hContext, ur_mem_flags_t flags,
                   mem_type type)
      : context(hContext), flags(flags), type(type) {}
};

namespace ur::metal {
struct buffer : ur_mem_handle_t_ {
  buffer(ur_context_handle_t hContext, ur_mem_flags_t flags, size_t size,
         const ur_buffer_properties_t *pProperties, ur_mem_handle_t *phBuffer);

  const size_t size = 0;
  MTL::Buffer *mBuffer = nullptr;
};

struct buffer_partition : ur_mem_handle_t_ {
  buffer_partition(ur::metal::buffer *parent, ur_mem_flags_t flags,
                   const ur_buffer_region_t *pRegion);

  ~buffer_partition() { parent->release(); }

  const size_t size = 0;
  ur::metal::buffer *parent = nullptr;
  MTL::Buffer *mBuffer = nullptr;
};
} // namespace ur::metal

#endif // UR_ADAPTER_METAL_MEMORY_HPP_INCLUDED
