/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
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
#include "cowl_xsd_vocab.h"

static inline bool cowl_literal_is_lang_string(CowlLiteral *literal) {
    return cowl_object_bit_get(literal);
}

CowlLiteral* cowl_literal(CowlDatatype *dt, CowlString *value, CowlString *lang) {
    if (!value) return NULL;
    CowlRDFVocab const *v = cowl_rdf_vocab();

    if (lang) {
        if (cowl_string_get_length(lang)) {
            if (dt && dt != v->dt.plain_literal && dt != v->dt.lang_string) return NULL;
            if (!(lang = cowl_string_intern(lang))) return NULL;
            dt = NULL;
        } else {
            lang = NULL;
        }
    }

    if (!lang && (!dt || dt == v->dt.plain_literal)) dt = cowl_xsd_vocab()->dt.string;

    CowlComposite *literal = ulib_malloc(sizeof(*literal) + 2 * sizeof(*literal->data));
    if (!literal) return NULL;

    literal->super = COWL_OBJECT_BIT_INIT(COWL_OT_LITERAL, lang);
    literal->data[0] = cowl_string_retain(value);

    if (lang) {
        literal->data[1] = cowl_string_retain(lang);
    } else {
        literal->data[1] = cowl_datatype_retain(dt);
    }

    return (CowlLiteral *)literal;
}

CowlLiteral* cowl_literal_from_string(UString dt, UString value, UString lang) {
    CowlDatatype *cdt = cowl_datatype_from_string(dt);
    CowlString *cvalue = cowl_string(ustring_dup(value));
    CowlString *clang = cowl_string_get_intern(lang);
    CowlLiteral *literal = cowl_literal(cdt, cvalue, clang);
    cowl_datatype_release(cdt);
    cowl_string_release(cvalue);
    cowl_string_release(clang);
    return literal;
}

CowlLiteral* cowl_literal_raw(CowlDatatype *dt, UString value, UString lang) {
    ulib_uint val_len = ustring_length(value), lang_len = ustring_length(lang);
    char const *val_str = ustring_data(value), *lang_str = ustring_data(lang);

    if (!lang_len && val_len) {
        CowlRDFVocab const *v = cowl_rdf_vocab();
        if (dt == v->dt.lang_string || dt == v->dt.plain_literal) {
            // Attempt to parse the language tag from the value.
            ulib_uint lang_idx = ustring_index_of_last(value, '@') + 1;

            if (lang_idx < val_len) {
                val_len = lang_idx;
                lang_str = val_str + lang_idx;
                lang_len = val_len - lang_idx;
            }
        }
    }

    CowlString *val_s = val_len ? cowl_string(ustring_copy(val_str, val_len)) : cowl_string_empty();
    CowlString *lang_s = lang_len ? cowl_string_get_intern(ustring_wrap(lang_str, lang_len)) : NULL;
    CowlLiteral *literal = cowl_literal(dt, val_s, lang_s);

    cowl_string_release(lang_s);
    cowl_string_release(val_s);

    return literal;
}

void cowl_literal_release(CowlLiteral *literal) {
    if (literal && !cowl_object_decr_ref(literal)) {
        cowl_string_release(cowl_literal_get_value(literal));
        if (cowl_literal_is_lang_string(literal)) {
            cowl_string_release(cowl_literal_get_lang(literal));
        } else {
            cowl_datatype_release(cowl_literal_get_datatype(literal));
        }
        ulib_free(literal);
    }
}

CowlDatatype* cowl_literal_get_datatype(CowlLiteral *literal) {
    if (cowl_literal_is_lang_string(literal)) return cowl_rdf_vocab()->dt.lang_string;
    return cowl_get_field(literal, 1);
}

CowlString* cowl_literal_get_value(CowlLiteral *literal) {
    return cowl_get_field(literal, 0);
}

CowlString* cowl_literal_get_lang(CowlLiteral *literal) {
    if (cowl_literal_is_lang_string(literal)) return cowl_get_field(literal, 1);
    return NULL;
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
