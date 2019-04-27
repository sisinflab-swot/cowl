/// @author Ivano Bilenchi

#include "cowl_obj_prop_exp_set.h"
#include "cowl_obj_prop_exp.h"

UHASH_SET_IMPL(CowlObjPropExpSet, CowlObjPropExp*,
               cowl_obj_prop_exp_hash, cowl_obj_prop_exp_equals)

bool cowl_obj_prop_exp_set_insert(CowlMutableObjPropExpSet *set, CowlObjPropExp *exp) {
    return uhset_insert(CowlObjPropExpSet, set, cowl_obj_prop_exp_retain(exp)) == UHASH_INSERTED;
}

void cowl_obj_prop_exp_set_free(CowlObjPropExpSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlObjPropExpSet, set, exp, cowl_obj_prop_exp_release(exp));
    uhash_free(CowlObjPropExpSet, (UHash(CowlObjPropExpSet) *)set);
}
