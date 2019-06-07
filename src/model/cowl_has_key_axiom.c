/// @author Ivano Bilenchi

#include "cowl_has_key_axiom_private.h"
#include "cowl_cls_exp.h"
#include "cowl_data_prop_exp.h"
#include "cowl_data_prop_exp_set.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_obj_prop_exp_set.h"

static CowlHasKeyAxiom* cowl_has_key_axiom_alloc(CowlClsExp *cls_exp, CowlObjPropExpSet *obj_props,
                                                 CowlDataPropExpSet *data_props) {
    cowl_uint_t hash = cowl_hash_3(COWL_HASH_INIT_HAS_KEY_AXIOM,
                                   cowl_cls_exp_hash(cls_exp),
                                   obj_props ? uhset_hash(CowlObjPropExpSet, obj_props) : 0,
                                   data_props ? uhset_hash(CowlDataPropExpSet, data_props) : 0);

    CowlHasKeyAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_HAS_KEY, hash),
        .cls_exp = cowl_cls_exp_retain(cls_exp),
        .obj_props = obj_props,
        .data_props = data_props
    };

    cowl_struct(CowlHasKeyAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_has_key_axiom_free(CowlHasKeyAxiom *axiom) {
    if (!axiom) return;
    cowl_cls_exp_release(axiom->cls_exp);
    cowl_obj_prop_exp_set_free(axiom->obj_props);
    cowl_data_prop_exp_set_free(axiom->data_props);
    free((void *)axiom);
}

CowlHasKeyAxiom* cowl_has_key_axiom_get(CowlClsExp *cls_exp, CowlObjPropExpSet *obj_props,
                                        CowlDataPropExpSet *data_props) {
    return cowl_has_key_axiom_alloc(cls_exp, obj_props, data_props);
}

CowlHasKeyAxiom* cowl_has_key_axiom_retain(CowlHasKeyAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_has_key_axiom_release(CowlHasKeyAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_has_key_axiom_free(axiom);
    }
}

CowlClsExp* cowl_has_key_axiom_get_cls_exp(CowlHasKeyAxiom *axiom) {
    return axiom->cls_exp;
}

CowlObjPropExpSet* cowl_has_key_axiom_get_obj_props(CowlHasKeyAxiom *axiom) {
    return axiom->obj_props;
}

CowlDataPropExpSet* cowl_has_key_axiom_get_data_props(CowlHasKeyAxiom *axiom) {
    return axiom->data_props;
}

bool cowl_has_key_axiom_equals(CowlHasKeyAxiom *lhs, CowlHasKeyAxiom *rhs) {
    return cowl_cls_exp_equals(lhs->cls_exp, rhs->cls_exp) &&
           uhset_equals(CowlObjPropExpSet, lhs->obj_props, rhs->obj_props) &&
           uhset_equals(CowlDataPropExpSet, lhs->data_props, rhs->data_props);
}

cowl_uint_t cowl_has_key_axiom_hash(CowlHasKeyAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_has_key_axiom_iterate_signature(CowlHasKeyAxiom *axiom, void *ctx,
                                          CowlEntityIterator iter) {
    if (!cowl_cls_exp_iterate_signature(axiom->cls_exp, ctx, iter)) return false;

    uhash_foreach_key(CowlObjPropExpSet, axiom->obj_props, prop, {
        if (!cowl_obj_prop_exp_iterate_signature(prop, ctx, iter)) return false;
    });

    uhash_foreach_key(CowlDataPropExpSet, axiom->data_props, prop, {
        if (!cowl_data_prop_exp_iterate_signature(prop, ctx, iter)) return false;
    });

    return true;
}
