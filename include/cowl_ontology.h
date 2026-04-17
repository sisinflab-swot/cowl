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

#include "cowl_any.h"
#include "cowl_attrs.h"
#include "cowl_axiom_flags.h"
#include "cowl_axiom_type.h"
#include "cowl_iterator.h"
#include "cowl_position.h"
#include "cowl_primitive_flags.h"
#include "cowl_ret.h"
#include "cowl_utils.h"
#include "ulib.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAxiomFilter);
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlPrefixMap);
cowl_struct_decl(CowlReader);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlWriter);
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
 * Creates a new ontology.
 *
 * @return Ontology, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlOntology *cowl_ontology(void);

/**
 * Reads an ontology from the specified file path.
 *
 * @param path File path.
 * @return Ontology, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlOntology *cowl_ontology_at_path(UString path);

/**
 * Reads an ontology from the specified input stream.
 *
 * @param stream Input stream.
 * @return CowlOntology object, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlOntology *cowl_ontology_from_stream(UIStream *stream);

/**
 * Writes the specified ontology to the given file path.
 *
 * @param onto The ontology.
 * @param path File path.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ontology_to_path(CowlOntology *onto, UString path);

/**
 * Writes the specified ontology to the given output stream.
 *
 * @param onto The ontology.
 * @param stream Output stream.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ontology_to_stream(CowlOntology *onto, UOStream *stream);

/**
 * Gets the prefix map of this ontology.
 *
 * @param onto The ontology.
 * @return The prefix map, or NULL on error.
 */
COWL_API
COWL_PURE
CowlPrefixMap *cowl_ontology_get_prefix_map(CowlOntology *onto);

/**
 * Gets the IRI of the ontology.
 *
 * @param onto The ontology.
 * @return The ontology IRI.
 */
COWL_API
COWL_PURE
CowlIRI *cowl_ontology_get_iri(CowlOntology *onto);

/**
 * Sets the IRI of the ontology.
 *
 * @param onto The ontology.
 * @param iri The IRI.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ontology_set_iri(CowlOntology *onto, CowlIRI *iri);

/**
 * Gets the version of the ontology.
 *
 * @param onto The ontology.
 * @return The version IRI.
 */
COWL_API
COWL_PURE
CowlIRI *cowl_ontology_get_version(CowlOntology *onto);

/**
 * Sets the version IRI of the ontology.
 *
 * @param onto The ontology.
 * @param version The version IRI.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ontology_set_version(CowlOntology *onto, CowlIRI *version);

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
 * Checks if the given ontology has an import with the specified IRI.
 *
 * @param onto The ontology.
 * @param import IRI of the imported ontology.
 * @return True if the ontology has the specified import, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_ontology_has_import(CowlOntology *onto, CowlIRI *import);

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
 * @return Number of axioms.
 */
COWL_API
COWL_PURE
ulib_uint cowl_ontology_axiom_count(CowlOntology *onto);

/**
 * Gets the number of imported ontologies.
 *
 * @param onto The ontology.
 * @return Number of imports.
 */
COWL_API
COWL_PURE
ulib_uint cowl_ontology_imports_count(CowlOntology *onto);

/**
 * Gets the number of axioms of the specified type.
 *
 * @param onto The ontology.
 * @param type The axiom type.
 * @return Number of axioms.
 */
COWL_API
COWL_PURE
ulib_uint cowl_ontology_axiom_count_for_type(CowlOntology *onto, CowlAxiomType type);

/**
 * Gets the number of axioms of the specified types.
 *
 * @param onto The ontology.
 * @param types The axiom types.
 * @return Number of axioms.
 */
COWL_API
COWL_PURE
ulib_uint cowl_ontology_axiom_count_for_types(CowlOntology *onto, CowlAxiomFlags types);

/**
 * Gets the number of axioms referencing the specified primitive.
 *
 * @param onto The ontology.
 * @param primitive The primitive.
 * @return Number of axioms.
 */
COWL_API
COWL_PURE
ulib_uint cowl_ontology_axiom_count_for_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive);

/**
 * Gets the number of primitives.
 *
 * @param onto The ontology.
 * @param flags Primitive flags.
 * @return Number of primitives.
 */
COWL_API
COWL_PURE
ulib_uint cowl_ontology_primitives_count(CowlOntology *onto, CowlPrimitiveFlags flags);

/**
 * Checks if the specified primitive is referenced by an axiom in the ontology.
 *
 * @param onto The ontology.
 * @param primitive The primitive.
 * @return True if the primitive is referenced by an axiom, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_ontology_has_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive);

/**
 * Checks whether the ontology contains the specified axiom.
 *
 * @param onto The ontology.
 * @param axiom The axiom.
 * @return True if the ontology contains the axiom, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_ontology_has_axiom(CowlOntology *onto, CowlAnyAxiom *axiom);

/**
 * Iterates over the annotations of the ontology.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ontology_iterate_annot(CowlOntology *onto, CowlIterator *iter);

/**
 * Iterates over the import IRIs.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ontology_iterate_imports(CowlOntology *onto, CowlIterator *iter);

/**
 * Iterates over the primitives referenced by the specified ontology.
 *
 * @param onto The ontology.
 * @param flags Primitive flags.
 * @param iter The iterator.
 * @return Return code.
 */
COWL_API
cowl_ret
cowl_ontology_iterate_primitives(CowlOntology *onto, CowlPrimitiveFlags flags, CowlIterator *iter);

/**
 * Iterates over the axioms in the ontology.
 *
 * @param onto The ontology.
 * @param iter The iterator.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ontology_iterate_axioms(CowlOntology *onto, CowlIterator *iter);

/**
 * Iterates over the axioms of a certain type.
 *
 * @param onto The ontology.
 * @param type The axiom type.
 * @param iter The iterator.
 * @return Return code.
 */
COWL_API
cowl_ret
cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type, CowlIterator *iter);

/**
 * Iterates over the axiom of some types.
 *
 * @param onto The ontology.
 * @param types The axiom types.
 * @param iter The iterator.
 * @return Return code.
 */
COWL_API
cowl_ret
cowl_ontology_iterate_axioms_of_types(CowlOntology *onto, CowlAxiomFlags types, CowlIterator *iter);

/**
 * Iterates over the axioms referencing the specified primitive.
 *
 * @param onto The ontology.
 * @param primitive The primitive.
 * @param iter The iterator.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_ontology_iterate_axioms_for_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive,
                                                    CowlIterator *iter);

/**
 * Iterates over the axioms matching the specified filter.
 *
 * @param onto The ontology.
 * @param filter The filter.
 * @param iter The iterator.
 * @return Return code.
 *
 * @note The filter must not be used anymore after calling this function.
 */
COWL_API
cowl_ret cowl_ontology_iterate_axioms_matching(CowlOntology *onto, CowlAxiomFilter *filter,
                                               CowlIterator *iter);

/**
 * Iterates over the constructs that are related to the specified primitive by some axiom.
 *
 * @param onto The ontology.
 * @param primitive The primitive.
 * @param types The axiom types.
 * @param position Position of the related constructs.
 * @param iter The iterator.
 * @return Return code.
 */
COWL_API
cowl_ret
cowl_ontology_iterate_related(CowlOntology *onto, CowlAnyPrimitive *primitive, CowlAxiomFlags types,
                              CowlPosition position, CowlIterator *iter);

/**
 * Iterates over the subclasses of the specified class.
 *
 * @param onto The ontology.
 * @param cls The class.
 * @param iter The iterator.
 * @return Return code.
 */
COWL_INLINE
cowl_ret cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *cls, CowlIterator *iter) {
    return cowl_ontology_iterate_related(onto, cls, COWL_AF_SUB_CLASS, COWL_PS_LEFT, iter);
}

/**
 * Iterates over the superclasses of the specified class.
 *
 * @param onto The ontology.
 * @param cls The class.
 * @param iter The iterator.
 * @return Return code.
 */
COWL_INLINE
cowl_ret
cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *cls, CowlIterator *iter) {
    return cowl_ontology_iterate_related(onto, cls, COWL_AF_SUB_CLASS, COWL_PS_RIGHT, iter);
}

/**
 * Iterates over the equivalent classes of the specified class.
 *
 * @param onto The ontology.
 * @param cls The class.
 * @param iter The iterator.
 * @return Return code.
 */
COWL_INLINE
cowl_ret cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *cls, CowlIterator *iter) {
    return cowl_ontology_iterate_related(onto, cls, COWL_AF_EQUIV_CLASSES, COWL_PS_ANY, iter);
}

/**
 * Iterates over the disjoint classes of the specified class.
 *
 * @param onto The ontology.
 * @param cls The class.
 * @param iter The iterator.
 * @return Return code.
 */
COWL_INLINE
cowl_ret
cowl_ontology_iterate_disjoint_classes(CowlOntology *onto, CowlClass *cls, CowlIterator *iter) {
    return cowl_ontology_iterate_related(onto, cls, COWL_AF_DISJ_CLASSES, COWL_PS_ANY, iter);
}

/**
 * Iterates over the types of the specified individual.
 *
 * @param onto The ontology.
 * @param ind The individual.
 * @param iter The iterator.
 * @return Return code.
 */
COWL_INLINE
cowl_ret
cowl_ontology_iterate_types(CowlOntology *onto, CowlAnyIndividual *ind, CowlIterator *iter) {
    return cowl_ontology_iterate_related(onto, ind, COWL_AF_CLASS_ASSERT, COWL_PS_LEFT, iter);
}

/// @}

COWL_END_DECLS

#endif // COWL_ONTOLOGY_H
