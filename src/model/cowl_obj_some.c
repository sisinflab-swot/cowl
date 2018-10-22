/// @author Ivano Bilenchi

#include "cowl_obj_some_private.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"

#pragma mark - Private

static CowlObjSome* cowl_obj_some_alloc(CowlObjPropExp *prop, CowlClsExp *filler) {
    uint32_t hash = cowl_hash_2(COWL_HASH_INIT_OBJ_SOME,
                                cowl_obj_prop_exp_hash(prop),
                                cowl_cls_exp_hash(filler));

    CowlObjSome init = {
        .super = COWL_CLS_EXP_INIT(CCET_OBJ_SOME, hash),
        .prop = cowl_obj_prop_exp_retain(prop),
        .filler = cowl_cls_exp_retain(filler)
    };

    struct CowlObjSome *restr = malloc(sizeof(*restr));
    memcpy(restr, &init, sizeof(*restr));
    return restr;
}

static void cowl_obj_some_free(CowlObjSome *restr) {
    if (!restr) return;
    cowl_obj_prop_exp_release(restr->prop);
    cowl_cls_exp_release(restr->filler);
    free((void *)restr);
}

#pragma mark - Public

CowlObjSome* cowl_obj_some_get(CowlObjPropExp *prop, CowlClsExp *filler) {
    return cowl_obj_some_alloc(prop, filler);
}

CowlObjSome* cowl_obj_some_retain(CowlObjSome *restr) {
    return cowl_cls_exp_ref_incr(restr);
}

void cowl_obj_some_release(CowlObjSome *restr) {
    if (restr && !cowl_cls_exp_ref_decr(restr)) {
        cowl_obj_some_free(restr);
    }
}

CowlObjPropExp* cowl_obj_some_get_prop(CowlObjSome *restr) {
    return restr->prop;
}

CowlClsExp* cowl_obj_some_get_filler(CowlObjSome *restr) {
    return restr->filler;
}

bool cowl_obj_some_equals(CowlObjSome *lhs, CowlObjSome *rhs) {
    return cowl_obj_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_cls_exp_equals(lhs->filler, rhs->filler);
}

uint32_t cowl_obj_some_hash(CowlObjSome *restr) {
    return cowl_cls_exp_hash_get(restr);
}

bool cowl_obj_some_iterate_signature(CowlObjSome *restr, void *ctx, CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_iterate_signature(restr->prop, ctx, iter)) return false;
    if (!cowl_cls_exp_iterate_signature(restr->filler, ctx, iter)) return false;
    return true;
}
