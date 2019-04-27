/// @author Ivano Bilenchi

#include "cowl_cls_exp_set.h"
#include "cowl_cls_exp.h"

UHASH_SET_IMPL(CowlClsExpSet, CowlClsExp*, cowl_cls_exp_hash, cowl_cls_exp_equals)

bool cowl_cls_exp_set_insert(CowlMutableClsExpSet *set, CowlClsExp *exp) {
    return uhset_insert(CowlClsExpSet, set, cowl_cls_exp_retain(exp)) == UHASH_INSERTED;
}

void cowl_cls_exp_set_free(CowlClsExpSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlClsExpSet, set, exp, cowl_cls_exp_release(exp));
    uhash_free(CowlClsExpSet, (UHash(CowlClsExpSet) *)set);
}
