/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_annot_value.h"
#include "cowl_anon_ind.h"
#include "cowl_iri.h"
#include "cowl_literal.h"
#include "cowl_object_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlAnnotValue* cowl_annot_value_retain(CowlAnnotValue *value) {
    return cowl_object_retain(value);
}

void cowl_annot_value_release(CowlAnnotValue *value) {

#define GEN_RELEASE(UC, LC) cowl_##LC##_release((Cowl##UC *)value); break

    switch (cowl_annot_value_get_type(value)) {
        case COWL_AVT_IRI: GEN_RELEASE(IRI, iri);
        case COWL_AVT_ANON_IND: GEN_RELEASE(AnonInd, anon_ind);
        case COWL_AVT_LITERAL: GEN_RELEASE(Literal, literal);
        default: break;
    }
}

CowlAnnotValueType cowl_annot_value_get_type(CowlAnnotValue *value) {
    switch (cowl_get_type(value)) {
        case COWL_OT_IRI: return COWL_AVT_IRI;
        case COWL_OT_I_ANONYMOUS: return COWL_AVT_ANON_IND;
        default: return COWL_AVT_LITERAL;
    }
}

CowlString* cowl_annot_value_to_string(CowlAnnotValue *value)
    COWL_TO_STRING_IMPL(annot_value, value)

bool cowl_annot_value_equals(CowlAnnotValue *lhs, CowlAnnotValue *rhs) {
    if (!cowl_object_equals_impl(lhs, rhs)) return false;

#define GEN_EQUALS(UC, LC) return cowl_##LC##_equals((Cowl##UC *)lhs, (Cowl##UC *)rhs)

    switch (cowl_annot_value_get_type(lhs)) {
        case COWL_AVT_IRI: GEN_EQUALS(IRI, iri);
        case COWL_AVT_ANON_IND: GEN_EQUALS(AnonInd, anon_ind);
        case COWL_AVT_LITERAL: GEN_EQUALS(Literal, literal);
        default: return false;
    }
}

cowl_uint_t cowl_annot_value_hash(CowlAnnotValue *value) {

#define GEN_HASH(UC, LC) return cowl_##LC##_hash((Cowl##UC *)value)

    switch (cowl_annot_value_get_type(value)) {
        case COWL_AVT_IRI: GEN_HASH(IRI, iri);
        case COWL_AVT_ANON_IND: GEN_HASH(AnonInd, anon_ind);
        case COWL_AVT_LITERAL: GEN_HASH(Literal, literal);
        default: return 0;
    }
}

bool cowl_annot_value_iterate(CowlAnnotValue *value, CowlIterator *iter) {

#define GEN_ITER(UC, LC) return cowl_##LC##_iterate((Cowl##UC *)value, iter)

    switch (cowl_annot_value_get_type(value)) {
        case COWL_AVT_ANON_IND: GEN_ITER(AnonInd, anon_ind);
        case COWL_AVT_LITERAL: GEN_ITER(Literal, literal);
        default: return true;
    }
}
