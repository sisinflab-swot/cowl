/**
 * Declares CowlOntology and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_H
#define COWL_ONTOLOGY_H

#include "cowl_axiom_type.h"
#include "cowl_iterator.h"
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
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
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
CowlObjectVec* cowl_ontology_get_annot(CowlOntology *onto);

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
COWL_PUBLIC
CowlString* cowl_ontology_to_string(CowlOntology *onto);

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
 */
COWL_PUBLIC
ulib_uint cowl_ontology_axiom_count_for_type(CowlOntology *onto, CowlAxiomType type);

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
ulib_uint cowl_ontology_axiom_count_for_annot_prop(CowlOntology *onto, CowlAnnotProp *prop);

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
ulib_uint cowl_ontology_axiom_count_for_class(CowlOntology *onto, CowlClass *owl_class);

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
ulib_uint cowl_ontology_axiom_count_for_data_prop(CowlOntology *onto, CowlDataProp *prop);

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
ulib_uint cowl_ontology_axiom_count_for_datatype(CowlOntology *onto, CowlDatatype *datatype);

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
ulib_uint cowl_ontology_axiom_count_for_obj_prop(CowlOntology *onto, CowlObjProp *prop);

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
ulib_uint cowl_ontology_axiom_count_for_named_ind(CowlOntology *onto, CowlNamedInd *ind);

/**
 * Gets the number of axioms referencing the specified anonymous individual.
 *
 * @param onto The ontology.
 * @param ind The individual.
 * @return Number of axioms.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_axiom_count_for_anon_ind(CowlOntology *onto, CowlAnonInd *ind);

/**
 * Gets the number of classes.
 *
 * @param onto The ontology.
 * @return Number of classes.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_classes_count(CowlOntology *onto);

/**
 * Gets the number of datatypes.
 *
 * @param onto The ontology.
 * @return Number of datatypes.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_datatypes_count(CowlOntology *onto);

/**
 * Gets the number of object properties.
 *
 * @param onto The ontology.
 * @return Number of object properties.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_obj_props_count(CowlOntology *onto);

/**
 * Gets the number of data properties.
 *
 * @param onto The ontology.
 * @return Number of data properties.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_data_props_count(CowlOntology *onto);

/**
 * Gets the number of annotation properties.
 *
 * @param onto The ontology.
 * @return Number of annotation properties.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_annot_props_count(CowlOntology *onto);

/**
 * Gets the number of named individuals.
 *
 * @param onto The ontology.
 * @return Number of named individuals.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_named_inds_count(CowlOntology *onto);

/**
 * Gets the number of anonymous individuals.
 *
 * @param onto The ontology.
 * @return Number of anonymous individuals.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
ulib_uint cowl_ontology_anon_inds_count(CowlOntology *onto);

/**
 * Checks if the specified entity is referenced by an axiom in the ontology.
 *
 * @param onto The ontology.
 * @param entity The entity.
 * @return True if the entity is referenced by an axiom, false otherwise.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_has_entity(CowlOntology *onto, CowlEntity *entity);

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
 * Iterates over the classes in the ontology.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_classes(CowlOntology *onto, CowlIterator *iter);

/**
 * Iterates over the data properties in the ontology.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_data_props(CowlOntology *onto, CowlIterator *iter);

/**
 * Iterates over the datatypes in the ontology.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_datatypes(CowlOntology *onto, CowlIterator *iter);

/**
 * Iterates over the object properties in the ontology.
 * @param onto The ontology.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_obj_props(CowlOntology *onto, CowlIterator *iter);

/**
 * Iterates over the annotation properties in the ontology.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_annot_props(CowlOntology *onto, CowlIterator *iter);

/**
 * Iterates over the named individuals in the ontology.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_named_inds(CowlOntology *onto, CowlIterator *iter);

/**
 * Iterates over the anonymous individuals in the ontology.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_anon_inds(CowlOntology *onto, CowlIterator *iter);

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
 * Iterates over the axioms referencing the specified annotation property.
 *
 * @param onto The ontology.
 * @param prop The annotation property.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_annot_prop(CowlOntology *onto, CowlAnnotProp *prop,
                                                 CowlIterator *iter);

/**
 * Iterates over the axioms referencing the specified class.
 *
 * @param onto The ontology.
 * @param owl_class The class.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_class(CowlOntology *onto, CowlClass *owl_class,
                                            CowlIterator *iter);

/**
 * Iterates over the axioms referencing the specified data property.
 *
 * @param onto The ontology.
 * @param prop The data property.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_data_prop(CowlOntology *onto, CowlDataProp *prop,
                                                CowlIterator *iter);

/**
 * Iterates over the axioms referencing the specified datatype.
 *
 * @param onto The ontology.
 * @param datatype The datatype.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_datatype(CowlOntology *onto, CowlDatatype *datatype,
                                               CowlIterator *iter);

/**
 * Iterates over the axioms referencing the specified object property.
 *
 * @param onto The ontology.
 * @param prop The object property.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_obj_prop(CowlOntology *onto, CowlObjProp *prop,
                                               CowlIterator *iter);

/**
 * Iterates over the axioms referencing the specified named individual.
 *
 * @param onto The ontology.
 * @param ind The named individual.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_named_ind(CowlOntology *onto, CowlNamedInd *ind,
                                                CowlIterator *iter);

/**
 * Iterates over the axioms referencing the specified anonymous individual.
 *
 * @param onto The ontology.
 * @param ind The anonymous individual.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlOntology
 */
COWL_PUBLIC
bool cowl_ontology_iterate_axioms_for_anon_ind(CowlOntology *onto, CowlAnonInd *ind,
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
