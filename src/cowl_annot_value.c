/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_annot_value.h"
#include "cowl_object_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlAnnotValue* cowl_annot_value_retain(CowlAnnotValue *value) {
    return cowl_object_incr_ref(value);
}

void cowl_annot_value_release(CowlAnnotValue *value) {
    cowl_object_release((CowlObject *)value);
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
    return cowl_object_equals((CowlObject *)lhs, (CowlObject *)rhs);
}

cowl_uint cowl_annot_value_hash(CowlAnnotValue *value) {
    return cowl_object_hash((CowlObject *)value);
}

bool cowl_annot_value_iterate_primitives(CowlAnnotValue *value, CowlPrimitiveFlags flags,
                                         CowlIterator *iter) {
    return cowl_object_iterate_primitives((CowlObject *)value, flags, iter);
}
