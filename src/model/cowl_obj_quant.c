/// @author Ivano Bilenchi

#include "cowl_obj_quant_private.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"

static CowlObjQuant* cowl_obj_quant_alloc(CowlClsExpType type, CowlObjPropExp *prop,
                                          CowlClsExp *filler) {
    uint32_t hash = cowl_hash_3(COWL_HASH_INIT_OBJ_QUANT, type,
                                cowl_obj_prop_exp_hash(prop), cowl_cls_exp_hash(filler));

    CowlObjQuant init = {
        .super = COWL_CLS_EXP_INIT(type, hash),
        .prop = cowl_obj_prop_exp_retain(prop),
        .filler = cowl_cls_exp_retain(filler)
    };

    struct CowlObjQuant *restr = malloc(sizeof(*restr));
    memcpy(restr, &init, sizeof(*restr));
    return restr;
}

static void cowl_obj_quant_free(CowlObjQuant *restr) {
    if (!restr) return;
    cowl_obj_prop_exp_release(restr->prop);
    cowl_cls_exp_release(restr->filler);
    free((void *)restr);
}

CowlObjQuant* cowl_obj_quant_get(CowlObjQuantType type, CowlObjPropExp *prop, CowlClsExp *filler) {
    return cowl_obj_quant_alloc(CCET_OBJ_SOME + type, prop, filler);
}

CowlObjQuant* cowl_obj_quant_retain(CowlObjQuant *restr) {
    return cowl_cls_exp_ref_incr(restr);
}

void cowl_obj_quant_release(CowlObjQuant *restr) {
    if (restr && !cowl_cls_exp_ref_decr(restr)) {
        cowl_obj_quant_free(restr);
    }
}

CowlObjQuantType cowl_obj_quant_get_type(CowlObjQuant *restr) {
    return restr->super.type - CCET_OBJ_SOME;
}

CowlObjPropExp* cowl_obj_quant_get_prop(CowlObjQuant *restr) {
    return restr->prop;
}

CowlClsExp* cowl_obj_quant_get_filler(CowlObjQuant *restr) {
    return restr->filler;
}

bool cowl_obj_quant_equals(CowlObjQuant *lhs, CowlObjQuant *rhs) {
    return lhs->super.type == rhs->super.type &&
           cowl_obj_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_cls_exp_equals(lhs->filler, rhs->filler);
}

uint32_t cowl_obj_quant_hash(CowlObjQuant *restr) {
    return cowl_cls_exp_hash_get(restr);
}

bool cowl_obj_quant_iterate_signature(CowlObjQuant *restr, void *ctx, CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_iterate_signature(restr->prop, ctx, iter)) return false;
    if (!cowl_cls_exp_iterate_signature(restr->filler, ctx, iter)) return false;
    return true;
}
