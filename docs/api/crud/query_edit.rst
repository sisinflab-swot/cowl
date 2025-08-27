===============================
Querying and editing ontologies
===============================

.. contents:: :local:

The ontology object
===================

Once a :struct:`CowlOntology` object has been read into memory, it can be queried and edited
to retrieve, add, or remove axioms, annotations, and other constructs.

.. doxygenstruct:: CowlOntology
.. doxygengroup:: CowlOntology
   :content-only:

.. _querying:

Querying ontologies
===================

The base mechanism for querying a :struct:`CowlOntology` and other constructs is invoking
their iterator member functions, which generally accept :struct:`CowlIterator` instances.

:struct:`CowlIterator` is a wrapper around a function that is called for every element matched
by the query. By providing a generic context pointer, you can plug any custom data structure
(loggers, collections, etc.), which allows for arbitrarily complex programmatic queries.
Iteration can be stopped at any time, enabling early termination for queries such as
finding the first construct that matches some condition.

.. doxygengroup:: CowlIterator_types
   :content-only:
.. doxygengroup:: CowlIterator_api
   :content-only:

.. doxygengroup:: CowlAxiomFlags_type
   :content-only:
.. doxygengroup:: CowlAxiomFlags_api
   :content-only:

.. doxygenstruct:: CowlAxiomFilter
.. doxygengroup:: CowlAxiomFilter
   :content-only:

.. _editing:

Editing ontologies
==================

Ontologies can be edited by adding or removing axioms, annotations and other constructs,
as allowed by the :struct:`CowlOntology` API. They can also be created from scratch
via the :func:`cowl_ontology()` constructor.

Access to the mappings between prefixed and full IRIs is pro is provided by a
:struct:`CowlPrefixMap` instance, retrievable by calling :func:`cowl_ontology_get_prefix_map()`.

.. doxygenstruct:: CowlPrefixMap
.. doxygengroup:: CowlPrefixMap
   :content-only:
