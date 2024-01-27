/**
 * Declares CowlSubDataPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SUB_DATA_PROP_AXIOM_H
#define COWL_SUB_DATA_PROP_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents a [SubDataPropertyOf] axiom in the OWL 2 specification.
 *
 * [SubDataPropertyOf]: https://www.w3.org/TR/owl2-syntax/#Data_Subproperties
 *
 * @superstruct{CowlAxiom}
 * @struct CowlSubDataPropAxiom
 */
cowl_struct_decl(CowlSubDataPropAxiom);

/**
 * @defgroup CowlSubDataPropAxiom CowlSubDataPropAxiom API
 * @{
 */

/**
 * Returns a data subproperty axiom.
 *
 * @param sub The subproperty.
 * @param super The superproperty.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlSubDataPropAxiom *
cowl_sub_data_prop_axiom(CowlAnyDataPropExp *sub, CowlAnyDataPropExp *super, CowlVector *annot) {
    return (CowlSubDataPropAxiom *)cowl_get_impl_2_annot(COWL_OT_A_SUB_DATA_PROP, sub, super,
                                                         annot);
}

/**
 * Gets the subproperty.
 *
 * @param axiom The axiom.
 * @return The subproperty.
 */
COWL_PURE
COWL_INLINE
CowlDataPropExp *cowl_sub_data_prop_axiom_get_sub(CowlSubDataPropAxiom *axiom) {
    return (CowlDataPropExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the superproperty.
 *
 * @param axiom The axiom.
 * @return The superproperty.
 */
COWL_PURE
COWL_INLINE
CowlDataPropExp *cowl_sub_data_prop_axiom_get_super(CowlSubDataPropAxiom *axiom) {
    return (CowlDataPropExp *)cowl_get_field(axiom, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_SUB_DATA_PROP_AXIOM_H
