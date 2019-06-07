/// @author Ivano Bilenchi

#include "cowl_nary_obj_prop_axiom_private.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_obj_prop_exp_set.h"

static CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_alloc(CowlAxiomType type,
                                                            CowlObjPropExpSet *props) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_NARY_OBJ_PROP_AXIOM, type,
                                   uhset_hash(CowlObjPropExpSet, props));

    CowlNAryObjPropAxiom init = {
        .super = COWL_AXIOM_INIT(type, hash),
        .props = props
    };

    cowl_struct(CowlNAryObjPropAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_nary_obj_prop_axiom_free(CowlNAryObjPropAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_set_free(axiom->props);
    free((void *)axiom);
}

CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_get(CowlNAryAxiomType type,
                                                   CowlObjPropExpSet *props) {
    return cowl_nary_obj_prop_axiom_alloc((CowlAxiomType)type + CAT_EQUIVALENT_OBJ_PROP, props);
}

CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_retain(CowlNAryObjPropAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_nary_obj_prop_axiom_release(CowlNAryObjPropAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_nary_obj_prop_axiom_free(axiom);
    }
}

CowlNAryAxiomType cowl_nary_obj_prop_axiom_get_type(CowlNAryObjPropAxiom *axiom) {
    return (CowlNAryAxiomType)(axiom->super.type - CAT_EQUIVALENT_OBJ_PROP);
}

CowlObjPropExpSet* cowl_nary_obj_prop_axiom_get_props(CowlNAryObjPropAxiom *axiom) {
    return axiom->props;
}

bool cowl_nary_obj_prop_axiom_equals(CowlNAryObjPropAxiom *lhs, CowlNAryObjPropAxiom *rhs) {
    return lhs->super.type == rhs->super.type &&
           uhset_equals(CowlObjPropExpSet, lhs->props, rhs->props);
}

cowl_uint_t cowl_nary_obj_prop_axiom_hash(CowlNAryObjPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_nary_obj_prop_axiom_iterate_signature(CowlNAryObjPropAxiom *axiom,
                                                void *ctx, CowlEntityIterator iter) {
    uhash_foreach_key(CowlObjPropExpSet, axiom->props, prop, {
        if (!cowl_obj_prop_exp_iterate_signature(prop, ctx, iter)) return false;
    });

    return true;
}
