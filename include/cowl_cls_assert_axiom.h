/**
 * Declares CowlClsAssertAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CLS_ASSERT_AXIOM_H
#define COWL_CLS_ASSERT_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents a [ClassAssertion] axiom in the OWL 2 specification.
 *
 * [ClassAssertion]: https://www.w3.org/TR/owl2-syntax/#Class_Assertions
 *
 * @superstruct{CowlAxiom}
 * @struct CowlClsAssertAxiom
 */
cowl_struct_decl(CowlClsAssertAxiom);

/**
 * @defgroup CowlClsAssertAxiom CowlClsAssertAxiom API
 * @{
 */

/**
 * Returns a class assertion axiom.
 *
 * @param exp The asserted class expression.
 * @param ind The assertion individual.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlClsAssertAxiom *
cowl_cls_assert_axiom(CowlAnyClsExp *exp, CowlAnyIndividual *ind, CowlVector *annot) {
    return (CowlClsAssertAxiom *)cowl_get_impl_2_annot(COWL_OT_A_CLASS_ASSERT, exp, ind, annot);
}

/**
 * Gets the class expression that is asserted to be a type for an individual by this axiom.
 *
 * @param axiom The axiom.
 * @return The class expression.
 */
COWL_PURE
COWL_INLINE
CowlClsExp *cowl_cls_assert_axiom_get_cls_exp(CowlClsAssertAxiom *axiom) {
    return (CowlClsExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the individual that is asserted to be an instance of a class expression by this axiom.
 *
 * @param axiom The axiom.
 * @return The individual.
 */
COWL_PURE
COWL_INLINE
CowlIndividual *cowl_cls_assert_axiom_get_ind(CowlClsAssertAxiom *axiom) {
    return (CowlIndividual *)cowl_get_field(axiom, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_CLS_ASSERT_AXIOM_H
