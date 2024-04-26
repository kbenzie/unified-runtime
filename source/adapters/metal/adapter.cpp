//===--------- adapter.cpp - Metal Adapter --------------------------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "adapter.hpp"
#include "device.hpp"
#include "platform.hpp"
#include "ur_util.hpp"

#include <mutex>

ur_adapter_handle_t_ adapter{};

thread_local ur_adapter_handle_t_::last_error_t lastError{};

ur_adapter_handle_t_::~ur_adapter_handle_t_() {
  if (platform) {
    platform->device->mDevice->release();
    platform->device = nullptr;
    platform = nullptr;
  }
}

void setLastError(std::string_view message, int32_t errorCode,
                  ur_result_t result) {
  lastError.message = message;
  lastError.errorCode = errorCode;
  lastError.result = result;
}

ur_adapter_handle_t_::last_error_t ur_adapter_handle_t_::getLastError() {
  return lastError;
}

UR_APIEXPORT ur_result_t UR_APICALL
urAdapterGet(uint32_t NumEntries, ur_adapter_handle_t *phAdapters,
             uint32_t *pNumAdapters) {
  static std::once_flag onceFlag;
  try {
    std::call_once(onceFlag, []() {
      if (!adapter.platform) {
        static ur_platform_handle_t_ platform;
        adapter.platform = &platform;
        // TODO: Support multi-device configs.
        static ur_device_handle_t_ device{};
        adapter.platform->device = &device;
        adapter.platform->device->platform = adapter.platform;
        adapter.platform->device->mDevice = MTL::CreateSystemDefaultDevice();
      }
    });
  } catch (const ur_result_t &error) {
    return error;
  }
  if (NumEntries > 0 && phAdapters) {
    *phAdapters = &adapter;
  }
  if (pNumAdapters) {
    *pNumAdapters = 1;
  }
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL
urAdapterRetain(ur_adapter_handle_t hAdapter) {
  hAdapter->retain();
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL
urAdapterRelease(ur_adapter_handle_t hAdapter) {
  if (hAdapter->getRefCount()) {
    hAdapter->release();
  }
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL
urAdapterGetInfo(ur_adapter_handle_t hAdapter, ur_adapter_info_t propName,
                 size_t propSize, void *pPropValue, size_t *pPropSizeRet) {
  switch (propName) {
  case UR_ADAPTER_INFO_BACKEND:
    if (pPropValue) {
      if (propSize < sizeof(ur_adapter_backend_t)) {
        return UR_RESULT_ERROR_INVALID_SIZE;
      }
      *static_cast<ur_adapter_backend_t *>(pPropValue) =
          UR_ADAPTER_BACKEND_UNKNOWN;
    }
    if (pPropSizeRet) {
      *pPropSizeRet = sizeof(ur_adapter_backend_t);
    }
    break;
  case UR_ADAPTER_INFO_REFERENCE_COUNT:
    if (pPropValue) {
      if (propSize < sizeof(uint32_t)) {
        return UR_RESULT_ERROR_INVALID_SIZE;
      }
      *static_cast<uint32_t *>(pPropValue) = hAdapter->getRefCount();
    }
    if (pPropSizeRet) {
      *pPropSizeRet = sizeof(uint32_t);
    }
    break;
  case UR_ADAPTER_INFO_FORCE_UINT32:
    ur::unreachable();
  }
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urAdapterGetLastError(
    ur_adapter_handle_t hAdapter, const char **ppMessage, int32_t *pError) {
  auto lastError = hAdapter->getLastError();
  if (ppMessage) {
    *ppMessage = lastError.message.c_str();
  }
  if (pError) {
    *pError = lastError.errorCode;
  }
  return lastError.result;
}
