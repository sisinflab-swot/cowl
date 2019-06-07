/// @author Ivano Bilenchi

#include "cowl_data_prop_range_axiom_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_data_range.h"
#include "cowl_hash_utils.h"

static CowlDataPropRangeAxiom* cowl_data_prop_range_axiom_alloc(CowlDataPropExp *prop,
                                                                CowlDataRange *range) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_DATA_PROP_RANGE_AXIOM,
                                   cowl_data_prop_exp_hash(prop),
                                   cowl_data_range_hash(range));

    CowlDataPropRangeAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_DATA_PROP_RANGE, hash),
        .prop_exp = cowl_data_prop_exp_retain(prop),
        .range = cowl_data_range_retain(range)
    };

    cowl_struct(CowlDataPropRangeAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_data_prop_range_axiom_free(CowlDataPropRangeAxiom *axiom) {
    if (!axiom) return;
    cowl_data_prop_exp_release(axiom->prop_exp);
    cowl_data_range_release(axiom->range);
    free((void *)axiom);
}

CowlDataPropRangeAxiom* cowl_data_prop_range_axiom_get(CowlDataPropExp *prop, CowlDataRange *range) {
    return cowl_data_prop_range_axiom_alloc(prop, range);
}

CowlDataPropRangeAxiom* cowl_data_prop_range_axiom_retain(CowlDataPropRangeAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_data_prop_range_axiom_release(CowlDataPropRangeAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_data_prop_range_axiom_free(axiom);
    }
}

CowlDataPropExp* cowl_data_prop_range_axiom_get_prop(CowlDataPropRangeAxiom *axiom) {
    return axiom->prop_exp;
}

CowlDataRange* cowl_data_prop_range_axiom_get_range(CowlDataPropRangeAxiom *axiom) {
    return axiom->range;
}

bool cowl_data_prop_range_axiom_equals(CowlDataPropRangeAxiom *lhs, CowlDataPropRangeAxiom *rhs) {
    return cowl_data_prop_exp_equals(lhs->prop_exp, rhs->prop_exp) &&
           cowl_data_range_equals(lhs->range, rhs->range);
}

cowl_uint_t cowl_data_prop_range_axiom_hash(CowlDataPropRangeAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_data_prop_range_axiom_iterate_signature(CowlDataPropRangeAxiom *axiom,
                                                 void *ctx, CowlEntityIterator iter) {
    if (!cowl_data_prop_exp_iterate_signature(axiom->prop_exp, ctx, iter)) return false;
    if (!cowl_data_range_iterate_signature(axiom->range, ctx, iter)) return false;
    return true;
}
