/// @author Ivano Bilenchi

#include "cowl_nary_data_prop_axiom_private.h"
#include "cowl_data_prop_exp.h"
#include "cowl_data_prop_exp_set.h"
#include "cowl_hash_utils.h"

static CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_alloc(CowlAxiomType type,
                                                              CowlDataPropExpSet *props) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_NARY_DATA_PROP_AXIOM, type,
                                   uhset_hash(CowlDataPropExpSet, props));

    CowlNAryDataPropAxiom init = {
        .super = COWL_AXIOM_INIT(type, hash),
        .props = props
    };

    cowl_struct(CowlNAryDataPropAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_nary_data_prop_axiom_free(CowlNAryDataPropAxiom *axiom) {
    if (!axiom) return;
    cowl_data_prop_exp_set_free(axiom->props);
    free((void *)axiom);
}

CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_get(CowlNAryAxiomType type,
                                                     CowlDataPropExpSet *props) {
    return cowl_nary_data_prop_axiom_alloc((CowlAxiomType)type + CAT_EQUIVALENT_DATA_PROP, props);
}

CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_retain(CowlNAryDataPropAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_nary_data_prop_axiom_release(CowlNAryDataPropAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_nary_data_prop_axiom_free(axiom);
    }
}

CowlNAryAxiomType cowl_nary_data_prop_axiom_get_type(CowlNAryDataPropAxiom *axiom) {
    return (CowlNAryAxiomType)(axiom->super.type - CAT_EQUIVALENT_DATA_PROP);
}

CowlDataPropExpSet* cowl_nary_data_prop_axiom_get_props(CowlNAryDataPropAxiom *axiom) {
    return axiom->props;
}

bool cowl_nary_data_prop_axiom_equals(CowlNAryDataPropAxiom *lhs, CowlNAryDataPropAxiom *rhs) {
    return lhs->super.type == rhs->super.type &&
           uhset_equals(CowlDataPropExpSet, lhs->props, rhs->props);
}

cowl_uint_t cowl_nary_data_prop_axiom_hash(CowlNAryDataPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_nary_data_prop_axiom_iterate_signature(CowlNAryDataPropAxiom *axiom,
                                                 void *ctx, CowlEntityIterator iter) {
    uhash_foreach_key(CowlDataPropExpSet, axiom->props, prop, {
        if (!cowl_data_prop_exp_iterate_signature(prop, ctx, iter)) return false;
    });

    return true;
}
