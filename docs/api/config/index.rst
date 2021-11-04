=============
Configuration
=============

Initialization
==============

Before making any API call, you **must** invoke :func:`cowl_api_init()`, which is
needed in order to initialize the library's internal state.

On the other hand, calling :func:`cowl_api_deinit()` is not strictly necessary, and may
actually be inconvenient if you plan to use Cowl functions again at a later time:
this is because, once invoked, you **must not** use objects previously retrieved via the API.
You can, of course, use objects retrieved after a new call to :func:`cowl_api_init()`.

.. doxygenfunction:: cowl_api_init
.. doxygenfunction:: cowl_api_deinit

Handlers and defaults
=====================

Global/default behaviour of the API can be configured via these functions. In general, you will
still be able to provide local overrides for specific objects.

.. doxygenfunction:: cowl_api_set_error_handler
.. doxygenfunction:: cowl_api_set_import_loader
.. doxygenfunction:: cowl_api_set_parser

Library version
===============

.. doxygenstruct:: CowlVersion
