/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_quant_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_data_range.h"
#include "cowl_hash_utils.h"
#include "cowl_macros.h"
#include "cowl_template.h"

static CowlDataQuant* cowl_data_quant_alloc(CowlClsExpType type, CowlDataPropExp *prop,
                                            CowlDataRange *range) {
    CowlDataQuant *restr = ulib_alloc(restr);
    if (!restr) return NULL;

    ulib_uint hash = cowl_hash_3(COWL_HASH_INIT_DATA_QUANT, type,
                                 cowl_data_prop_exp_hash(prop),
                                 cowl_data_range_hash(range));

    *restr = (CowlDataQuant) {
        .super = COWL_CLS_EXP_INIT(type, hash),
        .prop = cowl_data_prop_exp_retain(prop),
        .range = cowl_data_range_retain(range)
    };

    return restr;
}

static void cowl_data_quant_free(CowlDataQuant *restr) {
    cowl_data_prop_exp_release(restr->prop);
    cowl_data_range_release(restr->range);
    ulib_free(restr);
}

CowlDataQuant* cowl_data_quant_get(CowlQuantType type, CowlDataPropExp *prop,
                                   CowlDataRange *range) {
    if (!(prop && range && cowl_enum_value_is_valid(QT, type))) return NULL;
    return cowl_data_quant_alloc(COWL_CET_DATA_SOME + type, prop, range);
}

CowlDataQuant* cowl_data_quant_retain(CowlDataQuant *restr) {
    return cowl_object_incr_ref(restr);
}

void cowl_data_quant_release(CowlDataQuant *restr) {
    if (restr && !cowl_object_decr_ref(restr)) {
        cowl_data_quant_free(restr);
    }
}

CowlQuantType cowl_data_quant_get_type(CowlDataQuant *restr) {
    return (CowlQuantType)(cowl_get_type(restr) - COWL_OT_CE_DATA_SOME);
}

CowlDataPropExp* cowl_data_quant_get_prop(CowlDataQuant *restr) {
    return restr->prop;
}

CowlDataRange* cowl_data_quant_get_range(CowlDataQuant *restr) {
    return restr->range;
}

CowlString* cowl_data_quant_to_string(CowlDataQuant *restr)
    COWL_TO_STRING_IMPL(data_quant, restr)

bool cowl_data_quant_equals(CowlDataQuant *lhs, CowlDataQuant *rhs) {
    return cowl_object_type_equals(lhs, rhs) &&
           cowl_object_hash_equals(lhs, rhs) &&
           cowl_data_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_data_range_equals(lhs->range, rhs->range);
}

ulib_uint cowl_data_quant_hash(CowlDataQuant *restr) {
    return cowl_object_hash_get(restr);
}

bool cowl_data_quant_iterate_primitives(CowlDataQuant *restr, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return (cowl_data_prop_exp_iterate_primitives(restr->prop, flags, iter) &&
            cowl_data_range_iterate_primitives(restr->range, flags, iter));
}
