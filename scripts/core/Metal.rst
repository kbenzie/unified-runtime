<%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>

===========================
Metal UR Reference Document
===========================

Platform
========

Metal has no analagous concept to the `ur_platform_handle_t` object. The Metal
adapter uses platform initalization to get the default device from Metal and
store it for later use. Multi-device configurations are not supported at this
time as single GPU configuratons of Apple devices are the norm.

Device
======

A `MTLDevice` maps directly to the `ur_device_handle_t` object. A best effort
is made to implement the variaous :c:func:`urDeviceGetInfo` queries, however
some information is not available and will result in
`UR_RESULT_ERROR_UNSUPPORTED_ENUMERATION` being returned.

Context
=======

Metal has no analagous concept to the `ur_context_handle_t` object. The Metal
adapter only supports contexts containing a single device. As noted above, only
single device contexts are supported.

Memory
======

Storage Modes
-------------

The table below outlines the storage modes made available in Metal and how they
map to Unified Runtime memory concepts:

+----------------+---------+
| MTLStorageMode | Mapping |
+================+=========+
| shared_        | global  |
+----------------+---------+
| managed_       | global  |
+----------------+---------+
| private_       | local   |
+----------------+---------+
| memoryless_    | n/a     |
+----------------+---------+

.. _shared: https://developer.apple.com/documentation/metal/mtlstoragemode/shared
.. _managed: https://developer.apple.com/documentation/metal/mtlstoragemode/managed
.. _private: https://developer.apple.com/documentation/metal/mtlstoragemode/private
.. _memoryless: https://developer.apple.com/documentation/metal/mtlstoragemode/memoryless

For documentation on seting the storage mode when allocating a buffer or
texture, see `Setting Resource Storage Modes`_.

.. _Setting Resource Storage Modes: https://developer.apple.com/documentation/metal/resource_fundamentals/setting_resource_storage_modes

Buffer Creation
---------------

:c:enumerator:`UR_MEM_FLAG_ALLOC_HOST_POINTER`
    The default behaviour of the shared and managed `Storage Modes`_ is to
    allocate memory which is accessible to both CPU and GPU, no mapping is
    necessary.

:c:enumerator:`UR_MEM_FLAG_USE_HOST_POINTER`
    Maps to the `makeBuffer
    <https://developer.apple.com/documentation/metal/mtldevice/1433382-makebuffer>`_
    overload which "Creates a buffer that wraps an existing contiguous memory
    allocation."

:c:enumerator:`UR_MEM_FLAG_ALLOC_COPY_HOST_POINTER`
    Maps to the `makeBuffer
    <https://developer.apple.com/documentation/metal/mtldevice/1433429-makebuffer>`_
    overload which "Allocates a new buffer of a given length and initializes
    its contents by copying existing data into it."

Buffer Binding
--------------

When creating a :c:enum:`ur_mem_handle_t` the :c:enumerator:`UR_MEM_FLAG_READ_WRITE`,
:c:enumerator:`UR_MEM_FLAG_WRITE_ONLY`, and :c:enumerator:`UR_MEM_FLAG_READ_ONLY` flags can be specified by
the user with the first being the default. In Metal equivelent
MTLBindingAccess_ properties are specified when creating a MTLBufferBinding_ to
be attached to a pipeline.

.. _MTLBindingAccess: https://developer.apple.com/documentation/metal/mtlbindingaccess
.. _MTLBufferBinding: https://developer.apple.com/documentation/metal/mtlbufferbinding
