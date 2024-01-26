====================
The ontology manager
====================

Ontology reading and writing functionality is exposed via the :struct:`CowlManager` API.
A :struct:`CowlManager` instance manages one or more ontology documents, and allows reading
and writing ontologies from/to files, memory buffers, or byte streams. Its architecture allows
for multiple :ref:`readers <reading>` and :ref:`writers <writing>`,
either built-in or provided by the user.

.. doxygenstruct:: CowlManager
.. doxygengroup:: CowlManager
   :content-only:
