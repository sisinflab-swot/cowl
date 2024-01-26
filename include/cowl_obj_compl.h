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
/// @endcond

/**
 * Represents [ObjectComplementOf] in the OWL 2 specification.
 *
 * [ObjectComplementOf]: https://www.w3.org/TR/owl2-syntax/#Complement_of_Class_Expressions
 *
 * @superstruct{CowlClsExp}
 * @struct CowlObjCompl
 */
cowl_struct_decl(CowlObjCompl);

/**
 * @defgroup CowlObjCompl CowlObjCompl API
 * @{
 */

/**
 * Returns the complement of a class expression.
 *
 * @param operand The operand.
 * @return Class expression complement, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlObjCompl *cowl_obj_compl(CowlAnyClsExp *operand) {
    return (CowlObjCompl *)cowl_get_impl_1(COWL_OT_CE_OBJ_COMPL, operand);
}

/**
 * Gets the operand of the specified class expression complement.
 *
 * @param exp The complement.
 * @return The operand.
 */
COWL_PURE
COWL_INLINE
CowlClsExp *cowl_obj_compl_get_operand(CowlObjCompl *exp) {
    return (CowlClsExp *)cowl_get_field(exp, 0);
}

/// @}

COWL_END_DECLS

#endif // COWL_OBJ_COMPL_H
