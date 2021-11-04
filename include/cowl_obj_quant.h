/**
 * Declares CowlObjQuant and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_QUANT_H
#define COWL_OBJ_QUANT_H

#include "cowl_std.h"
#include "cowl_iterator.h"
#include "cowl_quant_type.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlObjQuant);
/// @endcond

/**
 * Represents [ObjectSomeValuesFrom] and [ObjectAllValuesFrom] in the OWL 2 specification.
 *
 * [ObjectSomeValuesFrom]: https://www.w3.org/TR/owl2-syntax/#Existential_Quantification
 * [ObjectAllValuesFrom]: https://www.w3.org/TR/owl2-syntax/#Universal_Quantification
 *
 * @struct CowlObjQuant
 * @extends CowlClsExp
 */

/**
 * Returns a retained object quantifier.
 *
 * @param type Object quantifier type.
 * @param prop The object property.
 * @param filler Filler of the quantifier.
 * @return Retained object quantifier, or NULL on error.
 *
 * @public @memberof CowlObjQuant
 */
COWL_PUBLIC
CowlObjQuant* cowl_obj_quant_get(CowlQuantType type, CowlObjPropExp *prop, CowlClsExp *filler);

/**
 * Retains the specified object quantifier.
 *
 * @param restr The object quantifier.
 * @return Retained object quantifier.
 *
 * @public @memberof CowlObjQuant
 */
COWL_PUBLIC
CowlObjQuant* cowl_obj_quant_retain(CowlObjQuant *restr);

/**
 * Releases the specified object quantifier.
 *
 * @param restr The object quantifier.
 *
 * @public @memberof CowlObjQuant
 */
COWL_PUBLIC
void cowl_obj_quant_release(CowlObjQuant *restr);

/**
 * Gets the type of the specified object quantifier.
 *
 * @param restr The object quantifier.
 * @return The type of the object quantifier.
 *
 * @public @memberof CowlObjQuant
 */
COWL_PUBLIC
CowlQuantType cowl_obj_quant_get_type(CowlObjQuant *restr);

/**
 * Gets the object property.
 *
 * @param restr The object quantifier.
 * @return The object property.
 *
 * @public @memberof CowlObjQuant
 */
COWL_PUBLIC
CowlObjPropExp* cowl_obj_quant_get_prop(CowlObjQuant *restr);

/**
 * Gets the filler of the specified object quantifier.
 *
 * @param restr The object quantifier.
 * @return Range of the object quantifier.
 *
 * @public @memberof CowlObjQuant
 */
COWL_PUBLIC
CowlClsExp* cowl_obj_quant_get_filler(CowlObjQuant *restr);

/**
 * Returns the string representation of the specified object quantifier.
 *
 * @param restr The object quantifier.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObjQuant
 */
COWL_PUBLIC
CowlString* cowl_obj_quant_to_string(CowlObjQuant *restr);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjQuant
 */
COWL_PUBLIC
bool cowl_obj_quant_equals(CowlObjQuant *lhs, CowlObjQuant *rhs);

/**
 * Hash function.
 *
 * @param restr The object quantifier.
 * @return The hash value.
 *
 * @public @memberof CowlObjQuant
 */
COWL_PUBLIC
ulib_uint cowl_obj_quant_hash(CowlObjQuant *restr);

/**
 * Iterates over the primitives referenced by the specified object quantifier.
 *
 * @param restr The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjQuant
 */
COWL_PUBLIC
bool cowl_obj_quant_iterate_primitives(CowlObjQuant *restr, CowlPrimitiveFlags flags,
                                       CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_QUANT_H
