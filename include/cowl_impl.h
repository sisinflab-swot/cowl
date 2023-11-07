/**
 * Declares default implementations for common functions.
 *
 * @note Never use these directly.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_IMPL_H
#define COWL_IMPL_H

#include "cowl_iterator.h"
#include "cowl_object_type.h"
#include "cowl_primitive_flags.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlVector);

COWL_API
COWL_RETAINED
CowlAny *cowl_get_impl(CowlObjectType type, CowlAny *fields[], CowlAny *opt);

COWL_API
COWL_RETAINED
CowlAny *cowl_get_impl_annot(CowlObjectType type, CowlAny *fields[], CowlVector *annot);

COWL_RETAINED
COWL_INLINE
CowlAny *cowl_get_impl_1_opt(CowlObjectType type, CowlAny *f1, CowlAny *opt) {
    CowlAny *fields[] = { f1 };
    return cowl_get_impl(type, fields, opt);
}

COWL_RETAINED
COWL_INLINE
CowlAny *cowl_get_impl_1_annot(CowlObjectType type, CowlAny *f1, CowlVector *annot) {
    CowlAny *fields[] = { f1 };
    return cowl_get_impl_annot(type, fields, annot);
}

COWL_RETAINED
COWL_INLINE
CowlAny *cowl_get_impl_1(CowlObjectType type, CowlAny *f1) {
    return cowl_get_impl_1_opt(type, f1, NULL);
}

COWL_RETAINED
COWL_INLINE
CowlAny *cowl_get_impl_2_opt(CowlObjectType type, CowlAny *f1, CowlAny *f2, CowlAny *opt) {
    CowlAny *fields[] = { f1, f2 };
    return cowl_get_impl(type, fields, opt);
}

COWL_RETAINED
COWL_INLINE
CowlAny *cowl_get_impl_2_annot(CowlObjectType type, CowlAny *f1, CowlAny *f2, CowlVector *annot) {
    CowlAny *fields[] = { f1, f2 };
    return cowl_get_impl_annot(type, fields, annot);
}

COWL_RETAINED
COWL_INLINE
CowlAny *cowl_get_impl_2(CowlObjectType type, CowlAny *f1, CowlAny *f2) {
    return cowl_get_impl_2_opt(type, f1, f2, NULL);
}

COWL_RETAINED
COWL_INLINE
CowlAny *
cowl_get_impl_3_opt(CowlObjectType type, CowlAny *f1, CowlAny *f2, CowlAny *f3, CowlAny *opt) {
    CowlAny *fields[] = { f1, f2, f3 };
    return cowl_get_impl(type, fields, opt);
}

COWL_RETAINED
COWL_INLINE
CowlAny *cowl_get_impl_3_annot(CowlObjectType type, CowlAny *f1, CowlAny *f2, CowlAny *f3,
                               CowlVector *annot) {
    CowlAny *fields[] = { f1, f2, f3 };
    return cowl_get_impl_annot(type, fields, annot);
}

COWL_RETAINED
COWL_INLINE
CowlAny *cowl_get_impl_3(CowlObjectType type, CowlAny *f1, CowlAny *f2, CowlAny *f3) {
    return cowl_get_impl_3_opt(type, f1, f2, f3, NULL);
}

COWL_API
COWL_RETAINED
CowlAny *cowl_get_impl_uint(CowlObjectType type, CowlAny *fields[], ulib_uint val, CowlAny *opt);

COWL_RETAINED
COWL_INLINE
CowlAny *cowl_get_impl_1_uint_opt(CowlObjectType type, CowlAny *f1, ulib_uint val, CowlAny *opt) {
    CowlAny *fields[] = { f1 };
    return cowl_get_impl_uint(type, fields, val, opt);
}

COWL_RETAINED
COWL_INLINE
CowlAny *cowl_get_impl_1_uint(CowlObjectType type, CowlAny *f1, ulib_uint val) {
    return cowl_get_impl_1_uint_opt(type, f1, val, NULL);
}

COWL_RETAINED
COWL_INLINE
CowlAny *cowl_get_impl_2_uint_opt(CowlObjectType type, CowlAny *f1, CowlAny *f2, ulib_uint val,
                                  CowlAny *opt) {
    CowlAny *fields[] = { f1, f2 };
    return cowl_get_impl_uint(type, fields, val, opt);
}

COWL_RETAINED
COWL_INLINE
CowlAny *cowl_get_impl_2_uint(CowlObjectType type, CowlAny *f1, CowlAny *f2, ulib_uint val) {
    return cowl_get_impl_2_uint_opt(type, f1, f2, val, NULL);
}

COWL_API
COWL_RETAINED
CowlAnyEntity *cowl_entity_get_impl(CowlObjectType type, CowlIRI *iri);

COWL_API
COWL_RETAINED
CowlAnyEntity *cowl_entity_from_string_impl(CowlObjectType type, UString string);

COWL_API
void cowl_release_all_impl(CowlAny **objects);

COWL_API
CowlAny **cowl_get_fields(CowlAny *object, unsigned *count);

COWL_API
COWL_PURE
unsigned cowl_get_field_count(CowlAny *object);

COWL_API
COWL_PURE
CowlAny *cowl_get_field(CowlAny *object, unsigned index);

COWL_API
COWL_PURE
bool cowl_has_opt_field(CowlAny *object);

COWL_API
COWL_PURE
CowlAny *cowl_get_opt_field(CowlAny *object);

COWL_API
COWL_PURE
ulib_uint cowl_get_uint_field(CowlAny *object);

/// @endcond

COWL_END_DECLS

#endif // COWL_IMPL_H
