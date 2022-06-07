/**
 * Declares default implementations for common functions.
 *
 * @note Never use these directly.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJECT_IMPL_H
#define COWL_OBJECT_IMPL_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond

COWL_PUBLIC
void* cowl_get_impl(CowlObjectType type, void *fields[], void *opt);

COWL_INLINE
void* cowl_get_impl_1(CowlObjectType type, void *f1, void *opt) {
    void *fields[] = { f1 };
    return cowl_get_impl(type, fields, opt);
}

COWL_INLINE
void* cowl_get_impl_2(CowlObjectType type, void *f1, void *f2, void *opt) {
    void *fields[] = { f1, f2 };
    return cowl_get_impl(type, fields, opt);
}

COWL_INLINE
void* cowl_get_impl_3(CowlObjectType type, void *f1, void *f2, void *f3, void *opt) {
    void *fields[] = { f1, f2, f3 };
    return cowl_get_impl(type, fields, opt);
}

COWL_PUBLIC
void* cowl_uint_get_impl(CowlObjectType type, void *fields[], ulib_uint val, void *opt);

COWL_INLINE
void* cowl_uint_get_impl_1(CowlObjectType type, void *f1, ulib_uint val, void *opt) {
    void *fields[] = { f1 };
    return cowl_uint_get_impl(type, fields, val, opt);
}

COWL_INLINE
void* cowl_uint_get_impl_2(CowlObjectType type, void *f1, void *f2, ulib_uint val, void *opt) {
    void *fields[] = { f1, f2 };
    return cowl_uint_get_impl(type, fields, val, opt);
}

COWL_PUBLIC
void cowl_release_impl(void *object);

COWL_PUBLIC
bool cowl_equals_impl(void *lhs, void *rhs);

COWL_PUBLIC
bool cowl_uint_equals_impl(void *lhs, void *rhs);

COWL_PUBLIC
ulib_uint cowl_hash_impl(void *object);

COWL_PUBLIC
ulib_uint cowl_uint_hash_impl(void *object);

COWL_PUBLIC
CowlString* cowl_to_string_impl(void *object);

COWL_PUBLIC
CowlString* cowl_uint_to_string_impl(void *object);

COWL_PUBLIC
bool cowl_iterate_primitives_impl(void *object, CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_PUBLIC
void* cowl_get_field(void *object, ulib_uint index);

COWL_PUBLIC
bool cowl_has_opt_field(void *object);

COWL_PUBLIC
void* cowl_get_opt_field(void *object);

COWL_PUBLIC
ulib_uint cowl_get_uint_field(void *object);

/// @endcond

COWL_END_DECLS

#endif // COWL_OBJECT_IMPL_H
