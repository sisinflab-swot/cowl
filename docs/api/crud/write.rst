.. _writing:

==================
Writing ontologies
==================

.. contents:: :local:

Writers
=======

Similarly to reading, Cowl can write ontologies to files, buffers or custom output streams
(see :struct:`UOStream`) through the :struct:`CowlManager` object.
You can control which writer is used in a number of ways:

- **At compile-time:** writers included in the compiled library can be selected
  by setting the ``COWL_WRITERS`` CMake variable. Built-in writers are exposed through
  ``cowl_writer_*()`` functions.
- **At run-time, globally:** you can set the default writer by calling :func:`cowl_set_writer()`.
- **At run-time, locally:** you can specify which writer you want :struct:`CowlManager` to use
  via :func:`cowl_manager_set_writer()`.

Additional writers can be integrated by providing suitably populated :struct:`CowlWriter` instances.
Refer to the built-in writers if you need guidance.

.. doxygenstruct:: CowlWriter
.. doxygengroup:: CowlWriter
   :content-only:

.. _ostream:

Writing ontologies as axiom streams
===================================

All standard OWL serialization formats allow ontologies to be serialized in such a way that
the resulting byte sequence consist of a *header*, a sequence of *axioms*, and a closing *footer*.
Ontology documents can therefore be serialized in a streaming fashion, without first building
an intermediate data store such as :struct:`CowlOntology`. This greatly reduces memory
usage in cases where one needs to provide the OWL representation of some dynamic data.

To do so, the chosen writer must implement the :struct:`CowlStreamWriter` interface, and the
ontology document must be serialized via the :struct:`CowlOStream` API. Similarly to input streams,
you can retrieve a :struct:`CowlOStream` instance via :func:`cowl_manager_get_ostream()`.

.. doxygenstruct:: CowlStreamWriter
.. doxygenstruct:: CowlOStream
.. doxygengroup:: CowlOStream
   :content-only:
