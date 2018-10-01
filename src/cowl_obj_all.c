/// @author Ivano Bilenchi

#include "cowl_obj_all_private.h"
#include "cowl_obj_prop_exp_private.h"
#include "cowl_hash_utils.h"

CowlObjPropExp const* cowl_obj_all_get_prop(CowlObjAll const *restr) {
    return restr->prop;
}

CowlClsExp const* cowl_obj_all_get_filler(CowlObjAll const *restr) {
    return restr->filler;
}

bool cowl_obj_all_equals(CowlObjAll const *lhs, CowlObjAll const *rhs) {
    return cowl_obj_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_cls_exp_equals(lhs->filler, rhs->filler);
}

uint32_t cowl_obj_all_hash(CowlObjAll const *restr) {
    return cowl_hash_2(COWL_HASH_INIT_OBJ_ALL,
                       cowl_obj_prop_exp_hash(restr->prop),
                       cowl_cls_exp_hash(restr->filler));
}
