.. _crud:

===========================
Managing ontology documents
===========================

Ontology reading, editing and writing functionality is exposed via the :class:`CowlManager` API.
A :class:`CowlManager` instance manages multiple ontology documents.

.. doxygenstruct:: CowlManager

.. _reading:

Reading
=======

Ontologies can be read from files, memory buffers or input streams (see :class:`UIStream`).
Cowl can attempt ontology deserialization via multiple readers, and you can control which reader
is used in a number of ways:

- **At compile-time:** readers included in the compiled library can be selected
  by setting the ``COWL_READERS`` CMake variable. Built-in readers are exposed through
  ``cowl_reader_*()`` functions.
- **At run-time, globally:** you can set the default reader by calling :func:`cowl_set_reader()`.
- **At run-time, locally:** you can specify which reader you want :class:`CowlManager` to use
  via :func:`CowlManager::cowl_manager_set_reader()`.

You can integrate additional readers by providing suitably populated :class:`CowlReader` instances.
When implementing one, use the provided :class:`CowlIStream` object to handle detected
OWL constructs. If you need to manage prefixed IRIs, you can do so through the :class:`CowlSymTable`
instance available by calling :func:`CowlIStream::cowl_istream_get_sym_table()`.
Refer to the built-in readers if you need guidance.

.. doxygenstruct:: CowlReader

.. _import:

Import handling
---------------

Cowl delegates locating and loading imported ontologies to the end user via the
:class:`CowlImportLoader` interface. Import loaders can be either provided locally
to specific objects (such as via :func:`CowlManager::cowl_manager_set_import_loader()`),
or you can opt to specify a global import loader via :func:`cowl_set_import_loader()`.
If you do both, Cowl prioritizes local loaders, as you would expect.

.. doxygenstruct:: CowlImportLoader

.. _istream:

Reading ontologies as axiom streams
-----------------------------------

Other than deserializing ontologies into :class:`CowlOntology` objects, Cowl supports a more
lightweight abstraction to access ontology contents by means of :class:`CowlIStream` instances,
which can be obtained by calling :func:`CowlManager::cowl_manager_get_istream()`.
You must provide a suitably populated :class:`CowlIStreamHandlers` object,
which tells the library how each OWL construct detected in the byte stream should be handled.

.. doxygenstruct:: CowlIStream
.. doxygenstruct:: CowlIStreamHandlers

.. _editing:

Editing
=======

Ontologies can be edited by adding or removing axioms, annotations and other constructs,
as allowed by the :class:`CowlOntology` API. They can also be created from scratch by calling
:func:`CowlManager::cowl_manager_get_ontology()` and specifying a unique :class:`CowlOntologyId`
or a ``NULL`` one, in which case an anonymous ontology is created.

Access to syntactical details that are not relevant to logic, such as the mapping
between prefixed and full IRIs, is provided by a :class:`CowlSymTable` instance
retrievable by calling :func:`CowlOntology::cowl_ontology_get_sym_table()`.

.. doxygenstruct:: CowlSymTable

.. _writing:

Writing
=======

Similarly to reading, Cowl can write ontologies to files, buffers or custom output streams
(see :class:`UOStream`). You can control which writer is used in a number of ways:

- **At compile-time:** writers included in the compiled library can be selected
  by setting the ``COWL_WRITERS`` CMake variable. Built-in writers are exposed through
  ``cowl_writer_*()`` functions.
- **At run-time, globally:** you can set the default writer by calling :func:`cowl_set_writer()`.
- **At run-time, locally:** you can specify which writer you want :class:`CowlManager` to use
  via :func:`CowlManager::cowl_manager_set_writer()`.

Additional writers can be integrated by providing suitably populated :class:`CowlWriter` instances.
Refer to the built-in writers if you need guidance.

.. doxygenstruct:: CowlWriter

.. _ostream:

Writing ontologies as axiom streams
-----------------------------------

All standard OWL serialization formats allow ontologies to be serialized in such a way that
the resulting byte sequence consist of a *header*, a sequence of *axioms*, and a closing *footer*.
Ontology documents can therefore be serialized in a streaming fashion, without first building
an intermediate data store such as :class:`CowlOntology`. This greatly reduces memory
usage in cases where one needs to provide the OWL representation of some dynamic data.

To do so, the chosen writer must implement the :class:`CowlStreamWriter` interface, and the
ontology document must be serialized via the :class:`CowlOStream` API. Similarly to input streams,
you can retrieve a :class:`CowlOStream` instance via :func:`CowlManager::cowl_manager_get_ostream()`.

.. doxygenstruct:: CowlStreamWriter
.. doxygenstruct:: CowlOStream
