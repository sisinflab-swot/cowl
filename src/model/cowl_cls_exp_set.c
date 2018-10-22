/// @author Ivano Bilenchi

#include "cowl_cls_exp_set.h"
#include "cowl_cls_exp.h"

KHASH_SET_UTILS_IMPL(CowlClsExpSet, CowlClsExp const*,
                     cowl_cls_exp_hash, cowl_cls_exp_equals);

bool cowl_cls_exp_set_add(khash_t(CowlClsExpSet) *set, CowlClsExp const *exp) {
    bool inserted = kh_insert(CowlClsExpSet, set, exp);
    cowl_cls_exp_retain(exp);
    return inserted;
}

void cowl_cls_exp_set_free(khash_t(CowlClsExpSet) const *set) {
    if (!set) return;
    kh_foreach_key(set, CowlClsExp const *exp, cowl_cls_exp_release(exp));
    kh_destroy(CowlClsExpSet, (khash_t(CowlClsExpSet) *)set);
}
