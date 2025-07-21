.. _error:

===============
Handling errors
===============

Errors are reported by Cowl via return values (such as :type:`cowl_ret`), or by returning ``NULL``
on allocation errors. Sometimes this may not be enough, such as when reading ontology documents:
in these cases, Cowl lets you setup :struct:`CowlErrorHandler` instances, which grant more
fine-grained control over errors.

Error handlers can be provided to :struct:`CowlManager` instances through the
:func:`cowl_manager_set_error_handler()` function. If an error handler is not set for a manager,
the :struct:`manager hierarchy <CowlManager>` is traversed upwards until a handler is found
or the root is reached.

.. doxygenstruct:: CowlErrorHandler
.. doxygenstruct:: CowlError
.. doxygenstruct:: CowlSyntaxError
.. doxygenstruct:: CowlErrorLoc
.. doxygengroup:: CowlError
   :content-only:
