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
cowl_struct_decl(CowlClsAssertAxiom);
/// @endcond

/**
 * Represents a [ClassAssertion] axiom in the OWL 2 specification.
 *
 * [ClassAssertion]: https://www.w3.org/TR/owl2-syntax/#Class_Assertions
 *
 * @struct CowlClsAssertAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a class assertion axiom.
 *
 * @param exp The asserted class expression.
 * @param ind The assertion individual.
 * @param annot [optional] The annotations.
 * @return Axiom, or NULL on error.
 *
 * @public @memberof CowlClsAssertAxiom
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
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_INLINE
CowlClsExp *cowl_cls_assert_axiom_get_cls_exp(CowlClsAssertAxiom *axiom) {
    return (CowlClsExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the individual that is asserted to be an instance of a class expression by this axiom.
 *
 * @param axiom The axiom.
 * @return The individual.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_INLINE
CowlIndividual *cowl_cls_assert_axiom_get_ind(CowlClsAssertAxiom *axiom) {
    return (CowlIndividual *)cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlClsAssertAxiom
 */
COWL_INLINE
CowlVector *cowl_cls_assert_axiom_get_annot(CowlClsAssertAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

COWL_END_DECLS

#endif // COWL_CLS_ASSERT_AXIOM_H
