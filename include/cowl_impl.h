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

#ifndef COWL_IMPL_H
#define COWL_IMPL_H

#include "cowl_object_type.h"
#include "cowl_primitive_flags.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);

COWL_PUBLIC
CowlAny* cowl_get_impl(CowlObjectType type, CowlAny *fields[], CowlAny *opt);

COWL_INLINE
CowlAny* cowl_get_impl_1_opt(CowlObjectType type, CowlAny *f1, CowlAny *opt) {
    CowlAny *fields[] = { f1 };
    return cowl_get_impl(type, fields, opt);
}


COWL_INLINE
CowlAny* cowl_get_impl_1(CowlObjectType type, CowlAny *f1) {
    return cowl_get_impl_1_opt(type, f1, NULL);
}

COWL_INLINE
CowlAny* cowl_get_impl_2_opt(CowlObjectType type, CowlAny *f1, CowlAny *f2, CowlAny *opt) {
    CowlAny *fields[] = { f1, f2 };
    return cowl_get_impl(type, fields, opt);
}

COWL_INLINE
CowlAny* cowl_get_impl_2(CowlObjectType type, CowlAny *f1, CowlAny *f2) {
    return cowl_get_impl_2_opt(type, f1, f2, NULL);
}

COWL_INLINE
CowlAny* cowl_get_impl_3_opt(CowlObjectType type, CowlAny *f1, CowlAny *f2,
                             CowlAny *f3, CowlAny *opt) {
    CowlAny *fields[] = { f1, f2, f3 };
    return cowl_get_impl(type, fields, opt);
}

COWL_INLINE
CowlAny* cowl_get_impl_3(CowlObjectType type, CowlAny *f1, CowlAny *f2, CowlAny *f3) {
    return cowl_get_impl_3_opt(type, f1, f2, f3, NULL);
}

COWL_PUBLIC
CowlAny* cowl_get_impl_uint(CowlObjectType type, CowlAny *fields[], ulib_uint val, CowlAny *opt);

COWL_INLINE
CowlAny* cowl_get_impl_1_uint_opt(CowlObjectType type, CowlAny *f1, ulib_uint val, CowlAny *opt) {
    CowlAny *fields[] = { f1 };
    return cowl_get_impl_uint(type, fields, val, opt);
}

COWL_INLINE
CowlAny* cowl_get_impl_1_uint(CowlObjectType type, CowlAny *f1, ulib_uint val) {
    return cowl_get_impl_1_uint_opt(type, f1, val, NULL);
}

COWL_INLINE
CowlAny* cowl_get_impl_2_uint_opt(CowlObjectType type, CowlAny *f1, CowlAny *f2,
                                  ulib_uint val, CowlAny *opt) {
    CowlAny *fields[] = { f1, f2 };
    return cowl_get_impl_uint(type, fields, val, opt);
}

COWL_INLINE
CowlAny* cowl_get_impl_2_uint(CowlObjectType type, CowlAny *f1, CowlAny *f2, ulib_uint val) {
    return cowl_get_impl_2_uint_opt(type, f1, f2, val, NULL);
}

COWL_PUBLIC
CowlAnyEntity* cowl_entity_get_impl(CowlObjectType type, CowlIRI *iri);

COWL_PUBLIC
CowlAnyEntity* cowl_entity_from_string_impl(CowlObjectType type, UString string);

COWL_PUBLIC
void cowl_release_impl(CowlAny *object);

COWL_PUBLIC
bool cowl_equals_impl(CowlAny *lhs, CowlAny *rhs);

COWL_PUBLIC
bool cowl_uint_equals_impl(CowlAny *lhs, CowlAny *rhs);

COWL_PUBLIC
ulib_uint cowl_hash_impl(CowlAny *object);

COWL_PUBLIC
ulib_uint cowl_uint_hash_impl(CowlAny *object);

COWL_PUBLIC
bool cowl_iterate_primitives_impl(CowlAny *object, CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_PUBLIC
CowlAny* cowl_get_field(CowlAny *object, ulib_uint index);

COWL_PUBLIC
bool cowl_has_opt_field(CowlAny *object);

COWL_PUBLIC
CowlAny* cowl_get_opt_field(CowlAny *object);

COWL_PUBLIC
ulib_uint cowl_get_uint_field(CowlAny *object);

/// @endcond

COWL_END_DECLS

#endif // COWL_IMPL_H
