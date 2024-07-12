.. _about:

=============
What is this?
=============

*Cowl* is a lightweight C/C++ API for working with OWL 2 ontologies, developed by
`SisInf Lab <swot_url_>`_ at the `Polytechnic University of Bari <poliba_url_>`_.

Motivation
==========

Access to OWL 2 ontologies is currently limited to platforms supporting Java (via the `OWL API`_)
or Python (through OWLReady_). owl-cpp_ also exists for other platforms, though it is not
actively maintained, and it deserializes ontologies into RDF triples rather than
OWL axioms and constructs.

Cowl aims to bring OWL support to most remaining platforms, with an explicit focus on
embedded devices. In fact, it abides to some key principles which make it very portable:

- It is written in **standard C11** with no compiler- or platform-specific API calls.
- It is **self-contained**, with no runtime dependencies other than `uLib`_.
- It goes to great lengths to have a **tiny memory footprint** while being **very fast**.

The latter property not only allows Cowl to run on resource-constrained devices,
but it makes it a great option for performance-critical applications, as it is able to handle
very large ontologies much faster and using significantly less memory than other tools
[SWEET22]_.

Features
========

Cowl is a complete implementation of the `OWL 2 specification`_. Currently supported features:

- Deserialization of ontologies into an optimized in-memory store.
- Programmatic ontology queries.
- Ontology creation and editing (addition and removal of axioms, annotations, imports, etc.).
- Ontology serialization to files, memory buffers and custom byte streams.
- Ontology reading and writing as :ref:`axiom streams <istream>`, a novel lightweight technique
  to manipulate ontology documents.

.. _limitations:

Limitations
===========

While Cowl's architecture allows for multiple readers and writers, the library currently only
supports reading and writing OWL ontologies in **functional syntax**.

Publications
============

Additional context about Cowl is provided in the following academic publications:

.. [SWEET22] Ivano Bilenchi, Floriano Scioscia, Michele Ruta. |sweet2022|_.
   *First International Workshop on the Semantic Web of EveryThing (SWEET 2022)*, co-located
   with the *22nd International Conference on Web Engineering (ICWE 2022)*.

Projects
========

This is a collection of notable projects using Cowl. If your project uses Cowl, we'd love to
hear about it! Feel free to send us an email or `open an issue <git_url_>`_, and we will consider
adding it to this list.

- `Tiny-ME`_: reasoner and matchmaking engine for the Semantic Web of Everything.
- `RDF::Cowl <RDFCowl_>`_: bindings of the Cowl library for the Perl programming language.

License
=======

Cowl is distributed under the `Eclipse Public License, Version 2.0`_.

.. _Eclipse Public License, Version 2.0: https://www.eclipse.org/legal/epl-2.0
.. _OWL 2 specification: https://www.w3.org/TR/owl2-syntax
.. _OWL API: https://github.com/owlcs/owlapi
.. _owl-cpp: http://owl-cpp.sourceforge.net
.. _OWLReady: https://bitbucket.org/jibalamy/owlready2
.. _RDFCowl: https://metacpan.org/pod/RDF::Cowl
.. _semver: https://semver.org
.. |sweet2022| replace:: **Cowl: a lightweight OWL library for the Semantic Web of Everything**
.. _sweet2022: http://sisinflab.poliba.it/publications/2022/BSR22
.. _Tiny-ME: https://swot.sisinflab.poliba.it/tinyme
.. _uLib: https://github.com/IvanoBilenchi/ulib
