/**
 * Declares CowlHasKeyAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_HAS_KEY_AXIOM_H
#define COWL_HAS_KEY_AXIOM_H

#include "cowl_object.h"
#include "cowl_vector.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlHasKeyAxiom);
/// @endcond

/**
 * Represents a [HasKey] axiom in the OWL 2 specification.
 *
 * [HasKey]: https://www.w3.org/TR/owl2-syntax/#Keys
 *
 * @struct CowlHasKeyAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained 'has key' axiom.
 *
 * @param cls_exp The class expression, instances of which this axiom acts as the key for.
 * @param obj_props Object property expressions that make up the key.
 * @param data_props Data property expressions that make up the key.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_INLINE
CowlHasKeyAxiom *cowl_has_key_axiom(CowlAnyClsExp *cls_exp, CowlVector *obj_props,
                                    CowlVector *data_props, CowlVector *annot) {
    if (!obj_props) obj_props = cowl_vector_empty();
    if (!data_props) data_props = cowl_vector_empty();
    return (CowlHasKeyAxiom *)cowl_get_impl_3_annot(COWL_OT_A_HAS_KEY, cls_exp, obj_props,
                                                    data_props, annot);
}

/**
 * Gets the class expression, instances of which this axiom acts as the key for.
 *
 * @param axiom The axiom.
 * @return The class expression.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_INLINE
CowlClsExp *cowl_has_key_axiom_get_cls_exp(CowlHasKeyAxiom *axiom) {
    return (CowlClsExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the set of object property expressions that make up the key.
 *
 * @param axiom The axiom.
 * @return The object property expressions.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_INLINE
CowlVector *cowl_has_key_axiom_get_obj_props(CowlHasKeyAxiom *axiom) {
    return (CowlVector *)cowl_get_field(axiom, 1);
}

/**
 * Gets the set of data property expressions that make up the key.
 *
 * @param axiom The axiom.
 * @return The data property expressions.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_INLINE
CowlVector *cowl_has_key_axiom_get_data_props(CowlHasKeyAxiom *axiom) {
    return (CowlVector *)cowl_get_field(axiom, 2);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlHasKeyAxiom
 */
COWL_INLINE
CowlVector *cowl_has_key_axiom_get_annot(CowlHasKeyAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

COWL_END_DECLS

#endif // COWL_HAS_KEY_AXIOM_H
