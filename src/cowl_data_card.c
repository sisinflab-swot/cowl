/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_card_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_data_range.h"
#include "cowl_hash_utils.h"
#include "cowl_macros.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlDataCard* cowl_data_card_alloc(CowlClsExpType type, CowlDataPropExp *prop,
                                          CowlDataRange *range, cowl_uint cardinality) {
    CowlDataCard *restr = cowl_alloc(restr);
    if (!restr) return NULL;

    cowl_uint hash;

    if (range) {
        hash = cowl_hash_4(COWL_HASH_INIT_DATA_CARD, type, cardinality,
                           cowl_data_prop_exp_hash(prop), cowl_data_range_hash(range));
        cowl_data_range_retain(range);
    } else {
        hash = cowl_hash_3(COWL_HASH_INIT_DATA_CARD, type, cardinality,
                           cowl_data_prop_exp_hash(prop));
    }

    *restr = (CowlDataCard) {
        .super = COWL_CLS_EXP_INIT(type, hash),
        .prop = cowl_data_prop_exp_retain(prop),
        .range = range,
        .cardinality = cardinality
    };

    return restr;
}

static void cowl_data_card_free(CowlDataCard *restr) {
    if (!restr) return;
    cowl_data_prop_exp_release(restr->prop);
    cowl_data_range_release(restr->range);
    cowl_free(restr);
}

CowlDataCard* cowl_data_card_get(CowlCardType type, CowlDataPropExp *prop,
                                 CowlDataRange *range, cowl_uint cardinality) {
    if (!(prop && cowl_enum_value_is_valid(CT, type))) return NULL;
    return cowl_data_card_alloc(COWL_CET_DATA_MIN_CARD + type, prop, range, cardinality);
}

CowlDataCard* cowl_data_card_retain(CowlDataCard *restr) {
    return cowl_object_retain(restr);
}

void cowl_data_card_release(CowlDataCard *restr) {
    if (restr && !cowl_object_release(restr)) {
        cowl_data_card_free(restr);
    }
}

CowlCardType cowl_data_card_get_type(CowlDataCard *restr) {
    return (CowlCardType)(cowl_get_type(restr) - COWL_OT_CE_DATA_MIN_CARD);
}

CowlDataPropExp* cowl_data_card_get_prop(CowlDataCard *restr) {
    return restr->prop;
}

CowlDataRange* cowl_data_card_get_range(CowlDataCard *restr) {
    return restr->range;
}

cowl_uint cowl_data_card_get_cardinality(CowlDataCard *restr) {
    return restr->cardinality;
}

CowlString* cowl_data_card_to_string(CowlDataCard *restr)
    COWL_TO_STRING_IMPL(data_card, restr)

bool cowl_data_card_equals(CowlDataCard *lhs, CowlDataCard *rhs) {
    if (lhs->cardinality != rhs->cardinality) return false;
    if (!cowl_hash_object_equals_impl(lhs, rhs)) return false;
    if (!cowl_data_prop_exp_equals(lhs->prop, rhs->prop)) return false;
    if (lhs->range == rhs->range) return true;
    if (lhs->range && rhs->range) return cowl_data_range_equals(lhs->range, rhs->range);
    return false;
}

cowl_uint cowl_data_card_hash(CowlDataCard *restr) {
    return cowl_object_hash_get(restr);
}

bool cowl_data_card_iterate_primitives(CowlDataCard *restr, CowlIterator *iter,
                                       CowlPrimitiveFlags flags) {
    if (!cowl_data_prop_exp_iterate_primitives(restr->prop, iter, flags)) return false;
    if (restr->range && !cowl_data_range_iterate_primitives(restr->range, iter, flags)) return false;
    return true;
}
