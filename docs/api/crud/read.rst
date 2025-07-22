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
- **At run-time:** you can specify which reader you want :struct:`CowlManager` to use
  via :func:`cowl_manager_set_reader()`. If a reader is not set for a manager,
  the :struct:`manager hierarchy <CowlManager>` is traversed upwards until a reader is found
  or the root is reached.

You can integrate additional readers by providing suitably populated :struct:`CowlReader` instances.
When implementing one, use the provided :struct:`CowlIStream` object to handle detected OWL
constructs. If you need to manage prefixed IRIs, you can do so through the :struct:`CowlPrefixMap`
instance available by calling :func:`cowl_istream_get_prefix_map()`.
Refer to the built-in readers if you need guidance on their implementation.

.. doxygenstruct:: CowlReader
.. doxygengroup:: CowlReader
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
