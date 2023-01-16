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
    UString const *raw_value = cowl_string_get_raw(value);
    char const *val_str = ustring_data(*raw_value);
    ulib_uint val_len = ustring_length(*raw_value);
    ulib_uint lang_idx = ustring_index_of_last(*raw_value, '@') + 1;

    *lang = NULL;

    if (lang_idx < val_len) {
        value = cowl_string_opt(ustring_wrap(val_str, lang_idx), COWL_SO_COPY);
        if (!value) return NULL;

        UString const raw_lang = ustring_wrap(val_str + lang_idx, val_len - lang_idx);
        *lang = cowl_string_opt(raw_lang, COWL_SO_COPY | COWL_SO_INTERN);

        if (!(*lang)) {
            cowl_string_release(value);
            return NULL;
        }
    }

    return value;
}

CowlLiteral *cowl_literal(CowlDatatype *dt, CowlString *value, CowlString *lang) {
    if (!value) return NULL;
    CowlRDFVocab const *v = cowl_rdf_vocab();

    if (lang && !cowl_string_get_length(lang)) lang = NULL;

    if (lang) {
        if (!(lang = cowl_string_intern(lang))) return NULL;
        if (dt) {
            if (dt == v->dt.lang_string || dt == v->dt.plain_literal) {
                dt = NULL;
            } else {
                // Literal with language tag but incorrect datatype.
                return NULL;
            }
        }
    } else if (dt == v->dt.lang_string || dt == v->dt.plain_literal) {
        // Attempt to parse the language tag from the value.
        if (!(value = parse_lang(value, &lang))) return NULL;
        dt = NULL;
    }

    if (!(lang || dt)) dt = cowl_xsd_vocab()->dt.string;

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

CowlLiteral *cowl_literal_from_string(UString dt, UString value, UString lang) {
    CowlDatatype *cdt = cowl_datatype_from_string(dt);
    CowlString *cvalue = cowl_string_opt(value, COWL_SO_COPY);
    CowlString *clang = cowl_string_opt(lang, COWL_SO_COPY | COWL_SO_INTERN);
    CowlLiteral *literal = cowl_literal(cdt, cvalue, clang);
    cowl_datatype_release(cdt);
    cowl_string_release(cvalue);
    cowl_string_release(clang);
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
    ulib_uint hash = uhash_combine_hash(6151U, COWL_OT_LITERAL);
    hash = uhash_combine_hash(hash, cowl_string_hash(cowl_literal_get_value(literal)));
    hash = uhash_combine_hash(hash, uhash_ptr_hash(cowl_get_field(literal, 1)));
    return hash;
}

bool cowl_literal_iterate_primitives(CowlLiteral *literal, CowlPrimitiveFlags flags,
                                     CowlIterator *iter) {
    return cowl_datatype_iterate_primitives(cowl_literal_get_datatype(literal), flags, iter);
}
