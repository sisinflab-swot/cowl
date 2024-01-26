=============
Configuration
=============

.. contents:: :local:

Initialization
==============

Before making any API call, you **must** invoke :func:`cowl_init()`, which is needed
to initialize the library's internal state. This state is meant to be application-scoped,
therefore calling :func:`cowl_deinit()` is generally unnecessary. If you need to do so,
you **must not** use previously retrieved objects as they will be invalid.

.. doxygengroup:: init
   :content-only:

Handlers and defaults
=====================

Global/default behaviour of the API can be configured via these functions. In general, you will
still be able to provide local overrides for specific objects.

.. doxygengroup:: config
   :content-only:

Library version
===============

The library version can be retrieved via the following functions, allowing for some degree
of feature checking.

.. doxygengroup:: version
   :content-only:
