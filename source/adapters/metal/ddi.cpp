//===--------- ddi.cpp - Metal Adapter ------------------------------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ur_ddi.h"

UR_DLLEXPORT ur_result_t UR_APICALL urGetGlobalProcAddrTable(
    ur_api_version_t version, ur_global_dditable_t *pDdiTable) {
  if (UR_API_VERSION_CURRENT < version) {
    return UR_RESULT_ERROR_UNSUPPORTED_VERSION;
  }
  pDdiTable->pfnAdapterGet = urAdapterGet;
  pDdiTable->pfnAdapterRelease = urAdapterRelease;
  pDdiTable->pfnAdapterRetain = urAdapterRetain;
  pDdiTable->pfnAdapterGetLastError = urAdapterGetLastError;
  pDdiTable->pfnAdapterGetInfo = urAdapterGetInfo;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetPlatformProcAddrTable(
    ur_api_version_t version, ur_platform_dditable_t *pDdiTable) {
  if (UR_API_VERSION_CURRENT < version) {
    return UR_RESULT_ERROR_UNSUPPORTED_VERSION;
  }
  pDdiTable->pfnGet = urPlatformGet;
  pDdiTable->pfnGetInfo = urPlatformGetInfo;
  pDdiTable->pfnGetNativeHandle = urPlatformGetNativeHandle;
  pDdiTable->pfnCreateWithNativeHandle = urPlatformCreateWithNativeHandle;
  pDdiTable->pfnGetApiVersion = urPlatformGetApiVersion;
  pDdiTable->pfnGetBackendOption = urPlatformGetBackendOption;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetDeviceProcAddrTable(
    ur_api_version_t version, ur_device_dditable_t *pDdiTable) {
  if (UR_API_VERSION_CURRENT < version) {
    return UR_RESULT_ERROR_UNSUPPORTED_VERSION;
  }
  pDdiTable->pfnGet = urDeviceGet;
  pDdiTable->pfnGetInfo = urDeviceGetInfo;
  pDdiTable->pfnRetain = urDeviceRetain;
  pDdiTable->pfnRelease = urDeviceRelease;
  pDdiTable->pfnPartition = urDevicePartition;
  pDdiTable->pfnSelectBinary = urDeviceSelectBinary;
  pDdiTable->pfnGetNativeHandle = urDeviceGetNativeHandle;
  pDdiTable->pfnCreateWithNativeHandle = urDeviceCreateWithNativeHandle;
  pDdiTable->pfnGetGlobalTimestamps = urDeviceGetGlobalTimestamps;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetContextProcAddrTable(
    ur_api_version_t version, ur_context_dditable_t *pDdiTable) {
  if (UR_API_VERSION_CURRENT < version) {
    return UR_RESULT_ERROR_UNSUPPORTED_VERSION;
  }
  pDdiTable->pfnCreate = urContextCreate;
  pDdiTable->pfnRetain = urContextRetain;
  pDdiTable->pfnRelease = urContextRelease;
  pDdiTable->pfnGetInfo = urContextGetInfo;
  pDdiTable->pfnGetNativeHandle = urContextGetNativeHandle;
  pDdiTable->pfnCreateWithNativeHandle = urContextCreateWithNativeHandle;
  pDdiTable->pfnSetExtendedDeleter = urContextSetExtendedDeleter;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL
urGetMemProcAddrTable(ur_api_version_t version, ur_mem_dditable_t *pDdiTable) {
  if (UR_API_VERSION_CURRENT < version) {
    return UR_RESULT_ERROR_UNSUPPORTED_VERSION;
  }
  pDdiTable->pfnImageCreate = urMemImageCreate;
  pDdiTable->pfnBufferCreate = urMemBufferCreate;
  pDdiTable->pfnRetain = urMemRetain;
  pDdiTable->pfnRelease = urMemRelease;
  pDdiTable->pfnBufferPartition = urMemBufferPartition;
  pDdiTable->pfnGetNativeHandle = urMemGetNativeHandle;
  pDdiTable->pfnBufferCreateWithNativeHandle =
      urMemBufferCreateWithNativeHandle;
  pDdiTable->pfnImageCreateWithNativeHandle = urMemImageCreateWithNativeHandle;
  pDdiTable->pfnGetInfo = urMemGetInfo;
  pDdiTable->pfnImageGetInfo = urMemImageGetInfo;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetSamplerProcAddrTable(
    ur_api_version_t version, ur_sampler_dditable_t *pDdiTable) {
  if (UR_API_VERSION_CURRENT < version) {
    return UR_RESULT_ERROR_UNSUPPORTED_VERSION;
  }
  pDdiTable->pfnCreate = nullptr;
  pDdiTable->pfnRetain = nullptr;
  pDdiTable->pfnRelease = nullptr;
  pDdiTable->pfnGetInfo = nullptr;
  pDdiTable->pfnGetNativeHandle = nullptr;
  pDdiTable->pfnCreateWithNativeHandle = nullptr;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL
urGetUSMProcAddrTable(ur_api_version_t version, ur_usm_dditable_t *pDdiTable) {
  if (UR_API_VERSION_CURRENT < version) {
    return UR_RESULT_ERROR_UNSUPPORTED_VERSION;
  }
  pDdiTable->pfnHostAlloc = nullptr;
  pDdiTable->pfnDeviceAlloc = nullptr;
  pDdiTable->pfnSharedAlloc = nullptr;
  pDdiTable->pfnFree = nullptr;
  pDdiTable->pfnGetMemAllocInfo = nullptr;
  pDdiTable->pfnPoolCreate = nullptr;
  pDdiTable->pfnPoolRelease = nullptr;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetProgramProcAddrTable(
    ur_api_version_t version, ur_program_dditable_t *pDdiTable) {
  if (UR_API_VERSION_CURRENT < version) {
    return UR_RESULT_ERROR_UNSUPPORTED_VERSION;
  }
  pDdiTable->pfnCreateWithIL = nullptr;
  pDdiTable->pfnCreateWithBinary = nullptr;
  pDdiTable->pfnBuild = nullptr;
  pDdiTable->pfnCompile = nullptr;
  pDdiTable->pfnLink = nullptr;
  pDdiTable->pfnRetain = nullptr;
  pDdiTable->pfnRelease = nullptr;
  pDdiTable->pfnGetFunctionPointer = nullptr;
  pDdiTable->pfnGetInfo = nullptr;
  pDdiTable->pfnGetBuildInfo = nullptr;
  pDdiTable->pfnSetSpecializationConstants = nullptr;
  pDdiTable->pfnGetNativeHandle = nullptr;
  pDdiTable->pfnCreateWithNativeHandle = nullptr;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetQueueProcAddrTable(
    ur_api_version_t version, ur_queue_dditable_t *pDdiTable) {
  if (UR_API_VERSION_CURRENT < version) {
    return UR_RESULT_ERROR_UNSUPPORTED_VERSION;
  }
  pDdiTable->pfnGetInfo = nullptr;
  pDdiTable->pfnCreate = nullptr;
  pDdiTable->pfnRetain = nullptr;
  pDdiTable->pfnRelease = nullptr;
  pDdiTable->pfnGetNativeHandle = nullptr;
  pDdiTable->pfnCreateWithNativeHandle = nullptr;
  pDdiTable->pfnFinish = nullptr;
  pDdiTable->pfnFlush = nullptr;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetKernelProcAddrTable(
    ur_api_version_t version, ur_kernel_dditable_t *pDdiTable) {
  if (UR_API_VERSION_CURRENT < version) {
    return UR_RESULT_ERROR_UNSUPPORTED_VERSION;
  }
  pDdiTable->pfnCreate = nullptr;
  pDdiTable->pfnGetInfo = nullptr;
  pDdiTable->pfnGetGroupInfo = nullptr;
  pDdiTable->pfnGetSubGroupInfo = nullptr;
  pDdiTable->pfnRetain = nullptr;
  pDdiTable->pfnRelease = nullptr;
  pDdiTable->pfnGetNativeHandle = nullptr;
  pDdiTable->pfnCreateWithNativeHandle = nullptr;
  pDdiTable->pfnSetArgValue = nullptr;
  pDdiTable->pfnSetArgLocal = nullptr;
  pDdiTable->pfnSetArgPointer = nullptr;
  pDdiTable->pfnSetExecInfo = nullptr;
  pDdiTable->pfnSetArgSampler = nullptr;
  pDdiTable->pfnSetArgMemObj = nullptr;
  pDdiTable->pfnSetSpecializationConstants = nullptr;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetEventProcAddrTable(
    ur_api_version_t version, ur_event_dditable_t *pDdiTable) {
  if (UR_API_VERSION_CURRENT < version) {
    return UR_RESULT_ERROR_UNSUPPORTED_VERSION;
  }
  pDdiTable->pfnGetInfo = nullptr;
  pDdiTable->pfnGetProfilingInfo = nullptr;
  pDdiTable->pfnWait = nullptr;
  pDdiTable->pfnRetain = nullptr;
  pDdiTable->pfnRelease = nullptr;
  pDdiTable->pfnGetNativeHandle = nullptr;
  pDdiTable->pfnCreateWithNativeHandle = nullptr;
  pDdiTable->pfnSetCallback = nullptr;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetEnqueueProcAddrTable(
    ur_api_version_t version, ur_enqueue_dditable_t *pDdiTable) {
  if (UR_API_VERSION_CURRENT < version) {
    return UR_RESULT_ERROR_UNSUPPORTED_VERSION;
  }
  pDdiTable->pfnKernelLaunch = nullptr;
  pDdiTable->pfnEventsWait = nullptr;
  pDdiTable->pfnEventsWaitWithBarrier = nullptr;
  pDdiTable->pfnMemBufferRead = nullptr;
  pDdiTable->pfnMemBufferWrite = nullptr;
  pDdiTable->pfnMemBufferReadRect = nullptr;
  pDdiTable->pfnMemBufferWriteRect = nullptr;
  pDdiTable->pfnMemBufferCopy = nullptr;
  pDdiTable->pfnMemBufferCopyRect = nullptr;
  pDdiTable->pfnMemBufferFill = nullptr;
  pDdiTable->pfnMemImageRead = nullptr;
  pDdiTable->pfnMemImageWrite = nullptr;
  pDdiTable->pfnMemImageCopy = nullptr;
  pDdiTable->pfnMemBufferMap = nullptr;
  pDdiTable->pfnMemUnmap = nullptr;
  pDdiTable->pfnUSMFill = nullptr;
  pDdiTable->pfnUSMMemcpy = nullptr;
  pDdiTable->pfnUSMPrefetch = nullptr;
  pDdiTable->pfnUSMAdvise = nullptr;
  pDdiTable->pfnUSMFill2D = nullptr;
  pDdiTable->pfnUSMMemcpy2D = nullptr;
  pDdiTable->pfnDeviceGlobalVariableWrite = nullptr;
  pDdiTable->pfnDeviceGlobalVariableRead = nullptr;
  return UR_RESULT_SUCCESS;
}
