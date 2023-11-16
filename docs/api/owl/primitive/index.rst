=======================
Entities and Primitives
=======================

*Entities* represent the named terms of OWL ontologies, and are modeled by :class:`CowlEntity`.
The term *primitive* has no correspondence in the OWL 2 specification.
It is used as a collective term for entities, anonymous individuals, and IRIs,
which are modeled by :class:`CowlPrimitive`. You can always safely cast :class:`CowlEntity`
to :class:`CowlPrimitive`, while the opposite can only be done after checking that the primitive
is an OWL entity (see :func:`CowlObject::cowl_is_entity()`).

.. doxygenstruct:: CowlEntity
.. doxygenenum:: CowlEntityType

.. doxygenstruct:: CowlPrimitive
.. doxygenenum:: CowlPrimitiveType

.. toctree::
   :caption: Primitive types

   CowlClass
   CowlDatatype
   CowlObjProp
   CowlDataProp
   CowlAnnotProp
   ../ind/CowlIndividual
   ../../base/CowlIRI
