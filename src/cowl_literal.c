/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_literal_private.h"
#include "cowl_datatype.h"
#include "cowl_hash_utils.h"
#include "cowl_rdf_vocab.h"
#include "cowl_string_private.h"
#include "cowl_template.h"

static CowlLiteral* cowl_literal_alloc(CowlDatatype *dt, CowlString *value, CowlString *lang) {
    CowlLiteral *literal = ulib_alloc(literal);
    if (!literal) return NULL;

    dt = cowl_datatype_retain(dt ? dt : cowl_rdf_vocab_get()->dt.plain_literal);
    value = value ? cowl_string_retain(value) : cowl_string_get_empty();
    lang = lang ? cowl_string_retain(lang) : cowl_string_get_empty();

    ulib_uint hash = cowl_hash_3(COWL_HASH_INIT_LITERAL,
                                 cowl_datatype_hash(dt),
                                 cowl_string_hash(value),
                                 uhash_ptr_hash(lang));

    *literal = (CowlLiteral) {
        .super = COWL_HASH_OBJECT_INIT(COWL_OT_LITERAL, hash),
        .dt = dt,
        .value = value,
        .lang = lang
    };

    return literal;
}

static void cowl_literal_free(CowlLiteral *literal) {
    if (!literal) return;
    cowl_datatype_release(literal->dt);
    cowl_string_release(literal->value);
    cowl_string_release(literal->lang);
    ulib_free(literal);
}

CowlLiteral* cowl_literal_get(CowlDatatype *dt, CowlString *value, CowlString *lang) {
    if (!value) return NULL;
    return cowl_literal_alloc(dt, value, cowl_string_intern(lang));
}

CowlLiteral* cowl_literal_get_raw(CowlDatatype *dt, UString value, UString lang) {
    ulib_uint val_len = ustring_length(value), lang_len = ustring_length(lang);
    char const *val_str = ustring_data(value), *lang_str = ustring_data(lang);

    if (!lang_len && val_len) {
        // The literal doesn't have a separate language tag, attempt to parse it from the value.
        ulib_uint lang_idx = ustring_index_of(value, '@') + 1;

        if (lang_idx < val_len) {
            val_len = lang_idx;
            lang_str = val_str + lang_idx;
            lang_len = val_len - lang_idx;
        }
    }

    CowlString *val_s = val_len ? cowl_string_get(ustring_copy(val_str, val_len)) : NULL;
    CowlString *lang_s = lang_len ? cowl_string_get(ustring_copy(lang_str, lang_len)) : NULL;
    CowlLiteral *literal = cowl_literal_alloc(dt, val_s, cowl_string_intern(lang_s));

    cowl_string_release(lang_s);
    cowl_string_release(val_s);

    return literal;
}

CowlLiteral* cowl_literal_retain(CowlLiteral *literal) {
    return cowl_object_incr_ref(literal);
}

void cowl_literal_release(CowlLiteral *literal) {
    if (literal && !cowl_object_decr_ref(literal)) {
        cowl_literal_free(literal);
    }
}

CowlDatatype* cowl_literal_get_datatype(CowlLiteral *literal) {
    return literal->dt;
}

CowlString* cowl_literal_get_value(CowlLiteral *literal) {
    return literal->value;
}

CowlString* cowl_literal_get_lang(CowlLiteral *literal) {
    return literal->lang;
}

CowlString* cowl_literal_to_string(CowlLiteral *literal)
    COWL_TO_STRING_IMPL(literal, literal)

bool cowl_literal_equals(CowlLiteral *lhs, CowlLiteral *rhs) {
    return cowl_object_hash_equals(lhs, rhs) &&
           lhs->lang == rhs->lang &&
           cowl_datatype_equals(lhs->dt, rhs->dt) &&
           cowl_string_equals(lhs->value, rhs->value);
}

ulib_uint cowl_literal_hash(CowlLiteral *literal) {
    return cowl_object_hash_get(literal);
}

bool cowl_literal_iterate_primitives(CowlLiteral *literal, CowlPrimitiveFlags flags,
                                     CowlIterator *iter) {
    return cowl_datatype_iterate_primitives(literal->dt, flags, iter);
}
