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

#include "cowl_any.h"
#include "cowl_attrs.h"
#include "cowl_impl.h"
#include "cowl_utils.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents a [HasKey] axiom in the OWL 2 specification.
 *
 * [HasKey]: https://www.w3.org/TR/owl2-syntax/#Keys
 *
 * @superstruct{CowlAxiom}
 * @struct CowlHasKeyAxiom
 */
cowl_struct_decl(CowlHasKeyAxiom);

/**
 * @defgroup CowlHasKeyAxiom CowlHasKeyAxiom API
 * @{
 */

/**
 * Returns a 'has key' axiom.
 *
 * @param cls_exp The class expression, instances of which this axiom acts as the key for.
 * @param obj_props @ctype{optional} Object property expressions that make up the key.
 * @param data_props @ctype{optional} Data property expressions that make up the key.
 * @param annot @ctype{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlHasKeyAxiom *cowl_has_key_axiom(CowlAnyClsExp *cls_exp, CowlVector *obj_props,
                                    CowlVector *data_props, CowlVector *annot);

/**
 * Gets the class expression, instances of which this axiom acts as the key for.
 *
 * @param axiom The axiom.
 * @return The class expression.
 */
COWL_PURE
COWL_INLINE
CowlClsExp *cowl_has_key_axiom_get_cls_exp(CowlHasKeyAxiom *axiom) {
    return (CowlClsExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the set of object property expressions that make up the key.
 *
 * @param axiom The axiom.
 * @return The object property expressions.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_has_key_axiom_get_obj_props(CowlHasKeyAxiom *axiom) {
    return (CowlVector *)cowl_get_field(axiom, 1);
}

/**
 * Gets the set of data property expressions that make up the key.
 *
 * @param axiom The axiom.
 * @return The data property expressions.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_has_key_axiom_get_data_props(CowlHasKeyAxiom *axiom) {
    return (CowlVector *)cowl_get_field(axiom, 2);
}

/// @}

COWL_END_DECLS

#endif // COWL_HAS_KEY_AXIOM_H
