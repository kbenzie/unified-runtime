//===--------- context.hpp - Metal Adapter --------------------------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef UR_ADAPTER_METLAL_CONTEXT_HPP_INCLUDED
#define UR_ADAPTER_METLAL_CONTEXT_HPP_INCLUDED

#include "common.hpp"
#include "ur_api.h"

struct ur_context_handle_t_ : ur::refcount {
  // TODO: Support multi-device configs.
  ur_device_handle_t device = nullptr;
  ur_context_flags_t flags = 0;
  ur_context_extended_deleter_t deleterCallback = nullptr;
  void *deleterCallbackUserData = nullptr;

  ur_context_handle_t_(uint32_t deviceCount,
                       const ur_device_handle_t *phDevices,
                       const ur_context_properties_t *pProperties);

  ~ur_context_handle_t_() {
    if (deleterCallback) {
      deleterCallback(deleterCallbackUserData);
    }
  }
};

#endif // UR_ADAPTER_METLAL_CONTEXT_HPP_INCLUDED
