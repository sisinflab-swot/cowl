/// @author Ivano Bilenchi

#include "cowl_obj_max_card_private.h"
#include "cowl_obj_prop_exp_private.h"
#include "cowl_hash_utils.h"

CowlObjPropExp const* cowl_obj_max_card_get_prop(CowlObjMaxCard const *restr) {
    return restr->prop;
}

CowlClsExp const* cowl_obj_max_card_get_filler(CowlObjMaxCard const *restr) {
    return restr->filler;
}

uint32_t cowl_obj_max_card_get_cardinality(CowlObjMaxCard const *restr) {
    return restr->cardinality;
}

bool cowl_obj_max_card_equals(CowlObjMaxCard const *lhs, CowlObjMaxCard const *rhs) {
    return lhs->cardinality == rhs->cardinality &&
           cowl_obj_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_cls_exp_equals(lhs->filler, rhs->filler);
}

uint32_t cowl_obj_max_card_hash(CowlObjMaxCard const *restr) {
    return cowl_hash_3(COWL_HASH_INIT_OBJ_MAX_CARD,
                       restr->cardinality,
                       cowl_obj_prop_exp_hash(restr->prop),
                       cowl_cls_exp_hash(restr->filler));
}
