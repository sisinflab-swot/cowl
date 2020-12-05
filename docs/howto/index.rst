======
How-to
======

.. contents:: :local:

.. _building:

Building from source
====================

Cowl can be built and run on **Windows**, **macOS** and **Linux**. We have successfully
deployed it to a wider range of platforms, including tiny microcontrollers,
with relatively minor build system setup. It can be compiled via any fairly recent version
of **GCC**, **LLVM** or **MSVC**, either as a **static** or **dynamic library**.

Requirements
------------

In order to compile it, you will need:

- CMake_ version 3.16 or later.
- Flex_ version 2.6.4 or later.
- Bison_ version 3.0 or later.

This is enough to build the library. If you also want to build its documentation, you will need:

- Doxygen_ version 1.8 or later.
- Sphinx_ version 2.0 or later, Breathe_ and the `Read The Docs Theme`_.

Sphinx is actually optional as well. Just having Doxygen will already generate some form of
HTML docs, though not as fancy as the ones you are viewing.

Downloading the sources
-----------------------

You can find Cowl's code on its `git repository <git_url_>`_. Please note that it contains
submodules, so it is recommended that you clone it using the `--recursive` flag.

.. code-block:: bash

   git clone --recursive <repo URL> <dir>

Compiling
---------

The following commands allow you to build Cowl:

.. code-block:: bash

   # Generate the build system
   cmake -S . -B cmake-build

   # [Optional] Edit build settings (build type, optimization options, etc.)
   ccmake cmake-build

   # Build the libraries and copy public headers into the output dir
   cmake --build cmake-build

   # [Optional] Build the documentation
   cmake --build cmake-build --target cowl-docs

.. _basics:

Programming with Cowl
=====================

The easiest way to get started is by checking out the provided :ref:`examples`.
However, in order to understand the principles behind the API, reading
this section is strongly recommended.

API initialization
------------------

Before making any API call, you **must** invoke :func:`cowl_api_init()`, which is
needed in order to initialize the library's internal state.
Calling API members without initializing the API is undefined behavior.

Ontology deserialization
------------------------

In order to query an ontology you must first deserialize it. This can be done via the
:func:`cowl_parser_parse_ontology()` function of :class:`CowlParser`. In general, ontologies may
`import <owl imports_>`_ other ontologies, which may involve retrieving them from the network.
Cowl's approach to imports reflects its :ref:`focus on portability <about>`, so ontology retrieval
is delegated to the end user via the :class:`CowlImportLoader` interface.

Ontology queries
----------------

The core type of the API is :class:`CowlOntology`, which consists of a set of :class:`CowlAxiom`
instances. The base mechanism for querying a :class:`CowlOntology` is invoking its iterator
member functions, which generally accept :class:`CowlIterator` instances.

:class:`CowlIterator` is a wrapper around a function that is called for every element matched
by the query. By providing a generic context pointer, you can plug any custom data structure
(loggers, collections, etc.), which allows for arbitrarily complex queries.

The iterator function returns a `boolean` that can be used to control iteration:
by returning `true` iteration goes on to the next element, while returning `false`
causes it to stop. This is useful if, for example, you want to find the first element
matching certain criteria.

Memory management
-----------------

Cowl uses `reference counting`_ for memory management.
You increase and decrease the reference count via `retain` and `release` member functions
available for every data structure. The API docs are very explicit about which functions
return already retained instances, which you must `release`. If nothing is specified,
then the returned instance is not retained, meaning its lifetime is generally tied
to that of some other object. If you need to keep it alive after its owner
has been deallocated, you must `retain` it.

Pseudo-inheritance
------------------

Since the `OWL 2 specification`_ is highly hierarchical, the API makes extensive use
of pseudo-inheritance for structs. Every data structure pseudo-inherits from :class:`CowlObject`,
whose concrete type can be queried via :func:`cowl_object_get_type()`.
Pseudo-inheritance allows you, as an example, to cast a :class:`CowlClass` to :class:`CowlClsExp`
or :class:`CowlObject` and back. Of course, if the API returns a base pseudo-class
such as :class:`CowlClsExp` or :class:`CowlObject`, and you are unsure about its concrete subclass,
you can check its type via `get_type` functions (e.g. :func:`cowl_cls_exp_get_type()`)
and cast accordingly. The API docs for type enumerations explicitly state the concrete struct
associated with every type.

.. _Bison: https://www.gnu.org/software/bison
.. _Breathe: https://breathe.readthedocs.io
.. _CMake: https://cmake.org
.. _Doxygen: http://doxygen.nl
.. _Flex: https://github.com/westes/flex
.. _OWL imports: https://www.w3.org/TR/owl2-syntax/#Imports
.. _OWL 2 specification: https://www.w3.org/TR/owl2-syntax
.. _Read The Docs Theme: https://sphinx-rtd-theme.readthedocs.io
.. _reference counting: https://en.wikipedia.org/wiki/Reference_counting
.. _Sphinx: http://sphinx-doc.org
