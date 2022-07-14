.. _reading:

================
Ontology reading
================

In order to query an ontology you must first deserialize it. This can be done via
:class:`CowlManager`, which can read ontologies from files, memory buffers,
or input streams (see :class:`UIStream`).

.. doxygenstruct:: CowlManager

.. _readers:

Readers
=======

Cowl can attempt ontology deserialization via multiple readers. You can control which reader
is used in a number of ways:

- **At compile-time:** readers included in the compiled library can be selected
  by toggling ``COWL_READER_*`` CMake variables. Built-in readers are exposed through
  ``cowl_reader_*_get()`` functions.
- **At run-time, globally:** you can set the default reader by calling `cowl_api_set_reader()`.
- **At run-time, locally:** you can specify which reader you want `CowlManager` to use
  via `CowlManager::cowl_manager_set_reader()`.

You can integrate additional readers by providing suitably populated `CowlReader` instances.
When implementing one, use the provided `CowlEditor` instance for common reader tasks,
such as ontology population and error handling. Refer to the built-in readers if you need guidance.

.. doxygenstruct:: CowlReader
.. doxygenstruct:: CowlEditor

.. _import:

Import handling
===============

Cowl delegates locating and loading imported ontologies to the end user via the
:class:`CowlImportLoader` interface. Import loaders can be either provided locally
to specific objects (such as via :func:`CowlManager::cowl_manager_set_import_loader()`),
or you can opt to specify a global import loader via :func:`cowl_api_set_import_loader()`.
If you do both, Cowl prioritizes local loaders, as you would expect.

.. doxygenstruct:: CowlImportLoader
