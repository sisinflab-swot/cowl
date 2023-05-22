/**
 * Declares CowlAnnotPropRangeAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_PROP_RANGE_AXIOM_H
#define COWL_ANNOT_PROP_RANGE_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlAnnotPropRangeAxiom);
/// @endcond

/**
 * Represents an [AnnotationPropertyRange] axiom in the OWL 2 specification.
 *
 * [AnnotationPropertyRange]: https://www.w3.org/TR/owl2-syntax/#Annotation_Property_Range
 *
 * @struct CowlAnnotPropRangeAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained annotation property range axiom.
 *
 * @param prop The annotation property.
 * @param range Range of the annotation property.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlAnnotPropRangeAxiom
 */
COWL_INLINE
CowlAnnotPropRangeAxiom *
cowl_annot_prop_range_axiom(CowlAnnotProp *prop, CowlIRI *range, CowlVector *annot) {
    return (CowlAnnotPropRangeAxiom *)cowl_get_impl_2_annot(COWL_OT_A_ANNOT_PROP_RANGE, prop, range,
                                                            annot);
}

/**
 * Gets the annotation property.
 *
 * @param axiom The axiom.
 * @return The annotation property.
 *
 * @public @memberof CowlAnnotPropRangeAxiom
 */
COWL_INLINE
CowlAnnotProp *cowl_annot_prop_range_axiom_get_prop(CowlAnnotPropRangeAxiom *axiom) {
    return (CowlAnnotProp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the range of the annotation property.
 *
 * @param axiom The axiom.
 * @return Range of the annotation property.
 *
 * @public @memberof CowlAnnotPropRangeAxiom
 */
COWL_INLINE
CowlIRI *cowl_annot_prop_range_axiom_get_range(CowlAnnotPropRangeAxiom *axiom) {
    return (CowlIRI *)cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlAnnotPropRangeAxiom
 */
COWL_INLINE
CowlVector *cowl_annot_prop_range_axiom_get_annot(CowlAnnotPropRangeAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlAnnotPropRangeAxiom
 */
COWL_INLINE
CowlString *cowl_annot_prop_range_axiom_to_string(CowlAnnotPropRangeAxiom *axiom) {
    return cowl_to_string(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnnotPropRangeAxiom
 */
COWL_INLINE
bool cowl_annot_prop_range_axiom_equals(CowlAnnotPropRangeAxiom *lhs,
                                        CowlAnnotPropRangeAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlAnnotPropRangeAxiom
 */
COWL_INLINE
ulib_uint cowl_annot_prop_range_axiom_hash(CowlAnnotPropRangeAxiom *axiom) {
    return cowl_hash_impl(axiom);
}

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlAnnotPropRangeAxiom
 */
COWL_INLINE
bool cowl_annot_prop_range_axiom_iterate_primitives(CowlAnnotPropRangeAxiom *axiom,
                                                    CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_RANGE_AXIOM_H
