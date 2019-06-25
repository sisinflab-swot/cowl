/// @author Ivano Bilenchi

#include "cowl_nary_data_prop_axiom_private.h"
#include "cowl_data_prop_exp_set.h"

static CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_alloc(CowlAxiomType type,
                                                              CowlDataPropExpSet *props,
                                                              CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_NARY_DATA_PROP_AXIOM, annot, type,
                                         cowl_data_prop_exp_set_hash(props));

    CowlNAryDataPropAxiom init = {
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .props = props
    };

    cowl_struct(CowlNAryDataPropAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_nary_data_prop_axiom_free(CowlNAryDataPropAxiom *axiom) {
    if (!axiom) return;
    cowl_data_prop_exp_set_free(axiom->props);
    cowl_axiom_free(axiom);
}

CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_get(CowlNAryAxiomType type,
                                                     CowlDataPropExpSet *props,
                                                     CowlAnnotationVec *annot) {
    CowlAxiomType axiom_type = (CowlAxiomType)type + CAT_EQUIVALENT_DATA_PROP;
    return cowl_nary_data_prop_axiom_alloc(axiom_type, props, annot);
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
    CowlAxiomFlags flags = axiom->super.flags;
    return (CowlNAryAxiomType)(cowl_axiom_flags_get_type(flags) - CAT_EQUIVALENT_DATA_PROP);
}

CowlDataPropExpSet* cowl_nary_data_prop_axiom_get_props(CowlNAryDataPropAxiom *axiom) {
    return axiom->props;
}

CowlAnnotationVec* cowl_nary_data_prop_axiom_get_annot(CowlNAryDataPropAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

bool cowl_nary_data_prop_axiom_equals(CowlNAryDataPropAxiom *lhs, CowlNAryDataPropAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs, cowl_data_prop_exp_set_equals(lhs->props, rhs->props));
}

cowl_uint_t cowl_nary_data_prop_axiom_hash(CowlNAryDataPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_nary_data_prop_axiom_iterate_signature(CowlNAryDataPropAxiom *axiom,
                                                 void *ctx, CowlEntityIterator iter) {
    if (!cowl_data_prop_exp_set_iterate_signature(axiom->props, ctx, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, ctx, iter)) return false;
    return true;
}
