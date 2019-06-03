/// @author Ivano Bilenchi

#include "cowl_sub_data_prop_axiom_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_hash_utils.h"

static CowlSubDataPropAxiom* cowl_sub_data_prop_axiom_alloc(CowlDataPropExp *sub,
                                                          CowlDataPropExp *super) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_SUB_DATA_PROP_AXIOM,
                                   cowl_data_prop_exp_hash(sub),
                                   cowl_data_prop_exp_hash(super));

    CowlSubDataPropAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_SUB_DATA_PROP, hash),
        .super_prop = cowl_data_prop_exp_retain(super),
        .sub_prop = cowl_data_prop_exp_retain(sub)
    };

    cowl_struct(CowlSubDataPropAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_sub_data_prop_axiom_free(CowlSubDataPropAxiom *axiom) {
    if (!axiom) return;
    cowl_data_prop_exp_release(axiom->super_prop);
    cowl_data_prop_exp_release(axiom->sub_prop);
    free((void *)axiom);
}

CowlSubDataPropAxiom* cowl_sub_data_prop_axiom_get(CowlDataPropExp *sub, CowlDataPropExp *super) {
    return cowl_sub_data_prop_axiom_alloc(sub, super);
}

CowlSubDataPropAxiom* cowl_sub_data_prop_axiom_retain(CowlSubDataPropAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_sub_data_prop_axiom_release(CowlSubDataPropAxiom *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_sub_data_prop_axiom_free(axiom);
    }
}

CowlDataPropExp* cowl_sub_data_prop_axiom_get_super(CowlSubDataPropAxiom *axiom) {
    return axiom->super_prop;
}

CowlDataPropExp* cowl_sub_data_prop_axiom_get_sub(CowlSubDataPropAxiom *axiom) {
    return axiom->sub_prop;
}

bool cowl_sub_data_prop_axiom_equals(CowlSubDataPropAxiom *lhs, CowlSubDataPropAxiom *rhs) {
    return cowl_data_prop_exp_equals(lhs->super_prop, rhs->super_prop) &&
           cowl_data_prop_exp_equals(lhs->sub_prop, rhs->sub_prop);
}

cowl_uint_t cowl_sub_data_prop_axiom_hash(CowlSubDataPropAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_sub_data_prop_axiom_iterate_signature(CowlSubDataPropAxiom *axiom,
                                               void *ctx, CowlEntityIterator iter) {
    if (!cowl_data_prop_exp_iterate_signature(axiom->super_prop, ctx, iter)) return false;
    if (!cowl_data_prop_exp_iterate_signature(axiom->sub_prop, ctx, iter)) return false;
    return true;
}
