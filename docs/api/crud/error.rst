.. _error:

===============
Handling errors
===============

Errors are reported by Cowl via return values (such as :type:`cowl_ret`), or by returning ``NULL``
on allocation errors. Sometimes this may not be enough, such as when reading ontology documents.
In these cases, Cowl supports a more detailed error reporting mechanism via the :type:`CowlError`
type, whose instances are returned by functions such as :func:`cowl_reader_last_error`.

.. doxygenstruct:: CowlError
.. doxygengroup:: CowlError
   :content-only:
