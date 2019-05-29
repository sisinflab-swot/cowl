/// @author Ivano Bilenchi

#include "cowl_data_card_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_data_range.h"
#include "cowl_hash_utils.h"

static CowlDataCard* cowl_data_card_alloc(CowlClsExpType type, CowlDataPropExp *prop,
                                          CowlDataRange *range, cowl_uint_t cardinality) {
    cowl_uint_t hash;

    if (range) {
        hash = cowl_hash_4(COWL_HASH_INIT_OBJ_CARD, type, cardinality,
                           cowl_data_prop_exp_hash(prop), cowl_data_range_hash(range));
        cowl_data_range_retain(range);
    } else {
        hash = cowl_hash_3(COWL_HASH_INIT_OBJ_CARD, type, cardinality,
                           cowl_data_prop_exp_hash(prop));
    }

    CowlDataCard init = {
        .super = COWL_CLS_EXP_INIT(type, hash),
        .prop = cowl_data_prop_exp_retain(prop),
        .range = range,
        .cardinality = cardinality
    };

    cowl_struct(CowlDataCard) *restr = malloc(sizeof(*restr));
    memcpy(restr, &init, sizeof(*restr));
    return restr;
}

static void cowl_data_card_free(CowlDataCard *restr) {
    if (!restr) return;
    cowl_data_prop_exp_release(restr->prop);
    cowl_data_range_release(restr->range);
    free((void *)restr);
}

CowlDataCard* cowl_data_card_get(CowlCardType type, CowlDataPropExp *prop,
                               CowlDataRange *range, cowl_uint_t cardinality) {
    return cowl_data_card_alloc(CCET_OBJ_MIN_CARD + type, prop, range, cardinality);
}

CowlDataCard* cowl_data_card_retain(CowlDataCard *restr) {
    return cowl_cls_exp_ref_incr(restr);
}

void cowl_data_card_release(CowlDataCard *restr) {
    if (restr && !cowl_cls_exp_ref_decr(restr)) {
        cowl_data_card_free(restr);
    }
}

CowlCardType cowl_data_card_get_type(CowlDataCard *restr) {
    return (CowlCardType)(restr->super.type - CCET_OBJ_MIN_CARD);
}

CowlDataPropExp* cowl_data_card_get_prop(CowlDataCard *restr) {
    return restr->prop;
}

CowlDataRange* cowl_data_card_get_range(CowlDataCard *restr) {
    return restr->range;
}

cowl_uint_t cowl_data_card_get_cardinality(CowlDataCard *restr) {
    return restr->cardinality;
}

bool cowl_data_card_equals(CowlDataCard *lhs, CowlDataCard *rhs) {
    if (lhs->cardinality != rhs->cardinality || lhs->super.type != rhs->super.type) return false;
    if (!cowl_data_prop_exp_equals(lhs->prop, rhs->prop)) return false;
    if (lhs->range == rhs->range) return true;
    if (lhs->range && rhs->range) return cowl_data_range_equals(lhs->range, rhs->range);
    return false;
}

cowl_uint_t cowl_data_card_hash(CowlDataCard *restr) {
    return cowl_cls_exp_hash_get(restr);
}

bool cowl_data_card_iterate_signature(CowlDataCard *restr,
                                     void *ctx, CowlEntityIterator iter) {
    if (!cowl_data_prop_exp_iterate_signature(restr->prop, ctx, iter)) return false;
    if (restr->range && !cowl_data_range_iterate_signature(restr->range, ctx, iter)) return false;
    return true;
}
