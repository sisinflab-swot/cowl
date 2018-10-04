/// @author Ivano Bilenchi

#include "cowl_obj_min_card_private.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_hash_utils.h"

CowlObjPropExp const* cowl_obj_min_card_get_prop(CowlObjMinCard const *restr) {
    return restr->prop;
}

CowlClsExp const* cowl_obj_min_card_get_filler(CowlObjMinCard const *restr) {
    return restr->filler;
}

uint32_t cowl_obj_min_card_get_cardinality(CowlObjMinCard const *restr) {
    return restr->cardinality;
}

bool cowl_obj_min_card_enum_signature(CowlObjMinCard const *restr, void *ctx,
                                      CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_enum_signature(restr->prop, ctx, iter)) return false;
    if (!cowl_cls_exp_enum_signature(restr->filler, ctx, iter)) return false;
    return true;
}

bool cowl_obj_min_card_equals(CowlObjMinCard const *lhs, CowlObjMinCard const *rhs) {
    return lhs->cardinality == rhs->cardinality &&
           cowl_obj_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_cls_exp_equals(lhs->filler, rhs->filler);
}

uint32_t cowl_obj_min_card_hash(CowlObjMinCard const *restr) {
    return cowl_hash_3(COWL_HASH_INIT_OBJ_MIN_CARD,
                       restr->cardinality,
                       cowl_obj_prop_exp_hash(restr->prop),
                       cowl_cls_exp_hash(restr->filler));
}
