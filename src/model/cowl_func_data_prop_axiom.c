/// @author Ivano Bilenchi

#include "cowl_func_data_prop_axiom_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_hash_utils.h"

static CowlFuncDataPropAxiom* cowl_func_data_prop_axiom_alloc(CowlDataPropExp *prop) {
    cowl_uint_t hash = cowl_hash_1(COWL_HASH_INIT_FUNCTIONAL_DATA_PROP_AXIOM,
                                   cowl_data_prop_exp_hash(prop));

    CowlFuncDataPropAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_FUNCTIONAL_DATA_PROP, hash),
        .prop = cowl_data_prop_exp_retain(prop)
    };

    cowl_struct(CowlFuncDataPropAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_func_data_prop_axiom_free(CowlFuncDataPropAxiom *axiom) {
    if (!axiom) return;
    cowl_data_prop_exp_release(axiom->prop);
    free((void *)axiom);
}

CowlFuncDataPropAxiom* cowl_func_data_prop_axiom_get(CowlDataPropExp *prop) {
    return cowl_func_data_prop_axiom_alloc(prop);
}

CowlFuncDataPropAxiom* cowl_func_data_prop_axiom_retain(CowlFuncDataPropAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_func_data_prop_axiom_release(CowlFuncDataPropAxiom *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_func_data_prop_axiom_free(axiom);
    }
}

CowlDataPropExp* cowl_func_data_prop_axiom_get_prop(CowlFuncDataPropAxiom *axiom) {
    return axiom->prop;
}

bool cowl_func_data_prop_axiom_equals(CowlFuncDataPropAxiom *lhs, CowlFuncDataPropAxiom *rhs) {
    return cowl_data_prop_exp_equals(lhs->prop, rhs->prop);
}

cowl_uint_t cowl_func_data_prop_axiom_hash(CowlFuncDataPropAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_func_data_prop_axiom_iterate_signature(CowlFuncDataPropAxiom *axiom,
                                                 void *ctx, CowlEntityIterator iter) {
    return cowl_data_prop_exp_iterate_signature(axiom->prop, ctx, iter);
}
