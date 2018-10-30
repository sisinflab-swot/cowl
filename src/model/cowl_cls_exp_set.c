/// @author Ivano Bilenchi

#include "cowl_cls_exp_set.h"
#include "cowl_cls_exp.h"

KHASH_SET_UTILS_IMPL(CowlClsExpSet, CowlClsExp*, cowl_cls_exp_hash, cowl_cls_exp_equals);

bool cowl_cls_exp_set_insert(CowlMutableClsExpSet *set, CowlClsExp *exp) {
    return kh_insert(CowlClsExpSet, set, cowl_cls_exp_retain(exp));
}

void cowl_cls_exp_set_free(CowlClsExpSet *set) {
    if (!set) return;
    kh_foreach_key(set, CowlClsExp *exp, cowl_cls_exp_release(exp));
    kh_destroy(CowlClsExpSet, (khash_t(CowlClsExpSet) *)set);
}
