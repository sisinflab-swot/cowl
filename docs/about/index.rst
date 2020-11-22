.. _about:

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

- It is written in **standard C11** with no compiler-specific extensions and no platform-specific
  API calls.
- It is completely **self-contained**, with no external dependencies other than
  `uLib`_ (which is also self-contained).
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

Finally, it is important to note that the library is in **early development**, as denoted by
the `0.x version number <semver_>`_, so expect its API to change between minor releases.
We will bump it to 1.0.0 once we are confident enough to make the public API stable.

License
=======

Cowl is distributed under the `Eclipse Public License, Version 2.0`_.

.. _Eclipse Public License, Version 2.0: https://www.eclipse.org/legal/epl-2.0
.. _OWL 2 specification: https://www.w3.org/TR/owl2-syntax
.. _OWL API: https://github.com/owlcs/owlapi
.. _owl-cpp: http://owl-cpp.sourceforge.net
.. _OWLReady: https://bitbucket.org/jibalamy/owlready2
.. _Polytechnic University of Bari: http://www.poliba.it
.. _semver: https://semver.org
.. _SisInf Lab: http://swot.sisinflab.poliba.it
.. _uLib: https://github.com/IvanoBilenchi/ulib
