/**
 * Declares CowlObjPropRangeAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_RANGE_AXIOM_H
#define COWL_OBJ_PROP_RANGE_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents an [ObjectPropertyRange] axiom in the OWL 2 specification.
 *
 * [ObjectPropertyRange]: https://www.w3.org/TR/owl2-syntax/#Object_Property_Range
 *
 * @superstruct{CowlAxiom}
 * @struct CowlObjPropRangeAxiom
 */
cowl_struct_decl(CowlObjPropRangeAxiom);

/**
 * @defgroup CowlObjPropRangeAxiom CowlObjPropRangeAxiom API
 * @{
 */

/**
 * Returns an object property range axiom.
 *
 * @param prop The object property.
 * @param range Range of the object property.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlObjPropRangeAxiom *
cowl_obj_prop_range_axiom(CowlAnyObjPropExp *prop, CowlAnyClsExp *range, CowlVector *annot) {
    return (CowlObjPropRangeAxiom *)cowl_get_impl_2_annot(COWL_OT_A_OBJ_PROP_RANGE, prop, range,
                                                          annot);
}

/**
 * Gets the object property.
 *
 * @param axiom The axiom.
 * @return The object property.
 */
COWL_PURE
COWL_INLINE
CowlObjPropExp *cowl_obj_prop_range_axiom_get_prop(CowlObjPropRangeAxiom *axiom) {
    return (CowlObjPropExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the range of the object property.
 *
 * @param axiom The axiom.
 * @return Range of the object property.
 */
COWL_PURE
COWL_INLINE
CowlClsExp *cowl_obj_prop_range_axiom_get_range(CowlObjPropRangeAxiom *axiom) {
    return (CowlClsExp *)cowl_get_field(axiom, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_OBJ_PROP_RANGE_AXIOM_H
