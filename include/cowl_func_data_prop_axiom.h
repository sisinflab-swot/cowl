/**
 * Declares CowlFuncDataPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_FUNC_DATA_PROP_AXIOM_H
#define COWL_FUNC_DATA_PROP_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents a [FunctionalDataProperty] axiom in the OWL 2 Specification.
 *
 * [FunctionalDataProperty]: https://www.w3.org/TR/owl2-syntax/#Functional_Data_Properties
 *
 * @superstruct{CowlAxiom}
 * @struct CowlFuncDataPropAxiom
 */
cowl_struct_decl(CowlFuncDataPropAxiom);

/**
 * @defgroup CowlFuncDataPropAxiom CowlFuncDataPropAxiom API
 * @{
 */

/**
 * Returns a functional data property axiom.
 *
 * @param prop The data property.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlFuncDataPropAxiom *cowl_func_data_prop_axiom(CowlAnyDataPropExp *prop, CowlVector *annot) {
    return (CowlFuncDataPropAxiom *)cowl_get_impl_1_annot(COWL_OT_A_FUNC_DATA_PROP, prop, annot);
}

/**
 * Gets the data property.
 *
 * @param axiom The axiom.
 * @return The data property.
 */
COWL_PURE
COWL_INLINE
CowlDataPropExp *cowl_func_data_prop_axiom_get_prop(CowlFuncDataPropAxiom *axiom) {
    return (CowlDataPropExp *)cowl_get_field(axiom, 0);
}

/// @}

COWL_END_DECLS

#endif // COWL_FUNC_DATA_PROP_AXIOM_H
