/// @author Ivano Bilenchi

#include "cowl_obj_all_private.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_hash_utils.h"

#pragma mark - Private

static CowlObjAll* cowl_obj_all_alloc(CowlObjPropExp const *prop, CowlClsExp const *filler) {
    uint32_t hash = cowl_hash_2(COWL_HASH_INIT_OBJ_ALL,
                                cowl_obj_prop_exp_hash(prop),
                                cowl_cls_exp_hash(filler));

    CowlObjAll init = {
        .super = COWL_CLS_EXP_INIT(CCET_OBJ_ALL, hash),
        .prop = cowl_obj_prop_exp_retain(prop),
        .filler = cowl_cls_exp_retain(filler)
    };

    CowlObjAll *restr = malloc(sizeof(*restr));
    memcpy(restr, &init, sizeof(*restr));
    return restr;
}

static void cowl_obj_all_free(CowlObjAll const *restr) {
    if (!restr) return;
    cowl_obj_prop_exp_release(restr->prop);
    cowl_cls_exp_release(restr->filler);
    free((void *)restr);
}

#pragma mark - Public

CowlObjAll const* cowl_obj_all_get(CowlObjPropExp const *prop, CowlClsExp const *exp) {
    return cowl_obj_all_alloc(prop, exp);
}

CowlObjAll const* cowl_obj_all_retain(CowlObjAll const *restr) {
    return cowl_cls_exp_ref_incr(restr);
}

void cowl_obj_all_release(CowlObjAll const *restr) {
    if (restr && !cowl_cls_exp_ref_decr(restr)) {
        cowl_obj_all_free(restr);
    }
}

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
    return cowl_cls_exp_hash_get(restr);
}

bool cowl_obj_all_iterate_signature(CowlObjAll const *restr, void *ctx, CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_iterate_signature(restr->prop, ctx, iter)) return false;
    if (!cowl_cls_exp_iterate_signature(restr->filler, ctx, iter)) return false;
    return true;
}
