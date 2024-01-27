/**
 * Declares CowlDataPropRangeAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_RANGE_AXIOM_H
#define COWL_DATA_PROP_RANGE_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents a [DataPropertyRange] axiom in the OWL 2 specification.
 *
 * [DataPropertyRange]: https://www.w3.org/TR/owl2-syntax/#Data_Property_Range
 *
 * @superstruct{CowlAxiom}
 * @struct CowlDataPropRangeAxiom
 */
cowl_struct_decl(CowlDataPropRangeAxiom);

/**
 * @defgroup CowlDataPropRangeAxiom CowlDataPropRangeAxiom API
 * @{
 */

/**
 * Returns a data property range axiom.
 *
 * @param prop The data property.
 * @param range Range of the data property.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDataPropRangeAxiom *
cowl_data_prop_range_axiom(CowlAnyDataPropExp *prop, CowlAnyDataRange *range, CowlVector *annot) {
    return (CowlDataPropRangeAxiom *)cowl_get_impl_2_annot(COWL_OT_A_DATA_PROP_RANGE, prop, range,
                                                           annot);
}

/**
 * Gets the data property.
 *
 * @param axiom The axiom.
 * @return The data property.
 */
COWL_PURE
COWL_INLINE
CowlDataPropExp *cowl_data_prop_range_axiom_get_prop(CowlDataPropRangeAxiom *axiom) {
    return (CowlDataPropExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the range of the data property.
 *
 * @param axiom The axiom.
 * @return Range of the data property.
 */
COWL_PURE
COWL_INLINE
CowlDataRange *cowl_data_prop_range_axiom_get_range(CowlDataPropRangeAxiom *axiom) {
    return (CowlDataRange *)cowl_get_field(axiom, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_DATA_PROP_RANGE_AXIOM_H
