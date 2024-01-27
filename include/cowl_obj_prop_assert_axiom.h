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
 * @superstruct{CowlAxiom}
 * @struct CowlObjPropAssertAxiom
 */
cowl_struct_decl(CowlObjPropAssertAxiom);

/**
 * @defgroup CowlObjPropAssertAxiom CowlObjPropAssertAxiom API
 * @{
 */

/**
 * Returns an object property assertion axiom.
 *
 * @param prop The object property.
 * @param subject The assertion subject.
 * @param object The assertion object.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlObjPropAssertAxiom *
cowl_obj_prop_assert_axiom(CowlAnyObjPropExp *prop, CowlAnyIndividual *subject,
                           CowlAnyIndividual *object, CowlVector *annot) {
    return (CowlObjPropAssertAxiom *)cowl_get_impl_3_annot(COWL_OT_A_OBJ_PROP_ASSERT, prop, subject,
                                                           object, annot);
}

/**
 * Returns a negative object property assertion axiom.
 *
 * @param prop The object property.
 * @param subject The assertion subject.
 * @param object The assertion object.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlObjPropAssertAxiom *
cowl_neg_obj_prop_assert_axiom(CowlAnyObjPropExp *prop, CowlAnyIndividual *subject,
                               CowlAnyIndividual *object, CowlVector *annot) {
    return (CowlObjPropAssertAxiom *)cowl_get_impl_3_annot(COWL_OT_A_NEG_OBJ_PROP_ASSERT, prop,
                                                           subject, object, annot);
}

/**
 * Returns true if the specified object property assertion axiom is negative.
 *
 * @param axiom The axiom.
 * @return True if the assertion is negative, false otherwise.
 */
COWL_PURE
COWL_INLINE
bool cowl_obj_prop_assert_axiom_is_negative(CowlObjPropAssertAxiom *axiom) {
    return cowl_get_type(axiom) == COWL_OT_A_NEG_OBJ_PROP_ASSERT;
}

/**
 * Gets the object property expression.
 *
 * @param axiom The axiom.
 * @return The object property expression.
 */
COWL_PURE
COWL_INLINE
CowlObjPropExp *cowl_obj_prop_assert_axiom_get_prop(CowlObjPropAssertAxiom *axiom) {
    return (CowlObjPropExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the assertion subject.
 *
 * @param axiom The axiom.
 * @return The assertion subject.
 */
COWL_PURE
COWL_INLINE
CowlIndividual *cowl_obj_prop_assert_axiom_get_subject(CowlObjPropAssertAxiom *axiom) {
    return (CowlIndividual *)cowl_get_field(axiom, 1);
}

/**
 * Gets the assertion object.
 *
 * @param axiom The axiom.
 * @return The assertion object.
 */
COWL_PURE
COWL_INLINE
CowlIndividual *cowl_obj_prop_assert_axiom_get_object(CowlObjPropAssertAxiom *axiom) {
    return (CowlIndividual *)cowl_get_field(axiom, 2);
}

/// @}

COWL_END_DECLS

#endif // COWL_OBJ_PROP_ASSERT_AXIOM_H
