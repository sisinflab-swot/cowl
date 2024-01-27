/**
 * Declares CowlDataPropAssertAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_ASSERT_AXIOM_H
#define COWL_DATA_PROP_ASSERT_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents a [DataPropertyAssertion] or [NegativeDataPropertyAssertion] axiom
 * in the OWL 2 specification.
 *
 * [DataPropertyAssertion]:
 * https://www.w3.org/TR/owl2-syntax/#Positive_Data_Property_Assertions
 *
 * [NegativeDataPropertyAssertion]:
 * https://www.w3.org/TR/owl2-syntax/#Negative_Data_Property_Assertions
 *
 * @superstruct{CowlAxiom}
 * @struct CowlDataPropAssertAxiom
 */
cowl_struct_decl(CowlDataPropAssertAxiom);

/**
 * @defgroup CowlDataPropAssertAxiom CowlDataPropAssertAxiom API
 * @{
 */

/**
 * Returns a data property assertion axiom.
 *
 * @param prop The data property.
 * @param subj The assertion subject.
 * @param obj The assertion object.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDataPropAssertAxiom *
cowl_data_prop_assert_axiom(CowlAnyDataPropExp *prop, CowlAnyIndividual *subj, CowlLiteral *obj,
                            CowlVector *annot) {
    return (CowlDataPropAssertAxiom *)cowl_get_impl_3_annot(COWL_OT_A_DATA_PROP_ASSERT, prop, subj,
                                                            obj, annot);
}

/**
 * Returns a negative data property assertion axiom.
 *
 * @param subj The assertion subject.
 * @param prop The data property.
 * @param obj The assertion object.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDataPropAssertAxiom *
cowl_neg_data_prop_assert_axiom(CowlAnyDataPropExp *prop, CowlAnyIndividual *subj, CowlLiteral *obj,
                                CowlVector *annot) {
    return (CowlDataPropAssertAxiom *)cowl_get_impl_3_annot(COWL_OT_A_NEG_DATA_PROP_ASSERT, prop,
                                                            subj, obj, annot);
}

/**
 * Returns true if the specified data property assertion axiom is negative.
 *
 * @param axiom The axiom.
 * @return True if the assertion is negative, false otherwise.
 */
COWL_PURE
COWL_INLINE
bool cowl_data_prop_assert_axiom_is_negative(CowlDataPropAssertAxiom *axiom) {
    return cowl_get_type(axiom) == COWL_OT_A_NEG_DATA_PROP_ASSERT;
}

/**
 * Gets the data property.
 *
 * @param axiom The axiom.
 * @return The data property.
 */
COWL_PURE
COWL_INLINE
CowlDataPropExp *cowl_data_prop_assert_axiom_get_prop(CowlDataPropAssertAxiom *axiom) {
    return (CowlDataPropExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the assertion subject.
 *
 * @param axiom The axiom.
 * @return The assertion subject.
 */
COWL_PURE
COWL_INLINE
CowlIndividual *cowl_data_prop_assert_axiom_get_subject(CowlDataPropAssertAxiom *axiom) {
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
CowlLiteral *cowl_data_prop_assert_axiom_get_object(CowlDataPropAssertAxiom *axiom) {
    return (CowlLiteral *)cowl_get_field(axiom, 2);
}

/// @}

COWL_END_DECLS

#endif // COWL_DATA_PROP_ASSERT_AXIOM_H
