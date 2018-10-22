/// @author Ivano Bilenchi

#include "cowl_obj_exact_card_private.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_hash_utils.h"

#pragma mark - Private

static CowlObjExactCard* cowl_obj_exact_card_alloc(CowlObjPropExp *prop, CowlClsExp *filler,
                                                   uint32_t cardinality) {
    uint32_t hash = cowl_hash_3(COWL_HASH_INIT_OBJ_EXACT_CARD,
                                cardinality,
                                cowl_obj_prop_exp_hash(prop),
                                cowl_cls_exp_hash(filler));

    CowlObjExactCard init = {
        .super = COWL_CLS_EXP_INIT(CCET_OBJ_EXACT_CARD, hash),
        .prop = cowl_obj_prop_exp_retain(prop),
        .filler = cowl_cls_exp_retain(filler),
        .cardinality = cardinality
    };

    struct CowlObjExactCard *restr = malloc(sizeof(*restr));
    memcpy(restr, &init, sizeof(*restr));
    return restr;
}

static void cowl_obj_exact_card_free(CowlObjExactCard *restr) {
    if (!restr) return;
    cowl_obj_prop_exp_release(restr->prop);
    cowl_cls_exp_release(restr->filler);
    free((void *)restr);
}

#pragma mark - Public

CowlObjExactCard* cowl_obj_exact_card_get(CowlObjPropExp *prop, CowlClsExp *filler,
                                          uint32_t cardinality) {
    return cowl_obj_exact_card_alloc(prop, filler, cardinality);
}

CowlObjExactCard* cowl_obj_exact_card_retain(CowlObjExactCard *restr) {
    return cowl_cls_exp_ref_incr(restr);
}

void cowl_obj_exact_card_release(CowlObjExactCard *restr) {
    if (restr && !cowl_cls_exp_ref_decr(restr)) {
        cowl_obj_exact_card_free(restr);
    }
}

CowlObjPropExp* cowl_obj_exact_card_get_prop(CowlObjExactCard *restr) {
    return restr->prop;
}

CowlClsExp* cowl_obj_exact_card_get_filler(CowlObjExactCard *restr) {
    return restr->filler;
}

uint32_t cowl_obj_exact_card_get_cardinality(CowlObjExactCard *restr) {
    return restr->cardinality;
}

bool cowl_obj_exact_card_equals(CowlObjExactCard *lhs, CowlObjExactCard *rhs) {
    return lhs->cardinality == rhs->cardinality &&
           cowl_obj_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_cls_exp_equals(lhs->filler, rhs->filler);
}

uint32_t cowl_obj_exact_card_hash(CowlObjExactCard *restr) {
    return cowl_cls_exp_hash_get(restr);
}

bool cowl_obj_exact_card_iterate_signature(CowlObjExactCard *restr,
                                           void *ctx, CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_iterate_signature(restr->prop, ctx, iter)) return false;
    if (!cowl_cls_exp_iterate_signature(restr->filler, ctx, iter)) return false;
    return true;
}
