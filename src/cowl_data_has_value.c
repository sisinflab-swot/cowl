/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_has_value_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_hash_utils.h"
#include "cowl_literal.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlDataHasValue* cowl_data_has_value_alloc(CowlDataPropExp *prop, CowlLiteral *value) {
    CowlDataHasValue *restr = cowl_alloc(restr);
    if (!restr) return NULL;

    cowl_uint hash = cowl_hash_2(COWL_HASH_INIT_DATA_HAS_VALUE,
                                 cowl_data_prop_exp_hash(prop),
                                 cowl_literal_hash(value));

    *restr = (CowlDataHasValue) {
        .super = COWL_CLS_EXP_INIT(COWL_CET_DATA_HAS_VALUE, hash),
        .prop = cowl_data_prop_exp_retain(prop),
        .value = cowl_literal_retain(value)
    };

    return restr;
}

static void cowl_data_has_value_free(CowlDataHasValue *restr) {
    if (!restr) return;
    cowl_data_prop_exp_release(restr->prop);
    cowl_literal_release(restr->value);
    cowl_free(restr);
}

CowlDataHasValue* cowl_data_has_value_get(CowlDataPropExp *prop, CowlLiteral *value) {
    if (!(prop && value)) return NULL;
    return cowl_data_has_value_alloc(prop, value);
}

CowlDataHasValue* cowl_data_has_value_retain(CowlDataHasValue *restr) {
    return cowl_object_incr_ref(restr);
}

void cowl_data_has_value_release(CowlDataHasValue *restr) {
    if (restr && !cowl_object_decr_ref(restr)) {
        cowl_data_has_value_free(restr);
    }
}

CowlDataPropExp* cowl_data_has_value_get_prop(CowlDataHasValue *restr) {
    return restr->prop;
}

CowlLiteral* cowl_data_has_value_get_value(CowlDataHasValue *restr) {
    return restr->value;
}

CowlString* cowl_data_has_value_to_string(CowlDataHasValue *restr)
    COWL_TO_STRING_IMPL(data_has_value, restr)

bool cowl_data_has_value_equals(CowlDataHasValue *lhs, CowlDataHasValue *rhs) {
    return cowl_object_hash_equals(lhs, rhs) &&
           cowl_data_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_literal_equals(lhs->value, rhs->value);
}

cowl_uint cowl_data_has_value_hash(CowlDataHasValue *restr) {
    return cowl_object_hash_get(restr);
}

bool cowl_data_has_value_iterate_primitives(CowlDataHasValue *restr, CowlIterator *iter,
                                            CowlPrimitiveFlags flags) {
    return (cowl_data_prop_exp_iterate_primitives(restr->prop, iter, flags) &&
            cowl_literal_iterate_primitives(restr->value, iter, flags));
}
