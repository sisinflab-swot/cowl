.. _reading:

================
Ontology reading
================

In order to query an ontology you must first deserialize it. This can be done via
:class:`CowlManager`, which can read ontologies from files, memory buffers,
or input streams (see :class:`UIStream`).

.. doxygenstruct:: CowlManager

.. _parsers:

Parsers
=======

Cowl can attempt ontology deserialization via multiple parsers. You can control which parser
is used in a number of ways:

- **At compile-time:** parsers included in the compiled library can be selected
  by toggling ``COWL_PARSER_*`` CMake variables. Built-in parsers are exposed through
  ``cowl_parser_*_get()`` functions.
- **At run-time, globally:** you can set the default parser by calling `cowl_api_set_parser()`.
- **At run-time, locally:** you can specify which parser you want `CowlManager` to use
  via `CowlManager::cowl_manager_set_parser()`.

You can integrate additional parsers by providing suitably populated `CowlParser` instances.
When implementing one, use the provided `CowlEditor` instance for common parser tasks,
such as ontology population and error handling. Refer to the built-in parsers if you need guidance.

.. doxygenstruct:: CowlParser
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
