/**
 * Declares CowlObjPropAssertAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_ASSERT_AXIOM_H
#define COWL_OBJ_PROP_ASSERT_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlObjPropAssertAxiom);
/// @endcond

/**
 * Represents an [ObjectPropertyAssertion] or [NegativeObjectPropertyAssertion] axiom
 * in the OWL 2 specification.
 *
 * [ObjectPropertyAssertion]:
 * https://www.w3.org/TR/owl2-syntax/#Positive_Object_Property_Assertions
 *
 * [NegativeObjectPropertyAssertion]:
 * https://www.w3.org/TR/owl2-syntax/#Negative_Object_Property_Assertions
 *
 * @struct CowlObjPropAssertAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained object property assertion axiom.
 *
 * @param prop The object property.
 * @param subject The assertion subject.
 * @param object The assertion object.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlObjPropAssertAxiom
 */
COWL_INLINE
CowlObjPropAssertAxiom *
cowl_obj_prop_assert_axiom(CowlAnyObjPropExp *prop, CowlAnyIndividual *subject,
                           CowlAnyIndividual *object, CowlVector *annot) {
    return (CowlObjPropAssertAxiom *)cowl_get_impl_3_annot(COWL_OT_A_OBJ_PROP_ASSERT, prop, subject,
                                                           object, annot);
}

/**
 * Returns a retained negative object property assertion axiom.
 *
 * @param prop The object property.
 * @param subject The assertion subject.
 * @param object The assertion object.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlObjPropAssertAxiom
 */
COWL_INLINE
CowlObjPropAssertAxiom *
cowl_neg_obj_prop_assert_axiom(CowlAnyObjPropExp *prop, CowlAnyIndividual *subject,
                               CowlAnyIndividual *object, CowlVector *annot) {
    return (CowlObjPropAssertAxiom *)cowl_get_impl_3_annot(COWL_OT_A_NEG_OBJ_PROP_ASSERT, prop,
                                                           subject, object, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlObjPropAssertAxiom
 */
COWL_INLINE
CowlObjPropAssertAxiom *cowl_obj_prop_assert_axiom_retain(CowlObjPropAssertAxiom *axiom) {
    return (CowlObjPropAssertAxiom *)cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlObjPropAssertAxiom
 */
COWL_INLINE
void cowl_obj_prop_assert_axiom_release(CowlObjPropAssertAxiom *axiom) {
    cowl_release_impl(axiom);
}

/**
 * Returns true if the specified object property assertion axiom is negative.
 *
 * @param axiom The axiom.
 * @return True if the assertion is negative, false otherwise.
 *
 * @public @memberof CowlObjPropAssertAxiom
 */
COWL_INLINE
bool cowl_obj_prop_assert_axiom_is_negative(CowlObjPropAssertAxiom *axiom) {
    return cowl_get_type(axiom) == COWL_OT_A_NEG_OBJ_PROP_ASSERT;
}

/**
 * Gets the object property expression.
 *
 * @param axiom The axiom.
 * @return The object property expression.
 *
 * @public @memberof CowlObjPropAssertAxiom
 */
COWL_INLINE
CowlObjPropExp *cowl_obj_prop_assert_axiom_get_prop(CowlObjPropAssertAxiom *axiom) {
    return (CowlObjPropExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the assertion subject.
 *
 * @param axiom The axiom.
 * @return The assertion subject.
 *
 * @public @memberof CowlObjPropAssertAxiom
 */
COWL_INLINE
CowlIndividual *cowl_obj_prop_assert_axiom_get_subject(CowlObjPropAssertAxiom *axiom) {
    return (CowlIndividual *)cowl_get_field(axiom, 1);
}

/**
 * Gets the assertion object.
 *
 * @param axiom The axiom.
 * @return The assertion object.
 *
 * @public @memberof CowlObjPropAssertAxiom
 */
COWL_INLINE
CowlIndividual *cowl_obj_prop_assert_axiom_get_object(CowlObjPropAssertAxiom *axiom) {
    return (CowlIndividual *)cowl_get_field(axiom, 2);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlObjPropAssertAxiom
 */
COWL_INLINE
CowlVector *cowl_obj_prop_assert_axiom_get_annot(CowlObjPropAssertAxiom *axiom) {
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
 * @public @memberof CowlObjPropAssertAxiom
 */
COWL_INLINE
CowlString *cowl_obj_prop_assert_axiom_to_string(CowlObjPropAssertAxiom *axiom) {
    return cowl_to_string(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjPropAssertAxiom
 */
COWL_INLINE
bool cowl_obj_prop_assert_axiom_equals(CowlObjPropAssertAxiom *lhs, CowlObjPropAssertAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlObjPropAssertAxiom
 */
COWL_INLINE
ulib_uint cowl_obj_prop_assert_axiom_hash(CowlObjPropAssertAxiom *axiom) {
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
 * @public @memberof CowlObjPropAssertAxiom
 */
COWL_INLINE
bool cowl_obj_prop_assert_axiom_iterate_primitives(CowlObjPropAssertAxiom *axiom,
                                                   CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_OBJ_PROP_ASSERT_AXIOM_H
