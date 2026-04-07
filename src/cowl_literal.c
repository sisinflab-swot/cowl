/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_literal.h"
#include "cowl_any.h"
#include "cowl_datatype.h"
#include "cowl_impl.h"
#include "cowl_iterator.h"
#include "cowl_literal_private.h"
#include "cowl_object.h"
#include "cowl_object_private.h"
#include "cowl_object_type.h"
#include "cowl_primitive_flags.h"
#include "cowl_rdf_vocab.h"
#include "cowl_ret.h"
#include "cowl_string.h"
#include "cowl_string_private.h"
#include "cowl_xsd_vocab.h"
#include "ulib.h"
#include <stddef.h>

static inline bool cowl_literal_is_lang_string(CowlLiteral *literal) {
    return cowl_object_bit_get(literal);
}

static CowlString *parse_lang(CowlString *value, CowlString **lang) {
    *lang = NULL;

    UString const *raw_value = cowl_string_get_raw(value);
    char const *val_str = ustring_data(*raw_value);
    ulib_uint val_len = ustring_length(*raw_value);
    ulib_uint lang_idx = ustring_index_of_last(*raw_value, '@') + 1;
    if (lang_idx >= val_len) return cowl_retain(value);

    CowlString *new_val = cowl_string_opt(ustring_wrap(val_str, lang_idx - 1), COWL_SO_COPY);
    if (!new_val) goto err;

    UString raw_lang;
    ulib_uint const lang_len = val_len - lang_idx;
    char *buf = ustring(&raw_lang, lang_len);
    if (!buf) goto err;

    ulib_str_to_lower(buf, val_str + lang_idx, lang_len);
    *lang = cowl_string_opt(raw_lang, COWL_SO_INTERN);
    if (!(*lang)) goto err;

    return new_val;

err:
    cowl_release(new_val);
    return NULL;
}

static CowlString *internalize_lang(CowlString *lang) {
    UString const *raw_lang = cowl_string_get_raw(lang);

    if (ustring_is_lower(*raw_lang)) {
        if (!(lang = cowl_string_intern(lang))) return NULL;
        cowl_retain(lang);
    } else {
        // Language tag must be normalized to lowercase.
        UString new_lang = ustring_to_lower(*raw_lang);
        if (ustring_is_null(new_lang)) return NULL;
        lang = cowl_string_opt(new_lang, COWL_SO_INTERN);
    }

    return lang;
}

static inline bool is_lang_datatype(CowlDatatype *dt) {
    CowlRDFVocab const *v = cowl_rdf_vocab();
    return dt == v->dt.lang_string || dt == v->dt.plain_literal;
}

static CowlLiteral *cowl_literal_alloc(CowlString *value, CowlAny *dt_or_lang, bool is_lang) {
    CowlLiteral *literal = cowl_get_impl_2(COWL_OT_LITERAL, value, dt_or_lang);
    if (is_lang) cowl_object_bit_set(literal);
    return literal;
}

static CowlLiteral *cowl_literal_string_alloc(CowlString *value) {
    return cowl_literal_alloc(value, cowl_xsd_vocab()->dt.string, false);
}

static CowlLiteral *cowl_literal_lang_alloc(CowlString *value, CowlString *lang) {
    if (cowl_string_get_length(lang) == 0) return cowl_literal_string_alloc(value);
    if (!(lang = internalize_lang(lang))) return NULL;
    CowlLiteral *ret = cowl_literal_alloc(value, lang, true);
    cowl_release(lang);
    return ret;
}

static CowlLiteral *cowl_literal_parse_lang_alloc(CowlString *value) {
    CowlString *lang;
    if (!(value = parse_lang(value, &lang))) return NULL;
    CowlLiteral *ret = cowl_literal_alloc(value, lang, true);
    cowl_release(value);
    cowl_release(lang);
    return ret;
}

static CowlLiteral *cowl_literal_typed_alloc(CowlString *value, CowlDatatype *dt) {
    return cowl_literal_alloc(value, dt, false);
}

void cowl_literal_free(CowlLiteral *literal) {
    cowl_release(cowl_get_field(literal, 0));
    cowl_release(cowl_get_field(literal, 1));
    ulib_free(literal);
}

CowlLiteral *cowl_literal(CowlString *value, CowlAny *dt_or_lang) {
    if (!value) return NULL;
    if (!dt_or_lang) return cowl_literal_string_alloc(value);
    bool is_lang = cowl_get_type(dt_or_lang) == COWL_OT_STRING;
    if (is_lang) return cowl_literal_lang_alloc(value, dt_or_lang);
    if (is_lang_datatype(dt_or_lang)) return cowl_literal_parse_lang_alloc(value);
    return cowl_literal_typed_alloc(value, dt_or_lang);
}

CowlLiteral *cowl_literal_plain(UString value) {
    CowlString *cvalue = cowl_string_opt(value, COWL_SO_COPY);
    if (!cvalue) return NULL;
    CowlLiteral *literal = cowl_literal_string_alloc(cvalue);
    cowl_release(cvalue);
    return literal;
}

CowlLiteral *cowl_literal_typed(UString value, CowlDatatype *dt) {
    CowlString *cvalue = cowl_string_opt(value, COWL_SO_COPY);
    if (!cvalue) return NULL;
    CowlLiteral *literal = cowl_literal_typed_alloc(cvalue, dt);
    cowl_release(cvalue);
    return literal;
}

CowlLiteral *cowl_literal_lang(UString value, UString lang) {
    CowlLiteral *ret = NULL;
    CowlString *cvalue = NULL;
    CowlString *clang = NULL;

    cvalue = cowl_string_opt(value, COWL_SO_COPY);
    if (!cvalue) goto end;
    clang = cowl_string_opt(lang, COWL_SO_COPY | COWL_SO_INTERN);
    if (!clang) goto end;

    ret = cowl_literal_lang_alloc(cvalue, clang);

end:
    cowl_release(cvalue);
    cowl_release(clang);
    return ret;
}

CowlDatatype *cowl_literal_get_datatype(CowlLiteral *literal) {
    if (cowl_literal_is_lang_string(literal)) return cowl_rdf_vocab()->dt.lang_string;
    return cowl_get_field(literal, 1);
}

CowlString *cowl_literal_get_value(CowlLiteral *literal) {
    return cowl_get_field(literal, 0);
}

CowlString *cowl_literal_get_lang(CowlLiteral *literal) {
    if (cowl_literal_is_lang_string(literal)) return cowl_get_field(literal, 1);
    return NULL;
}

bool cowl_literal_equals(CowlLiteral *lhs, CowlLiteral *rhs) {
    return cowl_get_field(lhs, 1) == cowl_get_field(rhs, 1) &&
           cowl_string_equals(cowl_literal_get_value(lhs), cowl_literal_get_value(rhs));
}

ulib_uint cowl_literal_hash(CowlLiteral *literal) {
    ulib_uint hash = ulib_hash_combine(6151U, COWL_OT_LITERAL);
    hash = ulib_hash_combine(hash, cowl_string_hash(cowl_literal_get_value(literal)));
    hash = ulib_hash_combine(hash, ulib_hash_alloc_ptr(cowl_get_field(literal, 1)));
    return hash;
}

cowl_ret cowl_literal_iterate_primitives(CowlLiteral *literal, CowlPrimitiveFlags flags,
                                         CowlIterator *iter) {
    return cowl_iterate_primitives(cowl_literal_get_datatype(literal), flags, iter);
}
