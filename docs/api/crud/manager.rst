====================
The ontology manager
====================

Ontology reading and writing functionality is exposed via the :struct:`CowlManager` API.
A :struct:`CowlManager` instance manages one or more ontology documents, and allows reading
and writing ontologies from/to files, memory buffers, or byte streams. Its architecture allows
for multiple :ref:`readers <reading>` and :ref:`writers <writing>`,
either built-in or provided by the user.

:struct:`CowlManager` objects form a hierarchical structure, with a single root manager
accessible via :func:`cowl_manager()`. Child managers can be created using
:func:`cowl_manager_new_child()`, establishing a parent-child relationship.

This hierarchy is leveraged for managing resources such as :ref:`error handlers <error>`,
:ref:`readers <reading>`, :ref:`writers <writing>`, and :struct:`ontologies <CowlOntology>`.
When a resource or object is requested from a :struct:`CowlManager` instance and is not
explicitly set or available in that instance, the manager hierarchy is traversed upwards,
searching each ancestor until the resource is found or the root manager is reached.

.. doxygenstruct:: CowlManager
.. doxygengroup:: CowlManager
   :content-only:
