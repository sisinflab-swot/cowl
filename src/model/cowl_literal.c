/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_literal_private.h"
#include "cowl_alloc.h"
#include "cowl_datatype.h"
#include "cowl_hash_utils.h"
#include "cowl_iterator_private.h"
#include "cowl_rdf_vocab.h"
#include "cowl_str_buf.h"
#include "cowl_string_private.h"

static CowlLiteral* cowl_literal_alloc(CowlDatatype *dt, CowlString *value, CowlString *lang) {
    CowlLiteral *literal = cowl_alloc(literal);

    if (!dt) dt = cowl_datatype_retain(cowl_rdf_vocab_get()->dt.plain_literal);
    if (!value) value = cowl_string_get_empty();

    cowl_uint_t hash = cowl_hash_3(COWL_HASH_INIT_LITERAL,
                                   cowl_datatype_hash(dt),
                                   cowl_string_hash(value),
                                   uhash_ptr_hash(lang));

    *literal = (CowlLiteral) {
        .super = COWL_HASH_OBJECT_INIT(hash),
        .dt = cowl_datatype_retain(dt),
        .value = cowl_string_retain(value),
        .lang = cowl_string_retain(lang)
    };

    return literal;
}

static void cowl_literal_free(CowlLiteral *literal) {
    if (!literal) return;
    cowl_datatype_release(literal->dt);
    cowl_string_release(literal->value);
    cowl_string_release(literal->lang);
    cowl_free(literal);
}

CowlLiteral* cowl_literal_get(CowlDatatype *dt, CowlString *value, CowlString *lang) {
    return cowl_literal_alloc(dt, value, cowl_string_get_intern(lang, false));
}

CowlLiteral* cowl_literal_get_raw(CowlDatatype *dt, CowlRawString value, CowlRawString lang) {

    if (!lang.length && value.length) {
        // The literal doesn't have a separate language tag, attempt to parse it from the value.
        cowl_uint_t lang_idx = cowl_raw_string_index_of(value, '@') + 1;

        if (lang_idx < value.length) {
            value = cowl_raw_string_init(value.cstring, lang_idx, false);
            lang = cowl_raw_string_init(value.cstring + lang_idx, value.length - lang_idx, false);
        }
    }

    CowlString *val_s = value.length ? cowl_string_get(value.cstring, value.length, true) : NULL;

    CowlString key = cowl_string_init(lang);
    CowlString *lang_s = cowl_string_get_intern(&key, true);

    return cowl_literal_alloc(dt, val_s, lang_s);
}

CowlLiteral* cowl_literal_retain(CowlLiteral *literal) {
    return cowl_object_retain(literal);
}

void cowl_literal_release(CowlLiteral *literal) {
    if (literal && !cowl_object_release(literal)) {
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

CowlString* cowl_literal_to_string(CowlLiteral *literal) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_literal(buf, literal);
    return cowl_str_buf_to_string(buf);
}

bool cowl_literal_equals(CowlLiteral *lhs, CowlLiteral *rhs) {
    return lhs->super.hash == rhs->super.hash &&
           lhs->lang == rhs->lang &&
           cowl_datatype_equals(lhs->dt, rhs->dt) &&
           cowl_string_equals(lhs->value, rhs->value);
}

cowl_uint_t cowl_literal_hash(CowlLiteral *literal) {
    return cowl_object_hash_get(literal);
}

bool cowl_literal_iterate_signature(CowlLiteral *literal, CowlEntityIterator *iter) {
    return cowl_iterate(iter, cowl_entity_wrap_datatype(literal->dt));
}
