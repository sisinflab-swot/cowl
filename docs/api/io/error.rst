.. _error:

==============
Error handling
==============

Errors are reported by Cowl via return values (such as :type:`cowl_ret`), or by returning ``NULL``
on allocation errors. Sometimes this may not be enough, such as when reading ontology documents:
in these cases, Cowl lets you setup :class:`CowlErrorHandler` instances, which grant more
fine-grained control over errors.

Error handlers can be either provided locally to specific objects (such as via
:func:`CowlReader::cowl_reader_set_error_handler()`), or you can opt to specify a global
error handler via :func:`cowl_api_set_error_handler()`. If you do both, Cowl prioritizes
local error handlers, as you would expect.

.. doxygenstruct:: CowlErrorHandler
.. doxygenstruct:: CowlError
.. doxygenstruct:: CowlErrorLoc
