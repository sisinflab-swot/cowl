.. _error:

===============
Handling errors
===============

Errors are reported by Cowl via return values (such as :type:`cowl_ret`), or by returning ``NULL``
on allocation errors. Sometimes this may not be enough, such as when reading ontology documents.
In these cases, more in-depth error handling is still being worked on.
