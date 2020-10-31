=============
Configuration
=============

Initialization
==============

Before making any API call, you **must** invoke :func:`cowl_api_init()`, which is
needed in order to initialize the library's internal state.

Calling :func:`cowl_api_deinit()` is not strictly necessary, and may actually be inconvenient
if you plan to use Cowl functions again at a later time: this is because, once invoked,
you **must not** use objects previously retrieved via the API. You can, of course, use
objects retrieved after a new call to :func:`cowl_api_init()`.

.. doxygenfunction:: cowl_api_init
.. doxygenfunction:: cowl_api_deinit

Memory allocation
=================

You can override the default allocator by defining the `COWL_ALLOC_HEADERS` and `COWL_ALLOC_SOURCES`
CMake variable as the paths to header and source files implementing your custom :func:`malloc()`,
:func:`realloc()` and :func:`free()` replacements, which must be called
:func:`cowl_custom_malloc()`, :func:`cowl_custom_realloc()` and :func:`cowl_custom_free()`.

.. doxygendefine:: cowl_malloc
.. doxygendefine:: cowl_realloc
.. doxygendefine:: cowl_free
.. doxygendefine:: cowl_alloc
