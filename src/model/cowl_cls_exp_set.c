/// @author Ivano Bilenchi

#include "cowl_cls_exp_set.h"
#include "cowl_cls_exp.h"

UHASH_SET_IMPL(CowlClsExpSet, CowlClsExp*, cowl_cls_exp_hash, cowl_cls_exp_equals)

void cowl_cls_exp_set_free(CowlClsExpSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlClsExpSet, set, exp, cowl_cls_exp_release(exp));
    uhash_free(CowlClsExpSet, (UHash(CowlClsExpSet) *)set);
}

bool cowl_cls_exp_set_equals(CowlClsExpSet *lhs, CowlClsExpSet *rhs) {
    return uhset_equals(CowlClsExpSet, lhs, rhs);
}

cowl_uint_t cowl_cls_exp_set_hash(CowlClsExpSet *set) {
    return uhset_hash(CowlClsExpSet, set);
}

bool cowl_cls_exp_set_iterate_signature(CowlClsExpSet *set, void *ctx, CowlEntityIterator iter) {
    uhash_foreach_key(CowlClsExpSet, set, exp, {
        if (!cowl_cls_exp_iterate_signature(exp, ctx, iter)) return false;
    });
    return true;
}
