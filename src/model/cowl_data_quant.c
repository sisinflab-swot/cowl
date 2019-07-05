/// @author Ivano Bilenchi

#include "cowl_data_quant_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_data_range.h"
#include "cowl_hash_utils.h"

static CowlDataQuant* cowl_data_quant_alloc(CowlClsExpType type, CowlDataPropExp *prop,
                                            CowlDataRange *range) {
    cowl_uint_t hash = cowl_hash_3(COWL_HASH_INIT_DATA_QUANT, type,
                                   cowl_data_prop_exp_hash(prop), cowl_data_range_hash(range));

    CowlDataQuant init = {
        .super = COWL_CLS_EXP_INIT(type, hash),
        .prop = cowl_data_prop_exp_retain(prop),
        .range = cowl_data_range_retain(range)
    };

    cowl_struct(CowlDataQuant) *restr = malloc(sizeof(*restr));
    memcpy(restr, &init, sizeof(*restr));
    return restr;
}

static void cowl_data_quant_free(CowlDataQuant *restr) {
    if (!restr) return;
    cowl_data_prop_exp_release(restr->prop);
    cowl_data_range_release(restr->range);
    free((void *)restr);
}

CowlDataQuant* cowl_data_quant_get(CowlQuantType type, CowlDataPropExp *prop,
                                   CowlDataRange *range) {
    return cowl_data_quant_alloc(COWL_CET_DATA_SOME + type, prop, range);
}

CowlDataQuant* cowl_data_quant_retain(CowlDataQuant *restr) {
    return cowl_object_retain(restr);
}

void cowl_data_quant_release(CowlDataQuant *restr) {
    if (restr && !cowl_object_release(restr)) {
        cowl_data_quant_free(restr);
    }
}

CowlQuantType cowl_data_quant_get_type(CowlDataQuant *restr) {
    return (CowlQuantType)(restr->super.type - COWL_CET_DATA_SOME);
}

CowlDataPropExp* cowl_data_quant_get_prop(CowlDataQuant *restr) {
    return restr->prop;
}

CowlDataRange* cowl_data_quant_get_range(CowlDataQuant *restr) {
    return restr->range;
}

bool cowl_data_quant_equals(CowlDataQuant *lhs, CowlDataQuant *rhs) {
    return lhs->super.type == rhs->super.type &&
           cowl_data_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_data_range_equals(lhs->range, rhs->range);
}

cowl_uint_t cowl_data_quant_hash(CowlDataQuant *restr) {
    return cowl_object_hash_get(restr);
}

bool cowl_data_quant_iterate_signature(CowlDataQuant *restr, CowlEntityIterator *iter) {
    if (!cowl_data_prop_exp_iterate_signature(restr->prop, iter)) return false;
    if (!cowl_data_range_iterate_signature(restr->range, iter)) return false;
    return true;
}
