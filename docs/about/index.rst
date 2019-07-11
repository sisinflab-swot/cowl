=============
What is this?
=============

*Cowl* is a lightweight C API for working with OWL 2 ontologies, developed by
`SisInf Lab`_ at the `Polytechnic University of Bari`_.

Motivation
==========

Access to OWL 2 ontologies is currently limited to platforms supporting Java
(via the `OWL API`_) or Python (through OWLReady_).
owl-cpp_ also exists for other platforms, though it deserializes
ontologies into RDF triples rather than OWL axioms and constructs.

Cowl aims to bring OWL support to most remaining platforms. In fact, it abides
to some key principles which make it very portable:

- It's written in **standard C11** with no compiler-specific extensions and no platform-specific
  API calls.
- It's completely **self-contained**, with no external dependencies other than
  `Vector(T)`_ and uHash_ (which are also self-contained and maintained by us).
- It goes to great lengths to have a **tiny memory footprint** while being **very fast**,
  meaning it can run even on the most resource-constrained devices.

Features
========

Cowl is a complete implementation of the `OWL 2 specification`_.
As of right now it allows you to parse OWL 2 ontologies and query them
for axioms and other constructs.

Limitations
===========

Cowl currently only supports ontologies in **functional syntax**.
Furthermore, it does not yet provide ontology editing and serialization capabilities.
We plan to address these shortcomings soon.

License
=======

Cowl is distributed under the `Eclipse Public License, Version 2.0`_.

.. _Eclipse Public License, Version 2.0: https://www.eclipse.org/legal/epl-2.0
.. _OWL 2 specification: https://www.w3.org/TR/owl2-syntax
.. _OWL API: https://github.com/owlcs/owlapi
.. _owl-cpp: http://owl-cpp.sourceforge.net
.. _OWLReady: https://bitbucket.org/jibalamy/owlready2
.. _Polytechnic University of Bari: http://www.poliba.it
.. _SisInf Lab: http://sisinflab.poliba.it/swottools
.. _uHash: https://github.com/IvanoBilenchi/uhash
.. _Vector(T): https://github.com/IvanoBilenchi/vector_t
