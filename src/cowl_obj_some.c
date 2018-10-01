/// @author Ivano Bilenchi

#include "cowl_obj_some_private.h"
#include "cowl_obj_prop_exp_private.h"
#include "cowl_hash_utils.h"

CowlObjPropExp const* cowl_obj_some_get_prop(CowlObjSome const *restr) {
    return restr->prop;
}

CowlClsExp const* cowl_obj_some_get_filler(CowlObjSome const *restr) {
    return restr->filler;
}

bool cowl_obj_some_equals(CowlObjSome const *lhs, CowlObjSome const *rhs) {
    return cowl_obj_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_cls_exp_equals(lhs->filler, rhs->filler);
}

uint32_t cowl_obj_some_hash(CowlObjSome const *restr) {
    return cowl_hash_2(COWL_HASH_INIT_OBJ_SOME,
                       cowl_obj_prop_exp_hash(restr->prop),
                       cowl_cls_exp_hash(restr->filler));
}
