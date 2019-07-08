/**
 * Declares CowlOntology and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_H
#define COWL_ONTOLOGY_H

#include "cowl_axiom_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAnonInd);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataProp);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlNamedInd);
cowl_struct_decl(CowlObjProp);
cowl_struct_decl(CowlOntologyID);
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
COWL_PUBLIC
CowlOntology* cowl_ontology_retain(CowlOntology *onto);

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
CowlOntologyID* cowl_ontology_get_id(CowlOntology *onto);

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
cowl_uint_t cowl_ontology_hash(CowlOntology *onto);

/**
 * Gets the number of axioms in the ontology.
 *
 * @param onto The ontology.
 * @return Number of axioms.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
cowl_uint_t cowl_ontology_axiom_count(CowlOntology *onto);

/**
 * Gets the number of imported ontologies.
 *
 * @param onto The ontology.
 * @return Number of imports.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
cowl_uint_t cowl_ontology_imports_count(CowlOntology *onto);

/**
 * Gets the number of axioms referencing the specified annotation property.
 *
 * @param onto The ontology.
 * @param prop The annotation property.
 * @return Number of axioms.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
cowl_uint_t cowl_ontology_axiom_count_for_annot_prop(CowlOntology *onto, CowlAnnotProp *prop);

/**
 * Gets the number of axioms referencing the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @return Number of axioms.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
cowl_uint_t cowl_ontology_axiom_count_for_class(CowlOntology *onto, CowlClass *owl_class);

/**
 * Gets the number of axioms referencing the specified data property.
 *
 * @param onto The ontology.
 * @param prop The data property.
 * @return Number of axioms.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
cowl_uint_t cowl_ontology_axiom_count_for_data_prop(CowlOntology *onto, CowlDataProp *prop);

/**
 * Gets the number of axioms referencing the specified datatype.
 *
 * @param onto The ontology.
 * @param datatype The datatype.
 * @return Number of axioms.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
cowl_uint_t cowl_ontology_axiom_count_for_datatype(CowlOntology *onto, CowlDatatype *datatype);

/**
 * Gets the number of axioms referencing the specified object property.
 *
 * @param onto The ontology.
 * @param prop The object property.
 * @return Number of axioms.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
cowl_uint_t cowl_ontology_axiom_count_for_obj_prop(CowlOntology *onto, CowlObjProp *prop);

/**
 * Gets the number of axioms referencing the specified named individual.
 *
 * @param onto The ontology.
 * @param ind The individual.
 * @return Number of axioms.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
cowl_uint_t cowl_ontology_axiom_count_for_named_ind(CowlOntology *onto, CowlNamedInd *ind);

/**
 * Iterates over the signature of the specified ontology.
 *
 * @param onto The ontology.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_signature(CowlOntology *onto, CowlEntityIterator *iter);

/**
 * Iterates over the imported ontologies.
 *
 * @param onto The ontology.
 * @param iter The ontology iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_imports(CowlOntology *onto, CowlOntologyIterator *iter);

/**
 * Iterates over the classes in the ontology.
 *
 * @param onto The ontology.
 * @param iter The class iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_classes(CowlOntology *onto, CowlClassIterator *iter);

/**
 * Iterates over the data properties in the ontology.
 *
 * @param onto The ontology.
 * @param iter The data property iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_data_props(CowlOntology *onto, CowlDataPropIterator *iter);

/**
 * Iterates over the datatypes in the ontology.
 *
 * @param onto The ontology.
 * @param iter The datatype iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_datatypes(CowlOntology *onto, CowlDatatypeIterator *iter);

/**
 * Iterates over the object properties in the ontology.
 * @param onto The ontology.
 * @param iter The object property iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_obj_props(CowlOntology *onto, CowlObjPropIterator *iter);

/**
 * Iterates over the annotation properties in the ontology.
 *
 * @param onto The ontology.
 * @param iter The annotation property iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_annot_props(CowlOntology *onto, CowlAnnotPropIterator *iter);

/**
 * Iterates over the named individuals in the ontology.
 *
 * @param onto The ontology.
 * @param iter The named individual iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_named_inds(CowlOntology *onto, CowlNamedIndIterator *iter);

/**
 * Iterates over the anonymous individuals in the ontology.
 *
 * @param onto The ontology.
 * @param iter The anonymous individual iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_anon_inds(CowlOntology *onto, CowlAnonIndIterator *iter);

/**
 * Iterates over the axioms in the ontology.
 *
 * @param onto The ontology.
 * @param iter The axiom iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms(CowlOntology *onto, CowlAxiomIterator *iter);

/**
 * Iterates over the axioms of a certain type.
 *
 * @param onto The ontology.
 * @param type The axiom type.
 * @param iter The axiom iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          CowlAxiomIterator *iter);

/**
 * Iterates over the axioms referencing the specified annotation property.
 *
 * @param onto The ontology.
 * @param prop The annotation property.
 * @param iter The axiom iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_annot_prop(CowlOntology *onto, CowlAnnotProp *prop,
                                                 CowlAxiomIterator *iter);

/**
 * Iterates over the axioms referencing the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The axiom iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_class(CowlOntology *onto, CowlClass *owl_class,
                                            CowlAxiomIterator *iter);

/**
 * Iterates over the axioms referencing the specified data property.
 *
 * @param onto The ontology.
 * @param prop The data property.
 * @param iter The axiom iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_data_prop(CowlOntology *onto, CowlDataProp *prop,
                                                CowlAxiomIterator *iter);

/**
 * Iterates over the axioms referencing the specified datatype.
 *
 * @param onto The ontology.
 * @param datatype The datatype.
 * @param iter The axiom iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_datatype(CowlOntology *onto, CowlDatatype *datatype,
                                               CowlAxiomIterator *iter);

/**
 * Iterates over the axioms referencing the specified object property.
 *
 * @param onto The ontology.
 * @param prop The object property.
 * @param iter The axiom iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_obj_prop(CowlOntology *onto, CowlObjProp *prop,
                                               CowlAxiomIterator *iter);

/**
 * Iterates over the axioms referencing the specified named individual.
 *
 * @param onto The ontology.
 * @param ind The named individual.
 * @param iter The axiom iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_named_ind(CowlOntology *onto, CowlNamedInd *ind,
                                                CowlAxiomIterator *iter);

/**
 * Iterates over the axioms referencing the specified anonymous individual.
 *
 * @param onto The ontology.
 * @param ind The anonymous individual.
 * @param iter The axiom iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_anon_ind(CowlOntology *onto, CowlAnonInd *ind,
                                               CowlAxiomIterator *iter);

/**
 * Iterates over the subclasses of the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The class expression iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class,
                                       CowlClsExpIterator *iter);

/**
 * Iterates over the superclasses of the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The class expression iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         CowlClsExpIterator *iter);

/**
 * Iterates over the equivalent classes of the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The class expression iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class,
                                      CowlClsExpIterator *iter);

/**
 * Iterates over the disjoint classes of the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The class expression iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_disjoint_classes(CowlOntology *onto, CowlClass *owl_class,
                                            CowlClsExpIterator *iter);

/**
 * Iterates over the types of the specified individual.
 *
 * @param onto The ontology.
 * @param ind The individual.
 * @param iter The class expression iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_types(CowlOntology *onto, CowlIndividual *ind, CowlClsExpIterator *iter);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_H
