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
#include "cowl_datatype.h"
#include "cowl_object_private.h"
#include "cowl_rdf_vocab.h"
#include "cowl_string_private.h"
#include "cowl_xsd_vocab.h"

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

static CowlLiteral *cowl_literal_alloc(CowlDatatype *dt, CowlString *value, CowlString *lang) {
    CowlComposite *literal = ulib_malloc(sizeof(*literal) + 2 * sizeof(*literal->fields));
    if (!literal) return NULL;

    literal->super = COWL_OBJECT_BIT_INIT(COWL_OT_LITERAL, lang);
    literal->fields[0].obj = value;

    if (lang) {
        literal->fields[1].obj = lang;
    } else {
        literal->fields[1].obj = dt;
    }

    cowl_retain(literal->fields[0].obj);
    cowl_retain(literal->fields[1].obj);

    return (CowlLiteral *)literal;
}

void cowl_literal_free(CowlLiteral *literal) {
    cowl_release(cowl_literal_get_value(literal));
    if (cowl_literal_is_lang_string(literal)) {
        cowl_release(cowl_literal_get_lang(literal));
    } else {
        cowl_release(cowl_literal_get_datatype(literal));
    }
    ulib_free(literal);
}

CowlLiteral *cowl_literal(CowlDatatype *dt, CowlString *value, CowlString *lang) {
    if (!value) return NULL;
    if (lang && !cowl_string_get_length(lang)) lang = NULL;

    CowlLiteral *ret = NULL;
    bool release_value = false, release_lang = false;

    if (lang) {
        // Validate datatype.
        if (dt && !is_lang_datatype(dt)) goto end;
        if (!(lang = internalize_lang(lang))) goto end;
        release_lang = true;
        dt = NULL;
    } else if (is_lang_datatype(dt)) {
        // Attempt to parse the language tag from the value.
        if (!(value = parse_lang(value, &lang))) goto end;
        release_value = release_lang = true;
        dt = NULL;
    }

    if (!(lang || dt)) dt = cowl_xsd_vocab()->dt.string;
    ret = cowl_literal_alloc(dt, value, lang);

end:
    if (release_value) cowl_release(value);
    if (release_lang) cowl_release(lang);

    return ret;
}

CowlLiteral *cowl_literal_from_string(UString dt, UString value, UString lang) {
    CowlDatatype *cdt = cowl_datatype_from_string(dt);
    CowlString *cvalue = cowl_string_opt(value, COWL_SO_COPY);
    CowlString *clang = cowl_string_opt(lang, COWL_SO_COPY | COWL_SO_INTERN);
    CowlLiteral *literal = cowl_literal(cdt, cvalue, clang);
    cowl_release(cdt);
    cowl_release(cvalue);
    cowl_release(clang);
    return literal;
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

bool cowl_literal_iterate_primitives(CowlLiteral *literal, CowlPrimitiveFlags flags,
                                     CowlIterator *iter) {
    return cowl_iterate_primitives(cowl_literal_get_datatype(literal), flags, iter);
}
