//===--------- platform.cpp - Metal Adapter -------------------------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "platform.hpp"
#include "adapter.hpp"
#include "ur/ur.hpp"

UR_APIEXPORT ur_result_t UR_APICALL urPlatformGet(
    ur_adapter_handle_t *phAdapters, uint32_t numAdapters, uint32_t numEntries,
    ur_platform_handle_t *phPlatforms, uint32_t *pNumPlatforms) {
  if (numAdapters != 1) {
    return UR_RESULT_ERROR_INVALID_SIZE;
  }
  if (phPlatforms) {
    if (numEntries != 1) {
      return UR_RESULT_ERROR_INVALID_SIZE;
    }
    *phPlatforms = phAdapters[0]->platform;
  }
  if (pNumPlatforms) {
    *pNumPlatforms = 1;
  }
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL
urPlatformGetInfo(ur_platform_handle_t hPlatform, ur_platform_info_t propName,
                  size_t propSize, void *pPropValue, size_t *pPropSizeRet) {
  UrReturnHelper returnValue(propSize, pPropValue, pPropSizeRet);
  switch (propName) {
  case UR_PLATFORM_INFO_NAME:
    return returnValue(hPlatform->name.c_str());
  case UR_PLATFORM_INFO_VENDOR_NAME:
    return returnValue(hPlatform->vendorName.c_str());
  case UR_PLATFORM_INFO_VERSION:
    return returnValue(hPlatform->version.c_str());
  case UR_PLATFORM_INFO_EXTENSIONS:
    return returnValue(hPlatform->extensions.c_str());
  case UR_PLATFORM_INFO_PROFILE:
    return returnValue(hPlatform->profile.c_str());
  case UR_PLATFORM_INFO_BACKEND:
    return returnValue(UR_PLATFORM_BACKEND_UNKNOWN);
  default:
    return UR_RESULT_ERROR_INVALID_ENUMERATION;
  }
}

UR_APIEXPORT ur_result_t UR_APICALL urPlatformGetApiVersion(
    ur_platform_handle_t hPlatform, ur_api_version_t *pVersion) {
  *pVersion = UR_API_VERSION_CURRENT;
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urPlatformGetNativeHandle(
    ur_platform_handle_t hPlatform, ur_native_handle_t *phNativePlatform) {
  return UR_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

UR_APIEXPORT ur_result_t UR_APICALL urPlatformCreateWithNativeHandle(
    ur_native_handle_t hNativePlatform, ur_adapter_handle_t hAdatper,
    const ur_platform_native_properties_t *pProperties,
    ur_platform_handle_t *phPlatform) {
  return UR_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

UR_APIEXPORT ur_result_t UR_APICALL urPlatformGetBackendOption(
    ur_platform_handle_t hPlatform, const char *pFrontendOption,
    const char **ppPlatformOption) {
  std::string_view frontendOption{pFrontendOption};
  if (frontendOption == "-O0") {
    *ppPlatformOption = "";
  } else if (frontendOption == "-O1") {
    *ppPlatformOption = "";
  } else if (frontendOption == "-O2") {
    *ppPlatformOption = "";
  } else if (frontendOption == "-O3") {
    *ppPlatformOption = "";
  } else {
    return UR_RESULT_ERROR_INVALID_VALUE;
  }
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urPlatformGetLastError(
    ur_platform_handle_t hPlatform, const char **ppMessage, int32_t *pError) {
  *ppMessage = "";
  *pError = -1;
  return UR_RESULT_SUCCESS;
}
