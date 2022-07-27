/**
 * Declares CowlOntology and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_H
#define COWL_ONTOLOGY_H

#include "cowl_axiom_type.h"
#include "cowl_iterator.h"
#include "cowl_object.h"
#include "cowl_ontology_id.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlAnonInd);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataProp);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlEntity);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlNamedInd);
cowl_struct_decl(CowlObjProp);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlOntology);
/// @endcond

/**
 * Represents an [Ontology] in the OWL 2 specification.
 *
 * [Ontology]: https://www.w3.org/TR/owl2-syntax/#Ontologies
 *
 * @struct CowlOntology
 */

/**
 * Retains the specified ontology.
 *
 * @param onto The ontology.
 * @return Retained ontology.
 *
 * @public @memberof CowlOntology
 */
COWL_INLINE
CowlOntology* cowl_ontology_retain(CowlOntology *onto) {
    return (CowlOntology *)cowl_retain(onto);
}

/**
 * Releases the specified ontology.
 *
 * @param onto The ontology.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
void cowl_ontology_release(CowlOntology *onto);

/**
 * Gets the ontology ID.
 *
 * @param onto The ontology.
 * @return The ontology ID.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
CowlOntologyId cowl_ontology_get_id(CowlOntology *onto);

/**
 * Gets the annotations of the specified ontology.
 *
 * @param onto The ontology.
 * @return The annotations.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
CowlVector* cowl_ontology_get_annot(CowlOntology *onto);

/**
 * Returns the string representation of the specified ontology.
 *
 * @param onto The ontology.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlOntology
 */
COWL_INLINE
CowlString* cowl_ontology_to_string(CowlOntology *onto) {
    return cowl_to_string(onto);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @note Two ontologies are considered equal if their ontology IDs are equal.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_equals(CowlOntology *lhs, CowlOntology *rhs);

/**
 * Hash function.
 *
 * @param onto The ontology.
 * @return The hash value.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_hash(CowlOntology *onto);

/**
 * Gets the number of axioms in the ontology.
 *
 * @param onto The ontology.
 * @return Number of axioms.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_axiom_count(CowlOntology *onto);

/**
 * Gets the number of imported ontologies.
 *
 * @param onto The ontology.
 * @return Number of imports.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_imports_count(CowlOntology *onto);

/**
 * Gets the number of axioms of the specified type.
 *
 * @param onto The ontology.
 * @param type The axiom type.
 * @return Number of axioms.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_axiom_count_for_type(CowlOntology *onto, CowlAxiomType type);

/**
 * Gets the number of axioms referencing the specified primitive.
 *
 * @param onto The ontology.
 * @param primitive The primitive.
 * @return Number of axioms.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_axiom_count_for_primitive(CowlOntology *onto, void *primitive);

/**
 * Gets the number of primitives.
 *
 * @param onto The ontology.
 * @param flags Iteration flags.
 * @return Number of primitives.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_primitives_count(CowlOntology *onto, CowlPrimitiveFlags flags);

/**
 * Checks if the specified primitive is referenced by an axiom in the ontology.
 *
 * @param onto The ontology.
 * @param primitive The primitive.
 * @return True if the primitive is referenced by an axiom, false otherwise.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_has_primitive(CowlOntology *onto, void *primitive);

/**
 * Iterates over the primitives referenced by the specified ontology.
 *
 * @param onto The ontology.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_primitives(CowlOntology *onto, CowlPrimitiveFlags flags,
                                      CowlIterator *iter);

/**
 * Iterates over the imported ontologies.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_imports(CowlOntology *onto, CowlIterator *iter);

/**
 * Iterates over the axioms in the ontology.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms(CowlOntology *onto, CowlIterator *iter);

/**
 * Iterates over the axioms of a certain type.
 *
 * @param onto The ontology.
 * @param type The axiom type.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          CowlIterator *iter);

/**
 * Iterates over the axioms referencing the specified primitive.
 *
 * @param onto The ontology.
 * @param primitive The primitive.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_primitive(CowlOntology *onto, void *primitive,
                                                CowlIterator *iter);

/**
 * Iterates over the subclasses of the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class,
                                       CowlIterator *iter);

/**
 * Iterates over the superclasses of the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         CowlIterator *iter);

/**
 * Iterates over the equivalent classes of the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class,
                                      CowlIterator *iter);

/**
 * Iterates over the disjoint classes of the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_disjoint_classes(CowlOntology *onto, CowlClass *owl_class,
                                            CowlIterator *iter);

/**
 * Iterates over the types of the specified individual.
 *
 * @param onto The ontology.
 * @param ind The individual.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_types(CowlOntology *onto, CowlIndividual *ind, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_H
