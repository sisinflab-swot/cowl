.. _writing:

==================
Writing ontologies
==================

.. contents:: :local:

Writer objects
==============

Similarly to reading, Cowl can write ontologies to files, buffers or custom output streams
(see :struct:`UOStream`). You can either use :struct:`CowlOntology` functions such as
:func:`cowl_ontology_to_path()` and :func:`cowl_ontology_to_stream()`, which leverage the default
writer to serialize the ontology, or instantiate and use a specific :struct:`CowlWriter`.

Writers can be configured and used in a number of ways:

- **At compile-time:** writers included in the compiled library can be selected
  by setting the ``COWL_WRITERS`` CMake variable. Built-in writers are exposed through
  ``cowl_writer_*()`` functions.
- **At run-time:** the default writer can be changed by calling :func:`cowl_set_writer()`.
  You can also decide to use a specific writer by instantiating a :struct:`CowlWriter` object.

Additional writers can be integrated by providing suitably populated :struct:`CowlWriter` instances.
Refer to the built-in writers if you need guidance on their implementation.

.. doxygenstruct:: CowlWriter
.. doxygengroup:: CowlWriter
   :content-only:

.. _ostream:

Axiom streams
=============

All standard OWL serialization formats allow ontologies to be serialized in such a way that
the resulting byte sequence consist of a *header*, a sequence of *axioms*, and a closing *footer*.
Ontology documents can therefore be serialized in a streaming fashion, without first building
an intermediate data store such as :struct:`CowlOntology`. This greatly reduces memory
usage in cases where one needs to provide the OWL representation of some dynamic data.

To do so, the chosen writer must support stream serialization by implementing the
:code:`write_header`, :code:`write_axiom`, and :code:`write_footer`` functions.
To serialize an ontology document using this technique, you must first call
:func:`cowl_writer_write_header()` to write the header, then call :func:`cowl_writer_write_axiom()`
for each axiom to be serialized, and finally call :func:`cowl_writer_write_footer()`.

.. doxygenstruct:: CowlOntologyHeader
.. doxygengroup:: CowlOntologyHeader
   :content-only:
