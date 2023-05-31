=============
Configuration
=============

Initialization
==============

Before making any API call, you **must** invoke :func:`cowl_init()`, which is needed
to initialize the library's internal state. This state is meant to be application-scoped,
therefore calling :func:`cowl_deinit()` is generally unnecessary. If you need to do so,
you **must not** use previously retrieved objects as they will be invalid.

.. doxygenfunction:: cowl_init
.. doxygenfunction:: cowl_deinit

Handlers and defaults
=====================

Global/default behaviour of the API can be configured via these functions. In general, you will
still be able to provide local overrides for specific objects.

.. doxygenfunction:: cowl_set_error_handler
.. doxygenfunction:: cowl_set_import_loader
.. doxygenfunction:: cowl_set_reader
.. doxygenfunction:: cowl_set_writer

Library version
===============

.. doxygenfunction:: cowl_get_version
.. doxygenfunction:: cowl_get_version_string
