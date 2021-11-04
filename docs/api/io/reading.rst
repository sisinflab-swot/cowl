.. _reading:

================
Ontology reading
================

In order to query an ontology you must first deserialize it. This can be done via
:class:`CowlReader`, which can read ontologies from files, memory buffers,
or input streams (see :class:`UIStream`).

.. doxygenstruct:: CowlReader

.. _parsers:

Parsers
=======

Cowl can attempt ontology deserialization via multiple parsers. You can control which parser
is used in a number of ways:

- **At compile-time:** parsers included in the compiled library can be selected
  by toggling ``COWL_PARSER_*`` CMake variables. Built-in parsers are exposed through
  ``cowl_parser_*_get()`` functions.
- **At run-time, globally:** you can set the default parser by calling `cowl_api_set_parser()`.
- **At run-time, locally:** you can specify which parser you want `CowlReader` to use
  by instantiating it via `CowlReader::cowl_reader_get_with_parser()`.

You can integrate additional parsers by providing suitably populated `CowlParser` instances.
When implementing one, use the provided `CowlParserCtx` instance for common parser tasks,
such as ontology population and error handling. Refer to the built-in parsers if you need guidance.

.. doxygenstruct:: CowlParser
.. doxygenstruct:: CowlParserCtx

.. _import:

Import handling
===============

Cowl delegates locating and loading imported ontologies to the end user via the
:class:`CowlImportLoader` interface. Import loaders can be either provided locally
to specific objects (such as via :func:`CowlReader::cowl_reader_set_import_loader()`),
or you can opt to specify a global import loader via :func:`cowl_api_set_import_loader()`.
If you do both, Cowl prioritizes local loaders, as you would expect.

.. doxygenstruct:: CowlImportLoader
