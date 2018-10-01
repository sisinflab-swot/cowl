/// @author Ivano Bilenchi

#include "cowl_obj_exact_card_private.h"
#include "cowl_obj_prop_exp_private.h"
#include "cowl_hash_utils.h"

CowlObjPropExp const* cowl_obj_exact_card_get_prop(CowlObjExactCard const *restr) {
    return restr->prop;
}

CowlClsExp const* cowl_obj_exact_card_get_filler(CowlObjExactCard const *restr) {
    return restr->filler;
}

uint32_t cowl_obj_exact_card_get_cardinality(CowlObjExactCard const *restr) {
    return restr->cardinality;
}

bool cowl_obj_exact_card_equals(CowlObjExactCard const *lhs, CowlObjExactCard const *rhs) {
    return lhs->cardinality == rhs->cardinality &&
           cowl_obj_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_cls_exp_equals(lhs->filler, rhs->filler);
}

uint32_t cowl_obj_exact_card_hash(CowlObjExactCard const *restr) {
    return cowl_hash_3(COWL_HASH_INIT_OBJ_EXACT_CARD,
                       restr->cardinality,
                       cowl_obj_prop_exp_hash(restr->prop),
                       cowl_cls_exp_hash(restr->filler));
}
