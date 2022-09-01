.. _about:

=============
What is this?
=============

*Cowl* is a lightweight C/C++ API for working with OWL 2 ontologies, developed by
`SisInf Lab <swot_url_>`_ at the `Polytechnic University of Bari <poliba_url_>`_.

Motivation
==========

Access to OWL 2 ontologies is currently limited to platforms supporting Java
(via the `OWL API`_) or Python (through OWLReady_).
owl-cpp_ also exists for other platforms, though it deserializes
ontologies into RDF triples rather than OWL axioms and constructs.

Cowl aims to bring OWL support to most remaining platforms. In fact, it abides
to some key principles which make it very portable:

- It is written in **standard C11** with no compiler-specific extensions and no platform-specific
  API calls.
- It is completely **self-contained**, with no external dependencies other than
  `uLib`_ (which is also self-contained).
- It goes to great lengths to have a **tiny memory footprint** while being **very fast**,
  meaning it can run even on the most resource-constrained devices.

Features
========

Cowl is a complete implementation of the `OWL 2 specification`_. Currently supported features:

- Deserialization of ontologies into an optimized in-memory store.
- Arbitrarily complex ontology queries.
- Ontology editing (addition and removal of axioms, annotations, imports, etc.).
- Ontology serialization to files, memory buffers or custom streams.

.. _limitations:

Limitations
===========

While Cowl's architecture allows for multiple readers and writers, the library currently only
supports reading and writing OWL ontologies in **functional syntax**.

License
=======

Cowl is distributed under the `Eclipse Public License, Version 2.0`_.

.. _Eclipse Public License, Version 2.0: https://www.eclipse.org/legal/epl-2.0
.. _OWL 2 specification: https://www.w3.org/TR/owl2-syntax
.. _OWL API: https://github.com/owlcs/owlapi
.. _owl-cpp: http://owl-cpp.sourceforge.net
.. _OWLReady: https://bitbucket.org/jibalamy/owlready2
.. _semver: https://semver.org
.. _uLib: https://github.com/IvanoBilenchi/ulib
