/// @author Ivano Bilenchi

#include "cowl_obj_prop_exp_set.h"
#include "cowl_obj_prop_exp.h"

KHASH_SET_UTILS_IMPL(CowlObjPropExpSet, CowlObjPropExp*,
                     cowl_obj_prop_exp_hash, cowl_obj_prop_exp_equals);

bool cowl_obj_prop_exp_set_insert(CowlMutableObjPropExpSet *set, CowlObjPropExp *exp) {
    return kh_insert(CowlObjPropExpSet, set, cowl_obj_prop_exp_retain(exp));
}

void cowl_obj_prop_exp_set_free(CowlObjPropExpSet *set) {
    if (!set) return;
    kh_foreach_key(set, CowlObjPropExp *exp, cowl_obj_prop_exp_release(exp));
    kh_destroy(CowlObjPropExpSet, (khash_t(CowlObjPropExpSet) *)set);
}
