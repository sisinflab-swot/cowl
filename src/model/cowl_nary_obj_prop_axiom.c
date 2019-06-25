/// @author Ivano Bilenchi

#include "cowl_nary_obj_prop_axiom_private.h"
#include "cowl_obj_prop_exp_set.h"

static CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_alloc(CowlAxiomType type,
                                                            CowlObjPropExpSet *props,
                                                            CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_NARY_OBJ_PROP_AXIOM, annot, type,
                                         cowl_obj_prop_exp_set_hash(props));

    CowlNAryObjPropAxiom init = {
        .super = COWL_AXIOM_INIT(type, hash, annot),
        .props = props
    };

    cowl_struct(CowlNAryObjPropAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_nary_obj_prop_axiom_free(CowlNAryObjPropAxiom *axiom) {
    if (!axiom) return;
    cowl_obj_prop_exp_set_free(axiom->props);
    cowl_axiom_free(axiom);
}

CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_get(CowlNAryAxiomType type,
                                                   CowlObjPropExpSet *props,
                                                   CowlAnnotationVec *annot) {
    CowlAxiomType axiom_type = (CowlAxiomType)type + CAT_EQUIVALENT_OBJ_PROP;
    return cowl_nary_obj_prop_axiom_alloc(axiom_type, props, annot);
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
    CowlAxiomFlags flags = axiom->super.flags;
    return (CowlNAryAxiomType)(cowl_axiom_flags_get_type(flags) - CAT_EQUIVALENT_OBJ_PROP);
}

CowlObjPropExpSet* cowl_nary_obj_prop_axiom_get_props(CowlNAryObjPropAxiom *axiom) {
    return axiom->props;
}

CowlAnnotationVec* cowl_nary_obj_prop_axiom_get_annot(CowlNAryObjPropAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

bool cowl_nary_obj_prop_axiom_equals(CowlNAryObjPropAxiom *lhs, CowlNAryObjPropAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs, cowl_obj_prop_exp_set_equals(lhs->props, rhs->props));
}

cowl_uint_t cowl_nary_obj_prop_axiom_hash(CowlNAryObjPropAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_nary_obj_prop_axiom_iterate_signature(CowlNAryObjPropAxiom *axiom,
                                                void *ctx, CowlEntityIterator iter) {
    if (!cowl_obj_prop_exp_set_iterate_signature(axiom->props, ctx, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, ctx, iter)) return false;
    return true;
}
