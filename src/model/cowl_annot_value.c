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
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlAnnotValue cowl_annot_value_retain(CowlAnnotValue value) {

#define GEN_CASE_RETAIN(CET, PREFIX, FIELD) \
    case CET: PREFIX##_retain(value.FIELD); break

    switch (value.type) {

        GEN_CASE_RETAIN(COWL_AVT_IRI, cowl_iri, iri);
        GEN_CASE_RETAIN(COWL_AVT_ANON_IND, cowl_anon_ind, anon_ind);
        GEN_CASE_RETAIN(COWL_AVT_LITERAL, cowl_literal, literal);

        default:
            break;
    }

    return value;
}

void cowl_annot_value_release(CowlAnnotValue value) {

#define GEN_CASE_RELEASE(CET, PREFIX, FIELD) \
    case CET: PREFIX##_release(value.FIELD); break

    switch (value.type) {

        GEN_CASE_RELEASE(COWL_AVT_IRI, cowl_iri, iri);
        GEN_CASE_RELEASE(COWL_AVT_ANON_IND, cowl_anon_ind, anon_ind);
        GEN_CASE_RELEASE(COWL_AVT_LITERAL, cowl_literal, literal);

        default:
            break;
    }
}

CowlString* cowl_annot_value_to_string(CowlAnnotValue value)
    COWL_TO_STRING_IMPL(annot_value, value)

bool cowl_annot_value_equals(CowlAnnotValue lhs, CowlAnnotValue rhs) {
    if (rhs.type != lhs.type) return false;

#define GEN_CASE_EQUALS(CET, PREFIX, FIELD) \
    case CET: return PREFIX##_equals(lhs.FIELD, rhs.FIELD)

    switch (lhs.type) {

        GEN_CASE_EQUALS(COWL_AVT_IRI, cowl_iri, iri);
        GEN_CASE_EQUALS(COWL_AVT_ANON_IND, cowl_anon_ind, anon_ind);
        GEN_CASE_EQUALS(COWL_AVT_LITERAL, cowl_literal, literal);

        default:
            return false;
    }
}

cowl_uint_t cowl_annot_value_hash(CowlAnnotValue value) {

#define GEN_CASE_HASH(CET, PREFIX, FIELD) \
    case CET: return PREFIX##_hash(value.FIELD)

    switch (value.type) {

        GEN_CASE_HASH(COWL_AVT_IRI, cowl_iri, iri);
        GEN_CASE_HASH(COWL_AVT_ANON_IND, cowl_anon_ind, anon_ind);
        GEN_CASE_HASH(COWL_AVT_LITERAL, cowl_literal, literal);

        default:
            return 0;
    }
}

bool cowl_annot_value_iterate_signature(CowlAnnotValue value, CowlEntityIterator *iter) {
    if (value.type != COWL_AVT_LITERAL) return true;
    return cowl_literal_iterate_signature(value.literal, iter);
}

bool cowl_annot_value_iterate_primitives(CowlAnnotValue value, CowlPrimitiveIterator *iter) {

#define GEN_CASE_PRIM(CAT, FIELD) \
    case CAT: return cowl_##FIELD##_iterate_primitives(value.FIELD, iter)

    switch (value.type) {
        GEN_CASE_PRIM(COWL_AVT_LITERAL, literal);
        GEN_CASE_PRIM(COWL_AVT_ANON_IND, anon_ind);
        default: return true;
    }
}
