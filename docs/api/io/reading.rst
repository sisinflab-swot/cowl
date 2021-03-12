================
Ontology reading
================

.. doxygenstruct:: CowlReader

Import handling
===============

.. _import:

Cowl delegatets locating and loading imported ontologies to the end user via the
:class:`CowlImportLoader` interface. Import loaders can be either provided locally
to specific objects (such as via :func:`CowlReader::cowl_reader_set_import_loader()`),
or you can opt to specify a global import loader via :func:`cowl_api_set_import_loader()`.
If you do both, Cowl prioritizes local loaders, as you would expect.

.. doxygenstruct:: CowlImportLoader
