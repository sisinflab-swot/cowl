=======================
Entities and Primitives
=======================

*Entities* represent the named terms of OWL ontologies, and are modeled by :class:`CowlEntity`.
*Primitives* are a superset of entities, which also include anonymous individuals. They are modeled
by :class:`CowlPrimitive`.

.. doxygenstruct:: CowlEntity
.. doxygenenum:: CowlEntityType

.. doxygenstruct:: CowlPrimitive
.. doxygenenum:: CowlPrimitiveType

.. toctree::
   :caption: Types

   CowlClass
   CowlDatatype

.. toctree::
   :caption: Properties

   CowlObjProp
   CowlDataProp
   CowlAnnotProp

.. toctree::
   :caption: Individuals

   ../ind/CowlIndividual
