=======================
Entities and primitives
=======================

*Entities* represent the named terms of OWL ontologies, such as classes, datatypes, and properties,
and are modeled by :struct:`CowlEntity`. The term *primitive* has no correspondence in the
OWL 2 specification. It is used as a collective term for entities, anonymous individuals,
and IRIs, which are modeled by :struct:`CowlPrimitive`. You can always safely cast
:struct:`CowlEntity` to :struct:`CowlPrimitive`, while the opposite can only be done
after checking that the primitive is an OWL entity (see :func:`cowl_is_entity()`).

.. doxygenstruct:: CowlEntity
.. doxygenenum:: CowlEntityType
.. doxygengroup:: CowlEntity
   :content-only:

.. doxygenstruct:: CowlPrimitive
.. doxygenenum:: CowlPrimitiveType
.. doxygengroup:: CowlPrimitive
   :content-only:

.. toctree::
   :caption: Subtypes

   class
   datatype
   obj_prop
   data_prop
   annot_prop
   individual
   iri
