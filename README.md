# Cowl

*Cowl* is a lightweight C API for working with OWL 2 ontologies, developed by
[SisInf Lab][swot] at the [Polytechnic University of Bari][poliba].

### Motivation

Access to OWL 2 ontologies is currently limited to platforms supporting Java
(via the [OWL API][owlapi]) or Python (through [OWLReady][owlready]).
[owl-cpp][owlcpp] also exists for other platforms, though it deserializes
ontologies into RDF triples rather than OWL axioms and constructs.

Cowl aims to bring OWL support to most remaining platforms. In fact, it abides
to some key principles which make it very portable:

- It's written in **standard C11** with no compiler-specific extensions and no platform-specific
  API calls.
- It's completely **self-contained**, with no external dependencies other than
  [Vector(T)][vector] and [uHash][uhash] (which are also self-contained and maintained by us).
- It goes to great lengths to have a **tiny memory footprint** while being **very fast**,
  meaning it can run even on the most resource-constrained devices.

### Features

Cowl is a complete implementation of the [OWL 2 specification][owl2].
As of right now it allows you to parse OWL 2 ontologies and query them
for axioms and other constructs.

### Limitations

Cowl currently only supports ontologies in **functional syntax**.
Furthermore, it does not yet provide ontology editing and serialization capabilities.
We plan to address these shortcomings soon.

### Documentation

The API is thoroughly documented. HTML docs are automatically generated while building
if [Doxygen][doxygen] is installed. For convenience, the latest HTML docs
are also available [online][docs].

### License

Cowl is distributed under the [Eclipse Public License, Version 2.0][epl2].

[docs]: http://sisinflab.poliba.it/swottools/cowl
[doxygen]: http://www.doxygen.nl
[epl2]: https://www.eclipse.org/legal/epl-2.0
[owl2]: https://www.w3.org/TR/owl2-syntax
[owlapi]: https://github.com/owlcs/owlapi
[owlcpp]: http://owl-cpp.sourceforge.net
[owlready]: https://bitbucket.org/jibalamy/owlready2
[poliba]: http://www.poliba.it
[swot]: http://sisinflab.poliba.it/swottools
[uhash]: https://github.com/IvanoBilenchi/uhash
[vector]: https://github.com/IvanoBilenchi/vector_t
