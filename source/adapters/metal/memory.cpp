//===--------- memory.cpp - Metal Adapter ---------------------------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "memory.hpp"
#include "context.hpp"
#include "device.hpp"

namespace ur::metal {
buffer::buffer(ur_context_handle_t hContext, ur_mem_flags_t flags, size_t size,
               const ur_buffer_properties_t *pProperties,
               ur_mem_handle_t *phBuffer)
    : ur_mem_handle_t_(hContext, flags, ur_mem_handle_t_::BUFFER), size(size) {
  // The default storage mode is specified, which means the buffer is
  // accessible on both CPU and GPU, this is shared on Apple Silicon or managed
  // otherwise i.e. UR_MEM_FLAG_ALLOC_COPY_HOST_POINTER is the default.
  MTL::ResourceOptions options = 0;
  // FIXME: Creating a buffer from mDevice means that hazard tracking is
  // enabled, this is the safe but slow option.
  auto mDevice = hContext->device->mDevice;
  if (flags & UR_MEM_FLAG_ALLOC_COPY_HOST_POINTER) {
    mBuffer = mDevice->newBuffer(pProperties->pHost, size, options);
  } else if (flags & UR_MEM_FLAG_USE_HOST_POINTER) {
    mBuffer = mDevice->newBuffer(pProperties->pHost, size, options, nullptr);
  } else {
    mBuffer = mDevice->newBuffer(size, options);
  }
}

buffer_partition::buffer_partition(ur::metal::buffer *parent,
                                   ur_mem_flags_t flags,
                                   const ur_buffer_region_t *pRegion)
    : ur_mem_handle_t_(parent->context, flags, ur_mem_handle_t_::PARTITION),
      size(pRegion->size) {
  parent->retain();
  MTL::ResourceOptions options = 0;
  uintptr_t baseAddr = reinterpret_cast<uintptr_t>(parent->mBuffer->contents());
  baseAddr += pRegion->origin;
  auto mDevice = parent->context->device->mDevice;
  mBuffer = mDevice->newBuffer(reinterpret_cast<void *>(baseAddr),
                               pRegion->size, options, nullptr);
}
} // namespace ur::metal

UR_APIEXPORT ur_result_t UR_APICALL urMemBufferCreate(
    ur_context_handle_t hContext, ur_mem_flags_t flags, size_t size,
    const ur_buffer_properties_t *pProperties, ur_mem_handle_t *phBuffer) {
  std::unique_ptr<ur::metal::buffer> buffer;
  try {
    buffer = std::make_unique<ur::metal::buffer>(hContext, flags, size,
                                                 pProperties, phBuffer);
  } catch (const std::bad_alloc &) {
    return UR_RESULT_ERROR_OUT_OF_HOST_MEMORY;
  } catch (const ur_result_t &error) {
    return error;
  }
  *phBuffer = buffer.release();
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urMemImageCreate(
    ur_context_handle_t hContext, ur_mem_flags_t flags,
    const ur_image_format_t *pImageFormat, const ur_image_desc_t *pImageDesc,
    void *pHost, ur_mem_handle_t *phMem) {
  return UR_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

UR_APIEXPORT ur_result_t UR_APICALL urMemRetain(ur_mem_handle_t hMem) {
  hMem->retain();
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urMemRelease(ur_mem_handle_t hMem) {
  if (hMem->release() == 0) {
    delete hMem;
  }
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urMemBufferPartition(
    ur_mem_handle_t hBuffer, ur_mem_flags_t flags,
    [[maybe_unused]] ur_buffer_create_type_t bufferCreateType,
    const ur_buffer_region_t *pRegion, ur_mem_handle_t *phBuffer) {
  if (hBuffer->type != ur_mem_handle_t_::BUFFER) {
    return UR_RESULT_ERROR_INVALID_MEM_OBJECT;
  }
  auto parent = static_cast<ur::metal::buffer *>(hBuffer);
  if (parent->flags & UR_MEM_FLAG_READ_ONLY && flags & UR_MEM_FLAG_READ_WRITE) {
    return UR_RESULT_ERROR_INVALID_VALUE;
  }
  if (parent->size < (pRegion->origin + pRegion->size)) {
    return UR_RESULT_ERROR_INVALID_BUFFER_SIZE;
  }

  std::unique_ptr<ur::metal::buffer_partition> buffer;
  try {
    buffer =
        std::make_unique<ur::metal::buffer_partition>(parent, flags, pRegion);
  } catch (const std::bad_alloc &) {
    return UR_RESULT_ERROR_OUT_OF_HOST_MEMORY;
  } catch (const ur_result_t &error) {
    return error;
  }
  *phBuffer = buffer.release();

  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL
urMemGetNativeHandle(ur_mem_handle_t hMem, ur_device_handle_t hDevice,
                     ur_native_handle_t *phNativeMem) {
  return UR_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

UR_APIEXPORT ur_result_t UR_APICALL urMemBufferCreateWithNativeHandle(
    ur_native_handle_t hNativeMem, ur_context_handle_t hContext,
    const ur_mem_native_properties_t *pProperties, ur_mem_handle_t *phMem) {
  return UR_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

UR_APIEXPORT ur_result_t UR_APICALL urMemImageCreateWithNativeHandle(
    ur_native_handle_t hNativeMem, ur_context_handle_t hContext,
    const ur_image_format_t *pImageFormat, const ur_image_desc_t *pImageDesc,
    const ur_mem_native_properties_t *pProperties, ur_mem_handle_t *phMem) {
  return UR_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

UR_APIEXPORT ur_result_t UR_APICALL urMemGetInfo(ur_mem_handle_t hMemory,
                                                 ur_mem_info_t propName,
                                                 size_t propSize,
                                                 void *pPropValue,
                                                 size_t *pPropSizeRet) {
  return UR_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

UR_APIEXPORT ur_result_t UR_APICALL urMemImageGetInfo(ur_mem_handle_t hMemory,
                                                      ur_image_info_t propName,
                                                      size_t propSize,
                                                      void *pPropValue,
                                                      size_t *pPropSizeRet) {
  return UR_RESULT_ERROR_UNSUPPORTED_FEATURE;
}
