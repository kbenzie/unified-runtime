//===--------- adapter.hpp - Metal Adapter --------------------------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef UR_ADAPTER_METAL_HPP_INCLUDED
#define UR_ADAPTER_METAL_HPP_INCLUDED

#include "common.hpp"
#include "ur_api.h"
#include <string>

struct ur_adapter_handle_t_ : ur::refcount {
  struct last_error_t {
    std::string message;
    int32_t errorCode;
    ur_result_t result;
  };

  ~ur_adapter_handle_t_();

  void setLastError(std::string_view message, int32_t errorCode,
                    ur_result_t result);

  last_error_t getLastError();

  ur_platform_handle_t platform = nullptr;
};

extern ur_adapter_handle_t_ adapter;

#endif // UR_ADAPTER_METAL_HPP_INCLUDED
