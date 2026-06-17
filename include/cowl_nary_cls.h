/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2026 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_CLS_H
#define COWL_NARY_CLS_H

#include "cowl_attrs.h"
#include "cowl_impl.h"
#include "cowl_nary_type.h"
#include "cowl_object.h"
#include "cowl_object_type.h"
#include "cowl_utils.h"
#include <stddef.h>

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
 * @struct CowlNAryCls
 */
cowl_struct_decl(CowlNAryCls);

/**
 * @copydoc CowlNAryCls
 * @deprecated Use @type{CowlNAryCls} instead.
 */
#define CowlNAryBool COWL_DEPRECATED_MACRO CowlNAryCls

/**
 * @defgroup CowlNAryCls CowlNAryCls API
 * @{
 */

/**
 * Returns a N-ary class expression.
 *
 * @param type N-ary class expression type.
 * @param operands The operands.
 * @return Expression, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlNAryCls *cowl_nary_cls(CowlNAryType type, CowlVector *operands) {
    if (!cowl_enum_value_is_valid(NT, type)) return NULL;
    CowlObjectType t = (CowlObjectType)(COWL_OT_CE_OBJ_INTERSECT + (CowlObjectType)type);
    return (CowlNAryCls *)cowl_get_impl_1(t, operands);
}

/// @copydoc cowl_nary_cls
COWL_DEPRECATED(Use @func{cowl_nary_cls} instead.)
COWL_INLINE
CowlNAryCls *cowl_nary_bool(CowlNAryType type, CowlVector *operands) {
    return cowl_nary_cls(type, operands);
}

/**
 * Returns an intersection of class expressions.
 *
 * @param operands The operands.
 * @return Expression, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlNAryCls *cowl_obj_intersect(CowlVector *operands) {
    return cowl_nary_cls(COWL_NT_INTERSECT, operands);
}

/**
 * Returns an intersection of class expressions.
 *
 * @param ... The operands.
 * @return Expression, or NULL on error.
 *
 * @alias CowlNAryCls *cowl_obj_intersect_of(...);
 */
COWL_RETAINED
#define cowl_obj_intersect_of(...) cowl_nary_get_impl(COWL_OT_CE_OBJ_INTERSECT, __VA_ARGS__, NULL)

/**
 * Returns a union of class expressions.
 *
 * @param operands The operands.
 * @return Expression, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlNAryCls *cowl_obj_union(CowlVector *operands) {
    return cowl_nary_cls(COWL_NT_UNION, operands);
}

/**
 * Returns a union of class expressions
 *
 * @param ... The operands.
 * @return Expression, or NULL on error.
 *
 * @alias CowlNAryCls *cowl_obj_union_of(...);
 */
COWL_RETAINED
#define cowl_obj_union_of(...) cowl_nary_get_impl(COWL_OT_CE_OBJ_UNION, __VA_ARGS__, NULL)

/**
 * Gets the type of the specified N-ary class expression.
 *
 * @param exp The expression.
 * @return The type.
 */
COWL_PURE
COWL_INLINE
CowlNAryType cowl_nary_cls_get_type(CowlNAryCls *exp) {
    return (CowlNAryType)(cowl_get_type(exp) - COWL_OT_CE_OBJ_INTERSECT);
}

/// @copydoc cowl_nary_cls_get_type
COWL_DEPRECATED(Use @func{cowl_nary_cls_get_type} instead.)
COWL_INLINE
CowlNAryType cowl_nary_bool_get_type(CowlNAryCls *exp) {
    return cowl_nary_cls_get_type(exp);
}

/**
 * Gets the operands of the specified N-ary class expression.
 *
 * @param exp The expression.
 * @return The operands.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_nary_cls_get_operands(CowlNAryCls *exp) {
    return (CowlVector *)cowl_get_field(exp, 0);
}

/// @copydoc cowl_nary_cls_get_operands
COWL_DEPRECATED(Use @func{cowl_nary_cls_get_operands} instead.)
COWL_INLINE
CowlVector *cowl_nary_bool_get_operands(CowlNAryCls *exp) {
    return cowl_nary_cls_get_operands(exp);
}

/// @}

COWL_END_DECLS

#endif // COWL_NARY_CLS_H
