//===--------- context.hpp - Metal Adapter --------------------------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "context.hpp"
#include "ur/ur.hpp"
#include <memory>

ur_context_handle_t_::ur_context_handle_t_(
    uint32_t deviceCount, const ur_device_handle_t *phDevices,
    const ur_context_properties_t *pProperties) {
  if (deviceCount > 1) {
    throw UR_RESULT_ERROR_DEVICE_LOST;
  }
  device = phDevices[0];
  if (pProperties) {
    flags = pProperties->flags;
  }
}

UR_APIEXPORT ur_result_t UR_APICALL
urContextCreate(uint32_t deviceCount, const ur_device_handle_t *phDevices,
                const ur_context_properties_t *pProperties,
                ur_context_handle_t *phContext) {
  if (deviceCount > 1) {
    return UR_RESULT_ERROR_UNSUPPORTED_FEATURE;
  }

  std::unique_ptr<ur_context_handle_t_> context;
  try {
    context = std::make_unique<ur_context_handle_t_>(deviceCount, phDevices,
                                                     pProperties);
  } catch (const std::bad_alloc &) {
    return UR_RESULT_ERROR_OUT_OF_HOST_MEMORY;
  } catch (const ur_result_t &error) {
    return error;
  }

  *phContext = context.release();

  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL
urContextRetain(ur_context_handle_t hContext) {
  hContext->retain();
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL
urContextRelease(ur_context_handle_t hContext) {
  if (hContext->release() == 0) {
    delete hContext;
  }
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL
urContextGetInfo(ur_context_handle_t hContext, ur_context_info_t propName,
                 size_t propSize, void *pPropValue, size_t *pPropSizeRet) {
  UrReturnHelper returnValue{propSize, pPropValue, pPropSizeRet};

  switch (propName) {
  case UR_CONTEXT_INFO_NUM_DEVICES:
    return returnValue(1);

  case UR_CONTEXT_INFO_DEVICES:
    return returnValue(&hContext->device);

  case UR_CONTEXT_INFO_REFERENCE_COUNT:
    return returnValue(hContext->getRefCount());

  case UR_CONTEXT_INFO_USM_MEMCPY2D_SUPPORT:
    return returnValue(false);

  case UR_CONTEXT_INFO_USM_FILL2D_SUPPORT:
    return returnValue(false);

  case UR_CONTEXT_INFO_ATOMIC_MEMORY_ORDER_CAPABILITIES:
    return returnValue(0);

  case UR_CONTEXT_INFO_ATOMIC_MEMORY_SCOPE_CAPABILITIES:
    return returnValue(0);

  case UR_CONTEXT_INFO_ATOMIC_FENCE_ORDER_CAPABILITIES:
    return returnValue(0);

  case UR_CONTEXT_INFO_ATOMIC_FENCE_SCOPE_CAPABILITIES:
    return returnValue(0);

  case UR_CONTEXT_INFO_FORCE_UINT32:
    ur::unreachable();
  }

  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urContextGetNativeHandle(
    ur_context_handle_t hContext, ur_native_handle_t *phNativeContext) {
  return UR_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

UR_APIEXPORT ur_result_t UR_APICALL urContextCreateWithNativeHandle(
    ur_native_handle_t hNativeContext, uint32_t numDevices,
    const ur_device_handle_t *phDevices,
    const ur_context_native_properties_t *pProperties,
    ur_context_handle_t *phContext) {
  return UR_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

UR_APIEXPORT ur_result_t UR_APICALL urContextSetExtendedDeleter(
    ur_context_handle_t hContext, ur_context_extended_deleter_t pfnDeleter,
    void *pUserData) {
  hContext->deleterCallback = pfnDeleter;
  hContext->deleterCallbackUserData = pUserData;
  return UR_RESULT_SUCCESS;
}
