==================
API initialization
==================

.. doxygenfunction:: cowl_api_init
.. doxygenfunction:: cowl_api_deinit

=================
Memory allocation
=================

You can override the default allocator by defining the :func:`cowl_malloc`,
:func:`cowl_realloc` and :func:`cowl_free` macros.

.. doxygendefine:: cowl_malloc
.. doxygendefine:: cowl_realloc
.. doxygendefine:: cowl_free
.. doxygendefine:: cowl_alloc
