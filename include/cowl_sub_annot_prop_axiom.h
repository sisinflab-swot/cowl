/**
 * Declares CowlSubAnnotPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SUB_ANNOT_PROP_AXIOM_H
#define COWL_SUB_ANNOT_PROP_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlSubAnnotPropAxiom);
/// @endcond

/**
 * Represents a [SubAnnotationPropertyOf] axiom in the OWL 2 specification.
 *
 * [SubAnnotationPropertyOf]: https://www.w3.org/TR/owl2-syntax/#Annotation_Subproperties
 *
 * @struct CowlSubAnnotPropAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained annotation subproperty axiom.
 *
 * @param sub The subproperty.
 * @param super The superproperty.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_INLINE
CowlSubAnnotPropAxiom* cowl_sub_annot_prop_axiom_get(CowlAnnotProp *sub, CowlAnnotProp *super,
                                                     CowlVector *annot) {
    return (CowlSubAnnotPropAxiom *)cowl_get_impl_2_opt(COWL_OT_A_SUB_ANNOT_PROP,
                                                        sub, super, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_INLINE
CowlSubAnnotPropAxiom* cowl_sub_annot_prop_axiom_retain(CowlSubAnnotPropAxiom *axiom) {
    return (CowlSubAnnotPropAxiom *)cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_INLINE
void cowl_sub_annot_prop_axiom_release(CowlSubAnnotPropAxiom *axiom) {
    cowl_release_impl(axiom);
}

/**
 * Gets the subproperty.
 *
 * @param axiom The axiom.
 * @return The subproperty.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_INLINE
CowlAnnotProp* cowl_sub_annot_prop_axiom_get_sub(CowlSubAnnotPropAxiom *axiom) {
    return (CowlAnnotProp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the superproperty.
 *
 * @param axiom The axiom.
 * @return The superproperty.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_INLINE
CowlAnnotProp* cowl_sub_annot_prop_axiom_get_super(CowlSubAnnotPropAxiom *axiom) {
    return (CowlAnnotProp *)cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_INLINE
CowlVector* cowl_sub_annot_prop_axiom_get_annot(CowlSubAnnotPropAxiom *axiom) {
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
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_INLINE
CowlString* cowl_sub_annot_prop_axiom_to_string(CowlSubAnnotPropAxiom *axiom) {
    return cowl_to_string_impl(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_INLINE
bool cowl_sub_annot_prop_axiom_equals(CowlSubAnnotPropAxiom *lhs, CowlSubAnnotPropAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_INLINE
ulib_uint cowl_sub_annot_prop_axiom_hash(CowlSubAnnotPropAxiom *axiom) {
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
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_INLINE
bool cowl_sub_annot_prop_axiom_iterate_primitives(CowlSubAnnotPropAxiom *axiom,
                                                  CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_SUB_ANNOT_PROP_AXIOM_H
