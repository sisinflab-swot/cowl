/**
 * Declares CowlOntology and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_H
#define COWL_ONTOLOGY_H

#include "cowl_axiom_flags.h"
#include "cowl_axiom_type.h"
#include "cowl_iterator.h"
#include "cowl_object.h"
#include "cowl_ontology_id.h"
#include "cowl_position.h"
#include "cowl_ret.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAxiomFilter);
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlManager);
cowl_struct_decl(CowlSymTable);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents an [Ontology] in the OWL 2 specification.
 *
 * [Ontology]: https://www.w3.org/TR/owl2-syntax/#Ontologies
 *
 * @superstruct{CowlObject}
 * @struct CowlOntology
 */
cowl_struct_decl(CowlOntology);

/**
 * @defgroup CowlOntology CowlOntology API
 * @{
 */

/**
 * Gets the manager of this ontology.
 *
 * @param onto The ontology.
 * @return The manager.
 */
COWL_API
COWL_PURE
CowlManager *cowl_ontology_get_manager(CowlOntology *onto);

/**
 * Gets the symbol table of this ontology.
 *
 * @param onto The ontology.
 * @return The symbol table.
 */
COWL_API
COWL_PURE
CowlSymTable *cowl_ontology_get_sym_table(CowlOntology *onto);

/**
 * Gets the ontology ID.
 *
 * @param onto The ontology.
 * @return The ontology ID.
 */
COWL_API
COWL_PURE
CowlOntologyId cowl_ontology_get_id(CowlOntology *onto);

/**
 * Sets the IRI of the ontology.
 *
 * @param onto The ontology.
 * @param iri The IRI.
 */
COWL_API
void cowl_ontology_set_iri(CowlOntology *onto, CowlIRI *iri);

/**
 * Sets the version IRI of the ontology.
 *
 * @param onto The ontology.
 * @param version The version IRI.
 */
COWL_API
void cowl_ontology_set_version(CowlOntology *onto, CowlIRI *version);

/**
 * Gets the annotations of the specified ontology.
 *
 * @param onto The ontology.
 * @return The annotations.
 */
COWL_API
COWL_PURE
CowlVector *cowl_ontology_get_annot(CowlOntology *onto);

/**
 * Adds an annotation to the ontology.
 *
 * @param onto The ontology.
 * @param annot The annotation.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ontology_add_annot(CowlOntology *onto, CowlAnnotation *annot);

/**
 * Removes an annotation from the ontology.
 *
 * @param onto The ontology.
 * @param annot The annotation.
 * @return True if the annotation was removed (it was found), false otherwise.
 */
COWL_API
bool cowl_ontology_remove_annot(CowlOntology *onto, CowlAnnotation *annot);

/**
 * Gets an imported ontology given its import IRI.
 *
 * @param onto The ontology.
 * @param iri Import IRI.
 * @return Imported ontology.
 */
COWL_API
COWL_PURE
CowlOntology *cowl_ontology_get_import(CowlOntology *onto, CowlIRI *iri);

/**
 * Gets the import IRI of an imported ontology.
 *
 * @param onto The ontology.
 * @param import The imported ontology.
 * @return Import IRI.
 */
COWL_API
COWL_PURE
CowlIRI *cowl_ontology_get_import_iri(CowlOntology *onto, CowlOntology *import);

/**
 * Adds an import to the ontology.
 *
 * @param onto The ontology.
 * @param import IRI of the imported ontology.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ontology_add_import(CowlOntology *onto, CowlIRI *import);

/**
 * Removes an import from the ontology.
 *
 * @param onto The ontology.
 * @param import IRI of the imported ontology.
 * @return True if the import was removed (it was found), false otherwise.
 */
COWL_API
bool cowl_ontology_remove_import(CowlOntology *onto, CowlIRI *import);

/**
 * Adds an axiom to the ontology.
 *
 * @param onto The ontology.
 * @param axiom The axiom.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ontology_add_axiom(CowlOntology *onto, CowlAnyAxiom *axiom);

/**
 * Removes an axiom from the ontology.
 *
 * @param onto The ontology.
 * @param axiom The axiom.
 * @return True if the axiom was removed (it was found), false otherwise.
 */
COWL_API
bool cowl_ontology_remove_axiom(CowlOntology *onto, CowlAnyAxiom *axiom);

/**
 * Removes the axioms matching the provided filter function.
 *
 * @param onto The ontology.
 * @param filter The filter.
 * @return Number of removed axioms.
 *
 * @note The filter must not be used anymore after calling this function.
 */
COWL_API
ulib_uint cowl_ontology_remove_axioms_matching(CowlOntology *onto, CowlAxiomFilter *filter);

/**
 * Gets the number of axioms in the ontology.
 *
 * @param onto The ontology.
 * @param imports If true, the query recurses over imported ontologies.
 * @return Number of axioms.
 */
COWL_API
COWL_PURE
ulib_uint cowl_ontology_axiom_count(CowlOntology *onto, bool imports);

/**
 * Gets the number of imported ontologies.
 *
 * @param onto The ontology.
 * @param imports If true, the query recurses over imported ontologies.
 * @return Number of imports.
 */
COWL_API
COWL_PURE
ulib_uint cowl_ontology_imports_count(CowlOntology *onto, bool imports);

/**
 * Gets the number of axioms of the specified type.
 *
 * @param onto The ontology.
 * @param type The axiom type.
 * @param imports If true, the query recurses over imported ontologies.
 * @return Number of axioms.
 */
COWL_API
COWL_PURE
ulib_uint cowl_ontology_axiom_count_for_type(CowlOntology *onto, CowlAxiomType type, bool imports);

