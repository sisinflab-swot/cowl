/// @author Ivano Bilenchi

#include "cowl_annot_prop_range_axiom_private.h"
#include "cowl_annot_prop.h"
#include "cowl_iri.h"

static CowlAnnotPropRangeAxiom* cowl_annot_prop_range_axiom_alloc(CowlAnnotProp *prop,
                                                                  CowlIRI *range,
                                                                  CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_ANNOT_PROP_RANGE_AXIOM, annot,
                                         cowl_annot_prop_hash(prop),
                                         cowl_iri_hash(range));

    CowlAnnotPropRangeAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_ANNOT_PROP_RANGE, hash, annot),
        .prop = cowl_annot_prop_retain(prop),
        .range = cowl_iri_retain(range)
    };

    cowl_struct(CowlAnnotPropRangeAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_annot_prop_range_axiom_free(CowlAnnotPropRangeAxiom *axiom) {
    if (!axiom) return;
    cowl_annot_prop_release(axiom->prop);
    cowl_iri_release(axiom->range);
    cowl_axiom_free(axiom);
}

CowlAnnotPropRangeAxiom* cowl_annot_prop_range_axiom_get(CowlAnnotProp *prop, CowlIRI *range,
                                                         CowlAnnotationVec *annot) {
    return cowl_annot_prop_range_axiom_alloc(prop, range, annot);
}

CowlAnnotPropRangeAxiom* cowl_annot_prop_range_axiom_retain(CowlAnnotPropRangeAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_annot_prop_range_axiom_release(CowlAnnotPropRangeAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_annot_prop_range_axiom_free(axiom);
    }
}

CowlAnnotProp* cowl_annot_prop_range_axiom_get_prop(CowlAnnotPropRangeAxiom *axiom) {
    return axiom->prop;
}

CowlIRI* cowl_annot_prop_range_axiom_get_range(CowlAnnotPropRangeAxiom *axiom) {
    return axiom->range;
}

CowlAnnotationVec* cowl_annot_prop_range_axiom_get_annot(CowlAnnotPropRangeAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

bool cowl_annot_prop_range_axiom_equals(CowlAnnotPropRangeAxiom *lhs,
                                        CowlAnnotPropRangeAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_iri_equals(lhs->range, rhs->range) &&
                                  cowl_annot_prop_equals(lhs->prop, rhs->prop));
}

cowl_uint_t cowl_annot_prop_range_axiom_hash(CowlAnnotPropRangeAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_annot_prop_range_axiom_iterate_signature(CowlAnnotPropRangeAxiom *axiom,
                                                   void *ctx, CowlEntityIterator iter) {
    if (!cowl_annot_prop_iterate_signature(axiom->prop, ctx, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, ctx, iter)) return false;
    return true;
}