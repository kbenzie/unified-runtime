//===--------- device.cpp - Metal Adapter ---------------------------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "device.hpp"
#include "adapter.hpp"
#include "platform.hpp"
#include "ur/ur.hpp"

#include <cstdio>

UR_APIEXPORT ur_result_t UR_APICALL urDeviceGet(ur_platform_handle_t hPlatform,
                                                ur_device_type_t deviceType,
                                                uint32_t numEntries,
                                                ur_device_handle_t *phDevices,
                                                uint32_t *pNumDevices) {
  if (phDevices) {
    if (numEntries != 1) {
      return UR_RESULT_ERROR_INVALID_SIZE;
    }
    *phDevices = hPlatform->device;
  }
  if (pNumDevices) {
    *pNumDevices = 1;
  }
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urDeviceGetInfo(ur_device_handle_t hDevice,
                                                    ur_device_info_t propName,
                                                    size_t propSize,
                                                    void *pPropValue,
                                                    size_t *pPropSizeRet) {
  UrReturnHelper returnValue{propSize, pPropValue, pPropSizeRet};
  switch (propName) {
  case UR_DEVICE_INFO_TYPE:
    return returnValue(UR_DEVICE_TYPE_GPU);

  case UR_DEVICE_INFO_VENDOR_ID: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_DEVICE_ID: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_COMPUTE_UNITS: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_WORK_ITEM_DIMENSIONS: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_WORK_ITEM_SIZES: // size_t[]
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_WORK_GROUP_SIZE: // size_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_SINGLE_FP_CONFIG: // ur_device_fp_capability_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_HALF_FP_CONFIG: // ur_device_fp_capability_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_DOUBLE_FP_CONFIG: // ur_device_fp_capability_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_QUEUE_PROPERTIES: // ur_queue_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PREFERRED_VECTOR_WIDTH_CHAR: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PREFERRED_VECTOR_WIDTH_SHORT: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PREFERRED_VECTOR_WIDTH_INT: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PREFERRED_VECTOR_WIDTH_LONG: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PREFERRED_VECTOR_WIDTH_FLOAT: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PREFERRED_VECTOR_WIDTH_DOUBLE: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PREFERRED_VECTOR_WIDTH_HALF: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_NATIVE_VECTOR_WIDTH_CHAR: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_NATIVE_VECTOR_WIDTH_SHORT: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_NATIVE_VECTOR_WIDTH_INT: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_NATIVE_VECTOR_WIDTH_LONG: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_NATIVE_VECTOR_WIDTH_FLOAT: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_NATIVE_VECTOR_WIDTH_DOUBLE: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_NATIVE_VECTOR_WIDTH_HALF: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_CLOCK_FREQUENCY: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MEMORY_CLOCK_RATE: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_ADDRESS_BITS: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_MEM_ALLOC_SIZE: // uint64_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_IMAGE_SUPPORTED: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_READ_IMAGE_ARGS: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_WRITE_IMAGE_ARGS: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_READ_WRITE_IMAGE_ARGS: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_IMAGE2D_MAX_WIDTH: // size_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_IMAGE2D_MAX_HEIGHT: // size_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_IMAGE3D_MAX_WIDTH: // size_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_IMAGE3D_MAX_HEIGHT: // size_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_IMAGE3D_MAX_DEPTH: // size_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_IMAGE_MAX_BUFFER_SIZE: // size_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_IMAGE_MAX_ARRAY_SIZE: // size_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_SAMPLERS: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_PARAMETER_SIZE: // size_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MEM_BASE_ADDR_ALIGN: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_GLOBAL_MEM_CACHE_TYPE: // ur_device_mem_cache_type_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_GLOBAL_MEM_CACHELINE_SIZE: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_GLOBAL_MEM_CACHE_SIZE: // uint64_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_GLOBAL_MEM_SIZE: // uint64_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_GLOBAL_MEM_FREE: // uint64_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_CONSTANT_BUFFER_SIZE: // uint64_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_CONSTANT_ARGS: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_LOCAL_MEM_TYPE: // ur_device_local_mem_type_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_LOCAL_MEM_SIZE: // uint64_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_ERROR_CORRECTION_SUPPORT: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_HOST_UNIFIED_MEMORY: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PROFILING_TIMER_RESOLUTION: {
    // FIXME: This is almost certainly wrong, can't find anything in the Metal
    // docs describing what this might be though. Setting to 1 so testing can
    // use a value.
    size_t profilingTimeerResolution = 1;
    return returnValue(profilingTimeerResolution);
  }

  case UR_DEVICE_INFO_ENDIAN_LITTLE: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_AVAILABLE: // ur_bool_t
    return returnValue(true);

  case UR_DEVICE_INFO_COMPILER_AVAILABLE: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_LINKER_AVAILABLE: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_EXECUTION_CAPABILITIES: // ur_device_exec_capability_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_QUEUE_ON_DEVICE_PROPERTIES: // ur_queue_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_QUEUE_ON_HOST_PROPERTIES: // ur_queue_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_BUILT_IN_KERNELS: // char[]
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PLATFORM:
    return returnValue(hDevice->platform);

  case UR_DEVICE_INFO_REFERENCE_COUNT:
    return returnValue(hDevice->getRefCount());

  case UR_DEVICE_INFO_IL_VERSION: // char[]
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_NAME:
    return returnValue(hDevice->mDevice->name()->cString(
        NS::StringEncoding::ASCIIStringEncoding));

  case UR_DEVICE_INFO_VENDOR:
    return returnValue("Apple");

  case UR_DEVICE_INFO_DRIVER_VERSION: {
    std::string driverVersion = "Metal ";
    driverVersion += std::to_string(METALCPP_VERSION_MAJOR / 100);
    driverVersion += "." + std::to_string(METALCPP_VERSION_MINOR);
    driverVersion += "." + std::to_string(METALCPP_VERSION_PATCH);
    return returnValue(driverVersion.c_str());
  }

  case UR_DEVICE_INFO_PROFILE: // char[]
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_VERSION: {
    return returnValue("");
  }

  case UR_DEVICE_INFO_BACKEND_RUNTIME_VERSION: // char[]
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_EXTENSIONS: {
    return returnValue("");
  }

  case UR_DEVICE_INFO_PRINTF_BUFFER_SIZE: // size_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PREFERRED_INTEROP_USER_SYNC: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PARENT_DEVICE: // ur_device_handle_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_SUPPORTED_PARTITIONS: // ur_device_partition_t[]
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PARTITION_MAX_SUB_DEVICES: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PARTITION_AFFINITY_DOMAIN: // ur_device_affinity_domain_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PARTITION_TYPE: // ur_device_partition_property_t[]
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_NUM_SUB_GROUPS: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_SUB_GROUP_INDEPENDENT_FORWARD_PROGRESS: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_SUB_GROUP_SIZES_INTEL: // uint32_t[]
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_USM_HOST_SUPPORT: // ur_device_usm_access_capability_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_USM_DEVICE_SUPPORT: // ur_device_usm_access_capability_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_USM_SINGLE_SHARED_SUPPORT: // ur_device_usm_access_capability_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_USM_CROSS_SHARED_SUPPORT: // ur_device_usm_access_capability_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_USM_SYSTEM_SHARED_SUPPORT: // ur_device_usm_access_capability_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_UUID: // char[]
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_PCI_ADDRESS: // char[]
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_GPU_EU_COUNT: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_GPU_EU_SIMD_WIDTH: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_GPU_EU_SLICES: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_GPU_EU_COUNT_PER_SUBSLICE: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_GPU_SUBSLICES_PER_SLICE: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_GPU_HW_THREADS_PER_EU: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_MEMORY_BANDWIDTH: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_IMAGE_SRGB: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_BUILD_ON_SUBDEVICE: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_ATOMIC_64: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_ATOMIC_MEMORY_ORDER_CAPABILITIES: // ur_memory_order_capability_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_ATOMIC_MEMORY_SCOPE_CAPABILITIES: // ur_memory_scope_capability_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_ATOMIC_FENCE_ORDER_CAPABILITIES: // ur_memory_order_capability_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_ATOMIC_FENCE_SCOPE_CAPABILITIES: // ur_memory_scope_capability_flags_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_BFLOAT16: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_COMPUTE_QUEUE_INDICES: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_KERNEL_SET_SPECIALIZATION_CONSTANTS: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MEMORY_BUS_WIDTH: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_WORK_GROUPS_3D: // size_t[3]
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_ASYNC_BARRIER: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MEM_CHANNEL_SUPPORT: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_HOST_PIPE_READ_WRITE_SUPPORTED: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_REGISTERS_PER_WORK_GROUP: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_IP_VERSION: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_VIRTUAL_MEMORY_SUPPORT: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_ESIMD_SUPPORT: // ur_boot_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_COMPONENT_DEVICES: // ur_device_handle_t[]
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_COMPOSITE_DEVICE: // ur_device_handle_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_COMMAND_BUFFER_SUPPORT_EXP: // ur_boot_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_COMMAND_BUFFER_UPDATE_SUPPORT_EXP: // ur_boot_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_BINDLESS_IMAGES_SUPPORT_EXP: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_BINDLESS_IMAGES_SHARED_USM_SUPPORT_EXP: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_BINDLESS_IMAGES_1D_USM_SUPPORT_EXP: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_BINDLESS_IMAGES_2D_USM_SUPPORT_EXP: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_IMAGE_PITCH_ALIGN_EXP: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_IMAGE_LINEAR_WIDTH_EXP: // size_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_IMAGE_LINEAR_HEIGHT_EXP: // size_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MAX_IMAGE_LINEAR_PITCH_EXP: // size_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MIPMAP_SUPPORT_EXP: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MIPMAP_ANISOTROPY_SUPPORT_EXP: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MIPMAP_MAX_ANISOTROPY_EXP: // uint32_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_MIPMAP_LEVEL_REFERENCE_SUPPORT_EXP: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_INTEROP_MEMORY_IMPORT_SUPPORT_EXP: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_INTEROP_MEMORY_EXPORT_SUPPORT_EXP: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_INTEROP_SEMAPHORE_IMPORT_SUPPORT_EXP: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_INTEROP_SEMAPHORE_EXPORT_SUPPORT_EXP: // ur_bool_t
    return UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION;

  case UR_DEVICE_INFO_FORCE_UINT32:
    std::abort();
  }
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urDeviceRetain(ur_device_handle_t hDevice) {
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL
urDeviceRelease(ur_device_handle_t hDevice) {
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urDevicePartition(
    ur_device_handle_t hDevice,
    const ur_device_partition_properties_t *pProperties, uint32_t NumDevices,
    ur_device_handle_t *phSubDevices, uint32_t *pNumDevicesRet) {
  return UR_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

UR_APIEXPORT ur_result_t UR_APICALL urDeviceSelectBinary(
    ur_device_handle_t hDevice, const ur_device_binary_t *pBinaries,
    uint32_t numBinaries, uint32_t *pSelectedBinary) {
  for (uint32_t index = 0; index < numBinaries; index++) {
    if (std::strncmp(pBinaries[index].pDeviceTargetSpec,
                     UR_DEVICE_BINARY_TARGET_SPIRV64,
                     sizeof(UR_DEVICE_BINARY_TARGET_SPIRV64)) == 0) {
      *pSelectedBinary = index;
      return UR_RESULT_SUCCESS;
    }
  }
  return UR_RESULT_ERROR_INVALID_BINARY;
}

UR_APIEXPORT ur_result_t UR_APICALL urDeviceGetNativeHandle(
    ur_device_handle_t hDevice, ur_native_handle_t *phNativeDevice) {
  *phNativeDevice = reinterpret_cast<ur_native_handle_t>(hDevice->mDevice);
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urDeviceCreateWithNativeHandle(
    ur_native_handle_t hNativeDevice, ur_platform_handle_t hPlatform,
    const ur_device_native_properties_t *pProperties,
    ur_device_handle_t *phDevice) {
  auto mDevice = reinterpret_cast<MTL::Device *>(hNativeDevice);
  // TODO: Support multi-device configs.
  if (hPlatform->device->mDevice != mDevice) {
    return UR_RESULT_ERROR_DEVICE_LOST;
  }
  *phDevice = hPlatform->device;
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urDeviceGetGlobalTimestamps(
    ur_device_handle_t hDevice, uint64_t *pDeviceTimestamp,
    uint64_t *pHostTimestamp) {
  MTL::Timestamp cpuTimestamp, gpuTimestamp;
  hDevice->mDevice->sampleTimestamps(
      pHostTimestamp ? pHostTimestamp : &cpuTimestamp,
      pDeviceTimestamp ? pDeviceTimestamp : &gpuTimestamp);
  return UR_RESULT_SUCCESS;
}
