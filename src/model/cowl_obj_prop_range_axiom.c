/// @author Ivano Bilenchi

#include "cowl_obj_prop_range_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"

#pragma mark - Private

static CowlObjPropRangeAxiom const* cowl_obj_prop_range_axiom_alloc(CowlObjPropExp const *prop,
                                                                    CowlClsExp const *range) {
    uint32_t hash = cowl_hash_2(COWL_HASH_INIT_OBJ_PROP_RANGE_AXIOM,
                                cowl_obj_prop_exp_hash(prop),
                                cowl_cls_exp_hash(range));

    CowlObjPropRangeAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_OBJ_PROP_RANGE, hash),
        .prop_exp = cowl_obj_prop_exp_retain(prop),
        .range = cowl_cls_exp_retain(range)
    };

    CowlObjPropRangeAxiom *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_obj_prop_range_axiom_free(CowlObjPropRangeAxiom const *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_release(axiom->prop_exp);
    cowl_cls_exp_release(axiom->range);
    free((void *)axiom);
}

#pragma mark - Public

CowlObjPropRangeAxiom const* cowl_obj_prop_range_axiom_get(CowlObjPropExp const *prop,
                                                           CowlClsExp const *range) {
    return cowl_obj_prop_range_axiom_alloc(prop, range);
}

CowlObjPropRangeAxiom const* cowl_obj_prop_range_axiom_retain
    (CowlObjPropRangeAxiom const *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_obj_prop_range_axiom_release(CowlObjPropRangeAxiom const *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_obj_prop_range_axiom_free(axiom);
    }
}

CowlObjPropExp const* cowl_obj_prop_range_axiom_get_prop(CowlObjPropRangeAxiom const *axiom) {
    return axiom->prop_exp;
}

CowlClsExp const* cowl_obj_prop_range_axiom_get_range(CowlObjPropRangeAxiom const *axiom) {
    return axiom->range;
}

bool cowl_obj_prop_range_axiom_equals(CowlObjPropRangeAxiom const *lhs,
                                      CowlObjPropRangeAxiom const *rhs) {
    return cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp) &&
           cowl_cls_exp_equals(lhs->range, rhs->range);
}

uint32_t cowl_obj_prop_range_axiom_hash(CowlObjPropRangeAxiom const *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_obj_prop_range_axiom_iterate_signature(CowlObjPropRangeAxiom const *axiom,
                                                 void *ctx, CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_iterate_signature(axiom->prop_exp, ctx, iter)) return false;
    if (!cowl_cls_exp_iterate_signature(axiom->range, ctx, iter)) return false;
    return true;
}
