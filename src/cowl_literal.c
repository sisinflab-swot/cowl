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
#include "cowl_object_private.h"
#include "cowl_string_private.h"
#include "cowl_rdf_vocab.h"

static inline bool cowl_literal_has_dt(CowlLiteral *literal) {
    return cowl_object_bit_get(literal);
}

static CowlLiteral* cowl_literal_alloc(CowlDatatype *dt, CowlString *value, CowlString *lang) {
    CowlComposite *literal = ulib_malloc(sizeof(*literal) + 2 * sizeof(*literal->data));
    if (!literal) return NULL;
    if (!dt && !lang) dt = cowl_rdf_vocab_get()->dt.plain_literal;

    literal->super = COWL_OBJECT_BIT_INIT(COWL_OT_LITERAL, dt);
    literal->data[0] = cowl_string_retain(value);

    if (dt) {
        literal->data[1] = cowl_datatype_retain(dt);
    } else {
        literal->data[1] = cowl_string_retain(lang);
    }

    return (CowlLiteral *)literal;
}

static void cowl_literal_free(CowlLiteral *literal) {
    cowl_string_release(cowl_literal_get_value(literal));
    if (cowl_literal_has_dt(literal)) {
        cowl_datatype_release(cowl_literal_get_datatype(literal));
    } else {
        cowl_string_release(cowl_literal_get_lang(literal));
    }
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

    CowlString *val_s = val_len ? cowl_string_get(ustring_copy(val_str, val_len)) : cowl_string_get_empty();
    CowlString *lang_s = lang_len ? cowl_string_get(ustring_copy(lang_str, lang_len)) : NULL;
    CowlLiteral *literal = cowl_literal_alloc(dt, val_s, cowl_string_intern(lang_s));

    cowl_string_release(lang_s);
    cowl_string_release(val_s);

    return literal;
}

void cowl_literal_release(CowlLiteral *literal) {
    if (literal && !cowl_object_decr_ref(literal)) {
        cowl_literal_free(literal);
    }
}

CowlDatatype* cowl_literal_get_datatype(CowlLiteral *literal) {
    if (cowl_literal_has_dt(literal)) return cowl_get_field(literal, 1);
    return cowl_rdf_vocab_get()->dt.plain_literal;
}

CowlString* cowl_literal_get_value(CowlLiteral *literal) {
    return cowl_get_field(literal, 0);
}

CowlString* cowl_literal_get_lang(CowlLiteral *literal) {
    if (cowl_literal_has_dt(literal)) return NULL;
    return cowl_get_field(literal, 1);
}

bool cowl_literal_equals(CowlLiteral *lhs, CowlLiteral *rhs) {
    return cowl_get_field(lhs, 1) == cowl_get_field(rhs, 1) &&
           cowl_string_equals(cowl_literal_get_value(lhs), cowl_literal_get_value(rhs));
}

ulib_uint cowl_literal_hash(CowlLiteral *literal) {
    ulib_uint hash = uhash_combine_hash(6151U, COWL_OT_LITERAL);
    hash = uhash_combine_hash(hash, cowl_string_hash(cowl_literal_get_value(literal)));
    hash = uhash_combine_hash(hash, uhash_ptr_hash(cowl_get_field(literal, 1)));
    return hash;
}

bool cowl_literal_iterate_primitives(CowlLiteral *literal, CowlPrimitiveFlags flags,
                                     CowlIterator *iter) {
    return cowl_datatype_iterate_primitives(cowl_literal_get_datatype(literal), flags, iter);
}
