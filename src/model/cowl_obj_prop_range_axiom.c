/// @author Ivano Bilenchi

#include "cowl_obj_prop_range_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"

static CowlObjPropRangeAxiom* cowl_obj_prop_range_axiom_alloc(CowlObjPropExp *prop,
                                                              CowlClsExp *range) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_OBJ_PROP_RANGE_AXIOM,
                                   cowl_obj_prop_exp_hash(prop),
                                   cowl_cls_exp_hash(range));

    CowlObjPropRangeAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_OBJ_PROP_RANGE, hash),
        .prop_exp = cowl_obj_prop_exp_retain(prop),
        .range = cowl_cls_exp_retain(range)
    };

    cowl_struct(CowlObjPropRangeAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_obj_prop_range_axiom_free(CowlObjPropRangeAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_release(axiom->prop_exp);
    cowl_cls_exp_release(axiom->range);
    free((void *)axiom);
}

CowlObjPropRangeAxiom* cowl_obj_prop_range_axiom_get(CowlObjPropExp *prop, CowlClsExp *range) {
    return cowl_obj_prop_range_axiom_alloc(prop, range);
}

CowlObjPropRangeAxiom* cowl_obj_prop_range_axiom_retain(CowlObjPropRangeAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_obj_prop_range_axiom_release(CowlObjPropRangeAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_obj_prop_range_axiom_free(axiom);
    }
}

CowlObjPropExp* cowl_obj_prop_range_axiom_get_prop(CowlObjPropRangeAxiom *axiom) {
    return axiom->prop_exp;
}

CowlClsExp* cowl_obj_prop_range_axiom_get_range(CowlObjPropRangeAxiom *axiom) {
    return axiom->range;
}

bool cowl_obj_prop_range_axiom_equals(CowlObjPropRangeAxiom *lhs, CowlObjPropRangeAxiom *rhs) {
    return cowl_obj_prop_exp_equals(lhs->prop_exp, rhs->prop_exp) &&
           cowl_cls_exp_equals(lhs->range, rhs->range);
}

cowl_uint_t cowl_obj_prop_range_axiom_hash(CowlObjPropRangeAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_obj_prop_range_axiom_iterate_signature(CowlObjPropRangeAxiom *axiom,
                                                 void *ctx, CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_iterate_signature(axiom->prop_exp, ctx, iter)) return false;
    if (!cowl_cls_exp_iterate_signature(axiom->range, ctx, iter)) return false;
    return true;
}