/**
 * Gets the number of axioms of the specified types.
 *
 * @param onto The ontology.
 * @param types The axiom types.
 * @param imports If true, the query recurses over imported ontologies.
 * @return Number of axioms.
 */
COWL_API
COWL_PURE
ulib_uint
cowl_ontology_axiom_count_for_types(CowlOntology *onto, CowlAxiomFlags types, bool imports);

/**
 * Gets the number of axioms referencing the specified primitive.
 *
 * @param onto The ontology.
 * @param primitive The primitive.
 * @param imports If true, the query recurses over imported ontologies.
 * @return Number of axioms.
 */
COWL_API
COWL_PURE
ulib_uint cowl_ontology_axiom_count_for_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive,
                                                  bool imports);

/**
 * Gets the number of primitives.
 *
 * @param onto The ontology.
 * @param flags Primitive flags.
 * @param imports If true, the query recurses over imported ontologies.
 * @return Number of primitives.
 */
COWL_API
COWL_PURE
ulib_uint
cowl_ontology_primitives_count(CowlOntology *onto, CowlPrimitiveFlags flags, bool imports);

/**
 * Checks if the specified primitive is referenced by an axiom in the ontology.
 *
 * @param onto The ontology.
 * @param primitive The primitive.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the primitive is referenced by an axiom, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_ontology_has_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive, bool imports);

/**
 * Checks whether the ontology contains the specified axiom.
 *
 * @param onto The ontology.
 * @param axiom The axiom.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the ontology contains the axiom, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_ontology_has_axiom(CowlOntology *onto, CowlAnyAxiom *axiom, bool imports);

/**
 * Iterates over the primitives referenced by the specified ontology.
 *
 * @param onto The ontology.
 * @param flags Primitive flags.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_API
bool cowl_ontology_iterate_primitives(CowlOntology *onto, CowlPrimitiveFlags flags,
                                      CowlIterator *iter, bool imports);

/**
 * Iterates over the imported ontologies.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_API
bool cowl_ontology_iterate_imports(CowlOntology *onto, CowlIterator *iter, bool imports);

/**
 * Iterates over the import IRIs.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_API
bool cowl_ontology_iterate_import_iris(CowlOntology *onto, CowlIterator *iter, bool imports);

/**
 * Iterates over the axioms in the ontology.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_API
bool cowl_ontology_iterate_axioms(CowlOntology *onto, CowlIterator *iter, bool imports);

/**
 * Iterates over the axioms of a certain type.
 *
 * @param onto The ontology.
 * @param type The axiom type.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_API
bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          CowlIterator *iter, bool imports);

/**
 * Iterates over the axiom of some types.
 *
 * @param onto The ontology.
 * @param types The axiom types.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_API
bool cowl_ontology_iterate_axioms_of_types(CowlOntology *onto, CowlAxiomFlags types,
                                           CowlIterator *iter, bool imports);

/**
 * Iterates over the axioms referencing the specified primitive.
 *
 * @param onto The ontology.
 * @param primitive The primitive.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_API
bool cowl_ontology_iterate_axioms_for_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive,
                                                CowlIterator *iter, bool imports);

/**
 * Iterates over the axioms matching the specified filter.
 *
 * @param onto The ontology.
 * @param filter The filter.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @note The filter must not be used anymore after calling this function.
 */
COWL_API
bool cowl_ontology_iterate_axioms_matching(CowlOntology *onto, CowlAxiomFilter *filter,
                                           CowlIterator *iter, bool imports);

/**
 * Iterates over the constructs that are related to the specified primitive by some axiom.
 *
 * @param onto The ontology.
 * @param primitive The primitive.
 * @param type Axiom type.
 * @param position Position of the related constructs.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_API
bool cowl_ontology_iterate_related(CowlOntology *onto, CowlAnyPrimitive *primitive,
                                   CowlAxiomType type, CowlPosition position, CowlIterator *iter,
                                   bool imports);

/**
 * Iterates over the subclasses of the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_INLINE
bool cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class, CowlIterator *iter,
                                       bool imports) {
    return cowl_ontology_iterate_related(onto, owl_class, COWL_AT_SUB_CLASS, COWL_PS_LEFT, iter,
                                         imports);
}

/**
 * Iterates over the superclasses of the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_INLINE
bool cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         CowlIterator *iter, bool imports) {
    return cowl_ontology_iterate_related(onto, owl_class, COWL_AT_SUB_CLASS, COWL_PS_RIGHT, iter,
                                         imports);
}

/**
 * Iterates over the equivalent classes of the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_INLINE
bool cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class, CowlIterator *iter,
                                      bool imports) {
    return cowl_ontology_iterate_related(onto, owl_class, COWL_AT_EQUIV_CLASSES, COWL_PS_ANY, iter,
                                         imports);
}

/**
 * Iterates over the disjoint classes of the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_INLINE
bool cowl_ontology_iterate_disjoint_classes(CowlOntology *onto, CowlClass *owl_class,
                                            CowlIterator *iter, bool imports) {
    return cowl_ontology_iterate_related(onto, owl_class, COWL_AT_DISJ_CLASSES, COWL_PS_ANY, iter,
                                         imports);
}

/**
 * Iterates over the types of the specified individual.
 *
 * @param onto The ontology.
 * @param ind The individual.
 * @param iter The iterator.
 * @param imports If true, the query recurses over imported ontologies.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_INLINE
bool cowl_ontology_iterate_types(CowlOntology *onto, CowlAnyIndividual *ind, CowlIterator *iter,
                                 bool imports) {
    return cowl_ontology_iterate_related(onto, ind, COWL_AT_CLASS_ASSERT, COWL_PS_LEFT, iter,
                                         imports);
}

/// @}

COWL_END_DECLS

#endif // COWL_ONTOLOGY_H
