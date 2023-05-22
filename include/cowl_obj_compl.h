/**
 * Declares CowlObjCompl and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_COMPL_H
#define COWL_OBJ_COMPL_H

#include "cowl_object.h"

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
 * @return Retained class expression complement, or NULL on error.
 *
 * @public @memberof CowlObjCompl
 */
COWL_INLINE
CowlObjCompl *cowl_obj_compl(CowlAnyClsExp *operand) {
    return (CowlObjCompl *)cowl_get_impl_1(COWL_OT_CE_OBJ_COMPL, operand);
}

/**
 * Gets the operand of the specified class expression complement.
 *
 * @param exp The complement.
 * @return The operand.
 *
 * @public @memberof CowlObjCompl
 */
COWL_INLINE
CowlClsExp *cowl_obj_compl_get_operand(CowlObjCompl *exp) {
    return (CowlClsExp *)cowl_get_field(exp, 0);
}

/**
 * Returns the string representation of the specified class expression complement.
 *
 * @param exp The class expression complement.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObjCompl
 */
COWL_INLINE
CowlString *cowl_obj_compl_to_string(CowlObjCompl *exp) {
    return cowl_to_string(exp);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjCompl
 */
COWL_INLINE
bool cowl_obj_compl_equals(CowlObjCompl *lhs, CowlObjCompl *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param exp The complement.
 * @return The hash value.
 *
 * @public @memberof CowlObjCompl
 */
COWL_INLINE
ulib_uint cowl_obj_compl_hash(CowlObjCompl *exp) {
    return cowl_hash_impl(exp);
}

COWL_END_DECLS

#endif // COWL_OBJ_COMPL_H
