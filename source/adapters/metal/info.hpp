//===--------- info.hpp - Metal Adapter -----------------------------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef UR_ADAPTER_METAL_INFO_HPP_INCLUDED
#define UR_ADAPTER_METAL_INFO_HPP_INCLUDED

#include "ur_api.h"
#include <cstring>
#include <string_view>
#include <type_traits>

namespace ur {
template <class T>
using is_string =
    std::disjunction<std::is_same<T, char *>, std::is_same<T, std::string>,
                     std::is_same<T, std::string_view>>;

template <class T> constexpr const bool is_string_v = is_string<T>::value;

template <class T>
inline std::enable_if_t<!ur::is_string_v<T>, ur_result_t>
setInfo(const T &value, size_t size, void *pValue, size_t *pSize) {
  if (pValue) {
    if (size < sizeof(T)) {
      return UR_RESULT_ERROR_INVALID_SIZE;
    }
    *static_cast<T *>(pValue) = value;
  }
  if (pSize) {
    *pSize = sizeof(T);
  }
  return UR_RESULT_SUCCESS;
}

inline ur_result_t setInfo(std::string_view value, size_t size, void *pValue,
                           size_t *pSize) {
  if (pValue) {
    if (size < value.size() + 1) {
      return UR_RESULT_ERROR_INVALID_SIZE;
    }
    std::strncpy(static_cast<char *>(pValue), value.data(),
                 std::min(size, value.size()));
  }
  if (pSize) {
    *pSize = value.size() + 1;
  }
  return UR_RESULT_SUCCESS;
}
} // namespace ur

#endif // UR_ADAPTER_METAL_INFO_HPP_INCLUDED
