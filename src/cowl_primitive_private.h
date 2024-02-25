/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PRIMITIVE_PRIVATE_H
#define COWL_PRIMITIVE_PRIVATE_H

#include "cowl_primitive.h"

COWL_BEGIN_DECLS

COWL_CONST
COWL_INLINE
bool cowl_primitive_type_is_entity(CowlPrimitiveType type) {
    return type != COWL_PT_IRI && type != COWL_PT_ANON_IND;
}

COWL_CONST
COWL_INLINE
bool cowl_primitive_equals(CowlAnyPrimitive *lhs, CowlAnyPrimitive *rhs) {
    return lhs == rhs;
}

COWL_CONST
COWL_INLINE
ulib_uint cowl_primitive_hash(CowlAnyPrimitive *primitive) {
    return ulib_hash_alloc_ptr(primitive);
}

COWL_END_DECLS

#endif // COWL_PRIMITIVE_PRIVATE_H
