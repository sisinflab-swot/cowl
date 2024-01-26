/**
 * Declares CowlNAryBool and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_BOOL_H
#define COWL_NARY_BOOL_H

#include "cowl_nary_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents [ObjectIntersectionOf] and [ObjectUnionOf] in the OWL 2 specification.
 *
 * [ObjectIntersectionOf]: https://www.w3.org/TR/owl2-syntax/#Intersection_of_Class_Expressions
 * [ObjectUnionOf]: https://www.w3.org/TR/owl2-syntax/#Union_of_Class_Expressions
 *
 * @superstruct{CowlClsExp}
 * @struct CowlNAryBool
 */
cowl_struct_decl(CowlNAryBool);

/**
 * @defgroup CowlNAryBool CowlNAryBool API
 * @{
 */

/**
 * Returns a N-ary boolean class expression.
 *
 * @param type N-ary class expression type.
 * @param operands The operands.
 * @return Expression, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlNAryBool *cowl_nary_bool(CowlNAryType type, CowlVector *operands) {
    if (!cowl_enum_value_is_valid(NT, type)) return NULL;
    CowlObjectType t = (CowlObjectType)(COWL_OT_CE_OBJ_INTERSECT + (CowlObjectType)type);
    return (CowlNAryBool *)cowl_get_impl_1(t, operands);
}

/**
 * Gets the type of the specified N-ary boolean class expression.
 *
 * @param exp The expression.
 * @return The type.
 */
COWL_PURE
COWL_INLINE
CowlNAryType cowl_nary_bool_get_type(CowlNAryBool *exp) {
    return (CowlNAryType)(cowl_get_type(exp) - COWL_OT_CE_OBJ_INTERSECT);
}

/**
 * Gets the operands of the specified N-ary boolean class expression.
 *
 * @param exp The expression.
 * @return The operands.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_nary_bool_get_operands(CowlNAryBool *exp) {
    return (CowlVector *)cowl_get_field(exp, 0);
}

/// @}

COWL_END_DECLS

#endif // COWL_NARY_BOOL_H
