/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_literal_private.h"
#include "cowl_datatype.h"
#include "cowl_hash_utils.h"
#include "cowl_iri.h"
#include "cowl_iterator_private.h"
#include "cowl_rdf_vocab.h"
#include "cowl_string.h"
#include "cowl_str_buf.h"

static CowlLiteral* cowl_literal_alloc(CowlDatatype *dt, CowlString *value, CowlString *lang) {
    cowl_uint_t hash = cowl_hash_3(COWL_HASH_INIT_LITERAL,
                                   cowl_datatype_hash(dt),
                                   cowl_string_hash(value),
                                   cowl_string_hash(lang));

    CowlLiteral init = COWL_LITERAL_INIT(
        cowl_datatype_retain(dt),
        cowl_string_retain(value),
        cowl_string_retain(lang),
        hash
    );

    cowl_struct(CowlLiteral) *literal = malloc(sizeof(*literal));
    memcpy(literal, &init, sizeof(*literal));
    return literal;
}

static void cowl_literal_free(CowlLiteral *literal) {
    if (!literal) return;
    cowl_datatype_release(literal->dt);
    cowl_string_release(literal->value);
    cowl_string_release(literal->lang);
    free((void *)literal);
}

CowlLiteral* cowl_literal_get(CowlDatatype *datatype, CowlString *literal, CowlString *lang) {
    if (!datatype) datatype = cowl_datatype_retain(cowl_rdf_vocab_get()->dt.plain_literal);
    if (!literal) literal = cowl_string_get_empty();
    if (!lang) lang = cowl_string_get_empty();
    return cowl_literal_alloc(datatype, literal, lang);
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
           cowl_datatype_equals(lhs->dt, rhs->dt) &&
           cowl_string_equals(lhs->value, rhs->value) &&
           cowl_string_equals(lhs->lang, rhs->lang);
}

cowl_uint_t cowl_literal_hash(CowlLiteral *literal) {
    return cowl_object_hash_get(literal);
}

bool cowl_literal_iterate_signature(CowlLiteral *literal, CowlEntityIterator *iter) {
    return cowl_iterate(iter, cowl_entity_wrap_datatype(literal->dt));
}
