.. _reading:

==================
Reading ontologies
==================

.. contents:: :local:

Ontology objects
================

Ontologies can be read from files, memory buffers or input streams (see :struct:`UIStream`).
The easiest way to read an ontology is using :struct:`CowlOntology` constructors such as
:func:`cowl_ontology_from_path()` and :func:`cowl_ontology_from_stream()`. This leverages the
default reader to create a fully-fledged ontology object, which can then be queried and edited.

If you wish to use a specific reader, you can instead instantiate a :struct:`CowlReader` object
and leverage its APIs, such as :func:`cowl_reader_read_ontology()` and
:func:`cowl_reader_read_ontology_from_path()`.

Reader objects
==============

The architecture of Cowl is designed to support multiple ontology serialization formats.
You can control which readers are available and can be used in a number of ways:

- **At compile-time:** readers included in the compiled library can be selected
  by setting the ``COWL_READERS`` CMake variable, and you can specify a default reader
  through the ``COWL_DEFAULT_READER`` variable. Built-in readers are exposed through
  ``cowl_reader_*()`` functions.
- **At run-time:** the default reader can be changed by calling :func:`cowl_set_reader()`.
  You can also decide to use a specific reader by instantiating a :struct:`CowlReader` object.

Additional readers can be integrated by providing suitably populated :struct:`CowlReader` instances.
When implementing one, use the provided :struct:`CowlChangeHandler` object to handle detected OWL
constructs. The management of prefixed IRIs can be easened by using :struct:`CowlPrefixMap`
objects. Refer to the built-in readers if you need guidance on their implementation.

.. doxygenstruct:: CowlReader
.. doxygengroup:: CowlReader
   :content-only:

.. _istream:

Axiom streams
=============

Other than deserializing ontologies into :struct:`CowlOntology` instances, Cowl supports a more
lightweight abstraction to access ontology contents by means of :struct:`CowlChangeHandler`
objects. This allows you to process ontologies as streams of axioms and other constructs,
without the overhead of building a complete in-memory representation.

By providing a suitably populated :struct:`CowlChangeHandler` object to functions such as
:func:`cowl_reader_read()`, you can read ontology documents as sequences of changes, each
represented by a :struct:`CowlChange` struct. Each change indicates whether an OWL construct
was added or removed, and provides access to the relevant data, so that you can process it
as needed for your application.

.. doxygenstruct:: CowlChangeHandler
.. doxygengroup:: CowlChangeHandler
   :content-only:

.. doxygengroup:: CowlChange_types
   :content-only:
.. doxygengroup:: CowlChange_api
   :content-only:
