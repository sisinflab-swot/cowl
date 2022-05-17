======
How-to
======

.. contents:: :local:

.. _building:

Building from source
====================

Cowl can be built and run on **Windows**, **macOS** and **Linux**. We have successfully deployed it
to a wider range of platforms, including tiny microcontrollers, with relatively minor
build system setup. It can be compiled either as a **static** or **dynamic library**.

Requirements
------------

In order to compile the library, you will need at a minimum:

- GCC_, LLVM_ or MSVC_, any fairly recent version.
- CMake_ version 3.18 or later.

There are additional requirements depending on which additional components
you would like to build or compile (e.g. :ref:`parsers <parsers>`).

**Functional parser:**

- Flex_ version 2.6.4 or later.
- Bison_ version 3.0 or later.

**Documentation:**

- Doxygen_ version 1.8 or later.
- Sphinx_ version 2.0 or later, Breathe_ and the `Read The Docs Theme`_.

Sphinx is optional: Doxygen will already generate some form of HTML docs,
though not as fancy as the ones you are viewing.

Downloading the sources
-----------------------

You can find Cowl's code on its `git repository <git_url_>`_. Please note that it contains
submodules, so it is recommended that you clone it using the ``--recursive`` flag.

.. code-block:: bash

   git clone --recursive <repo URL> <dir>

Compiling
---------

The following commands allow you to build Cowl:

.. code-block:: bash

   # Generate the build system
   cmake -B cmake-build

   # [Optional] Edit build settings (build type, optimization options, etc.)
   ccmake cmake-build

   # Build the libraries and copy public headers into the output dir
   cmake --build cmake-build

   # [Optional] Build the documentation
   cmake --build cmake-build --target cowl-docs

Programming with Cowl
=====================

The easiest way to get started is by checking out the provided :ref:`examples <examples>`.
However, in order to understand the principles behind the API, reading
this section is strongly recommended.

API initialization
------------------

Before making any API call, you **must** invoke :func:`cowl_api_init()`, which is
needed in order to initialize the library's internal state.
Calling API members without initializing the API is undefined behavior.

Ontology deserialization
------------------------

In order to query an ontology you must first deserialize it, which can be done via
:class:`CowlManager`. Cowl can use multiple parsers, either built-in or provided by the user.
For further information, refer to :ref:`the related documentation <reading>`.

OWL ontologies may `import <owl imports_>`_ other ontologies, which may involve loading them
from mass storage or retrieving them from the network. Cowl's approach to imports reflects
its :ref:`focus on portability <about>`, so ontology retrieval
:ref:`is delegated to the end user <import>`.

Ontology queries
----------------

The core type of the API is :class:`CowlOntology`, which consists of a set of :class:`CowlAxiom`
instances. The base mechanism for querying a :class:`CowlOntology` is invoking its iterator
member functions, which generally accept :class:`CowlIterator` instances.

:class:`CowlIterator` is a wrapper around a function that is called for every element matched
by the query. By providing a generic context pointer, you can plug any custom data structure
(loggers, collections, etc.), which allows for arbitrarily complex queries.

Memory management
-----------------

Cowl uses `reference counting`_ for memory management.
You increase and decrease the reference count via `retain` and `release` member functions
available for every data structure. The API docs are very explicit about which functions
return already retained instances, which you must release. If nothing is specified,
then the returned instance is not retained, meaning its lifetime is generally tied
to that of some other object. If you need to keep it alive after its owner
has been deallocated, you must retain it.

Pseudo-inheritance
------------------

Since the `OWL 2 specification`_ is highly hierarchical, the API makes extensive use
of pseudo-inheritance for structs. Every data structure pseudo-inherits from :class:`CowlObject`,
whose concrete type can be queried via :func:`cowl_get_type()`.
Pseudo-inheritance allows you, as an example, to cast a :class:`CowlClass` to :class:`CowlClsExp`
or :class:`CowlObject` and back. Of course, if the API returns a base pseudo-class
such as :class:`CowlClsExp` or :class:`CowlObject`, and you are unsure about its concrete subclass,
you can check its type via `get_type` functions (e.g. :func:`cowl_cls_exp_get_type()`)
and cast accordingly. The API docs for type enumerations explicitly state the concrete type
associated with every enumeration value.

.. _Bison: https://www.gnu.org/software/bison
.. _Breathe: https://breathe.readthedocs.io
.. _CMake: https://cmake.org
.. _Doxygen: http://doxygen.nl
.. _Flex: https://github.com/westes/flex
.. _GCC: https://gcc.gnu.org
.. _LLVM: https://llvm.org
.. _MSVC: https://visualstudio.microsoft.com
.. _OWL imports: https://www.w3.org/TR/owl2-syntax/#Imports
.. _OWL 2 specification: https://www.w3.org/TR/owl2-syntax
.. _Read The Docs Theme: https://sphinx-rtd-theme.readthedocs.io
.. _reference counting: https://en.wikipedia.org/wiki/Reference_counting
.. _Sphinx: http://sphinx-doc.org
