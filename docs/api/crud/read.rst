.. _reading:

==================
Reading ontologies
==================

.. contents:: :local:

Readers
=======

Ontologies can be read from files, memory buffers or input streams (see :struct:`UIStream`) through
the :struct:`CowlManager` object. Cowl can attempt ontology deserialization via multiple readers,
and you can control which reader is used in a number of ways:

- **At compile-time:** readers included in the compiled library can be selected
  by setting the ``COWL_READERS`` CMake variable. Built-in readers are exposed through
  ``cowl_reader_*()`` functions.
- **At run-time, globally:** you can set the default reader by calling :func:`cowl_set_reader()`.
- **At run-time, locally:** you can specify which reader you want :struct:`CowlManager` to use
  via :func:`cowl_manager_set_reader()`.

You can integrate additional readers by providing suitably populated :struct:`CowlReader` instances.
When implementing one, use the provided :struct:`CowlIStream` object to handle detected OWL
constructs. If you need to manage prefixed IRIs, you can do so through the :struct:`CowlSymTable`
instance available by calling :func:`cowl_istream_get_sym_table()`.
Refer to the built-in readers if you need guidance.

.. doxygenstruct:: CowlReader
.. doxygengroup:: CowlReader
   :content-only:

.. _import:

Handling imports
================

Cowl delegates locating and loading imported ontologies to the end user via the
:struct:`CowlImportResolver` interface. Import resolvers can be provided to :struct:`CowlManager`
instances via :func:`cowl_manager_set_import_resolver()`. By default, :struct:`CowlManager` will
attempt to resolve imports based on the IRIs of ontologies it is currently responsible for,
i.e. those that have been loaded or created through it.

.. doxygenstruct:: CowlImportResolver
.. doxygengroup:: CowlImportResolver
   :content-only:

.. _istream:

Reading ontologies as axiom streams
===================================

Other than deserializing ontologies into :struct:`CowlOntology` objects, Cowl supports a more
lightweight abstraction to access ontology contents by means of :struct:`CowlIStream` instances,
which can be obtained by calling :func:`cowl_manager_get_istream()`. You must provide a suitably
populated :struct:`CowlIStreamHandlers` object, which tells the library how each OWL construct
detected in the byte stream should be handled.

.. doxygenstruct:: CowlIStream
.. doxygengroup:: CowlIStream
   :content-only:
.. doxygenstruct:: CowlIStreamHandlers
