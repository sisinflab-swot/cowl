======
How-to
======

.. contents:: :local:

.. _building:

Building from source
====================

Cowl can be built and run on **Windows**, **macOS** and **Linux**. It has also been successfully
deployed to a wider range of platforms, including tiny microcontrollers, with relatively minor
build system setup. It can be compiled either as a **static** or **dynamic library**.

Requirements
------------

In order to compile the library, you will need at a minimum:

- GCC_, LLVM_ or MSVC_, any fairly recent version.
- CMake_ version 3.18 or later.

There are additional requirements depending on which additional components
you would like to build or compile (e.g. :ref:`readers <reading>`).

**Functional reader:**

- Flex_ version 2.6.4 or later.
- Bison_ version 3.0 or later.

**Documentation:**

- Doxygen_ version 1.8 or later.
- *(optional)* Sphinx_ version 2.0 or later, Breathe_ and the `Read The Docs Theme`_.

Sphinx is optional as Doxygen will already generate some form of HTML docs,
though not as fancy as the ones you are viewing.

Downloading the sources
-----------------------

You can find Cowl's code on its `git repository <git_url_>`_. Please note that it contains
submodules, so it is recommended that you clone it using the ``--recursive`` flag.

.. parsed-literal::

   git clone --recursive |git_url|

Compiling
---------

The following commands allow you to build Cowl:

.. code-block:: bash

   # Generate the build system
   cmake -B cmake-build -DCMAKE_BUILD_TYPE=Release

   # [Optional] Edit build settings (build type, optimization options, etc.)
   ccmake cmake-build

   # Build the library
   cmake --build cmake-build --config Release

   # [Optional] Build the documentation
   cmake --build cmake-build --target cowl-docs

   # [Optional] Install the library and its headers in <install path>
   cmake --install cmake-build --prefix <install path>

Linking
-------

If you're using CMake as your build system, you can link against Cowl by configuring your
*CMakeLists.txt* file as follows:

.. code-block:: cmake

    # Assuming Cowl's source is under "lib/cowl"
    add_subdirectory("lib/cowl" EXCLUDE_FROM_ALL)
    target_link_libraries(your-target PRIVATE cowl)

For other build systems or if you are building directly through a compiler, please refer
to their respective documentations. A relatively headache-free way to integrate Cowl
involves compiling it and then linking against the built library, making sure
the build system or compiler is aware of Cowl's headers. Note that in this case
you likely need to link against uLib as well.

Programming with Cowl
=====================

The easiest way to get started is by checking out the provided :ref:`examples <examples>`.
However, in order to understand the principles behind the API, reading
this section is strongly recommended.

API initialization
------------------

Before making any API call, you **must** invoke :func:`cowl_init()`, which is
needed in order to initialize the library's internal state.
Calling API members without initializing the API is undefined behavior.

Ontology deserialization
------------------------

In order to query an ontology you must first deserialize it, which can be done via
:class:`CowlManager`. Cowl can use multiple readers, either built-in or provided by the user.
For further information, refer to :ref:`the related documentation <reading>`.

OWL ontologies may `import <owl imports>`_ other ontologies, which may involve loading them
from mass storage or retrieving them from the network. Cowl's approach to imports reflects
its :ref:`focus on portability <about>`, so ontology retrieval
:ref:`is delegated to the end user <import>`.

Ontology queries
----------------

The core type of the API is :class:`CowlOntology`, which is essentially a collection
of :class:`CowlAxiom` instances. Under the hood, a :class:`CowlOntology` is an optimized
self-organizing in-memory store, which keeps axioms indexed by type and referenced entities,
allowing for very fast queries.

Ontology queries are functional, and query endpoints can be easily recognized in the
:class:`CowlOntology` API as they accept :class:`CowlIterator` instances.
See :ref:`the related documentation <querying>` and :ref:`examples <examples>`
for further information about how to use iterators.

Ontology editing and writing
----------------------------

Ontologies can be created from scratch, or existing ontologies can be edited by adding
or removing axioms, annotations and other constructs, as allowed by the :class:`CowlOntology` API.
Edited ontologies can then be written in any supported syntax
(see :ref:`the related documentation <writing>`).

Under the hood
==============

This section illustrates a few important low-level details
that you need to know in order to correctly use the library.

Memory management
-----------------

Cowl uses `reference counting`_ for memory management.
Reference counts are increased and decreased via :func:`CowlObject::cowl_retain()` and
:func:`CowlObject::cowl_release()`, respectively. Generally speaking, each retain call must
be balanced by a corresponding release, in order to avoid leaking memory. There are also
functions that return retained instances to new or existing objects, which you must also
make sure to release.

Functions that return retained instances are marked with the `COWL_RETAINED` attribute
in the header files, and are annotated as such in the API documentation.
If a function returns a pointer to a Cowl object, and `COWL_RETAINED` is not specified
in its declaration, then the returned instance is not retained, meaning its lifetime
is generally tied to that of some other object. If you need to keep it alive
after its owner has been deallocated, you must retain it.

Pseudo-inheritance
------------------

Since the `OWL 2 specification`_ is highly hierarchical, the API makes extensive use
of pseudo-inheritance for structs. Every data structure pseudo-inherits from :class:`CowlObject`,
whose concrete type can be queried via :func:`CowlObject::cowl_get_type()`.
Pseudo-inheritance allows you, as an example, to cast a :class:`CowlClass` to :class:`CowlClsExp`
or :class:`CowlObject` and back. Of course, if the API returns a base pseudo-class
such as :class:`CowlClsExp` or :class:`CowlObject`, and you are unsure about its concrete subclass,
you can check its type via `get_type` functions (e.g. :func:`CowlClsExp::cowl_cls_exp_get_type()`)
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
