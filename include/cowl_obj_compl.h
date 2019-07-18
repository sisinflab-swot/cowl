/**
 * Declares CowlObjCompl and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_COMPL_H
#define COWL_OBJ_COMPL_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlObjCompl);
/// @endcond

/**
 * Represents [ObjectComplementOf] in the OWL 2 specification.
 *
 * [ObjectComplementOf]: https://www.w3.org/TR/owl2-syntax/#Complement_of_Class_Expressions
 *
 * @struct CowlObjCompl
 * @extends CowlClsExp
 */

/**
 * Returns a retained class expression complement.
 *
 * @param operand The operand.
 * @return Retained class expression complement.
 *
 * @public @memberof CowlObjCompl
 */
COWL_PUBLIC
CowlObjCompl* cowl_obj_compl_get(CowlClsExp *operand);

/**
 * Retains the specified class expression complement.
 *
 * @param exp The complement.
 * @return Retained class expression complement.
 *
 * @public @memberof CowlObjCompl
 */
COWL_PUBLIC
CowlObjCompl* cowl_obj_compl_retain(CowlObjCompl *exp);

/**
 * Releases the specified class expression complement.
 *
 * @param exp The complement.
 *
 * @public @memberof CowlObjCompl
 */
COWL_PUBLIC
void cowl_obj_compl_release(CowlObjCompl *exp);

/**
 * Gets the operand of the specified class expression complement.
 *
 * @param exp The complement.
 * @return The operand.
 *
 * @public @memberof CowlObjCompl
 */
COWL_PUBLIC
CowlClsExp* cowl_obj_compl_get_operand(CowlObjCompl *exp);

/**
 * Returns the string representation of the specified class expression complement.
 *
 * @param exp The class expression complement.
 * @return String representation.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObjCompl
 */
COWL_PUBLIC
CowlString* cowl_obj_compl_to_string(CowlObjCompl *exp);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjCompl
 */
COWL_PUBLIC
bool cowl_obj_compl_equals(CowlObjCompl *lhs, CowlObjCompl *rhs);

/**
 * Hash function.
 *
 * @param exp The complement.
 * @return The hash value.
 *
 * @public @memberof CowlObjCompl
 */
COWL_PUBLIC
cowl_uint_t cowl_obj_compl_hash(CowlObjCompl *exp);

/**
 * Iterates over the signature of the specified class expression complement.
 *
 * @param exp The complement.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjCompl
 */
COWL_PUBLIC
bool cowl_obj_compl_iterate_signature(CowlObjCompl *exp, CowlEntityIterator *iter);

/**
 * Iterates over the anonymous individuals referenced by
 * the specified class expression complement.
 *
 * @param exp The complement.
 * @param iter The anonymous individual iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjCompl
 */
COWL_PUBLIC
bool cowl_obj_compl_iterate_anon_inds(CowlObjCompl *exp, CowlAnonIndIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_COMPL_H
