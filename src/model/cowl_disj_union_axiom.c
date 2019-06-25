/// @author Ivano Bilenchi

#include "cowl_disj_union_axiom_private.h"
#include "cowl_class.h"
#include "cowl_cls_exp_set.h"

static CowlDisjUnionAxiom* cowl_disj_union_axiom_alloc(CowlClass *cls, CowlClsExpSet *disjoints,
                                                       CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_DISJ_UNION_AXIOM, annot,
                                         cowl_class_hash(cls),
                                         cowl_cls_exp_set_hash(disjoints));

    CowlDisjUnionAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_DISJOINT_UNION, hash, annot),
        .cls = cowl_class_retain(cls),
        .disjoints = disjoints
    };

    cowl_struct(CowlDisjUnionAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_disj_union_axiom_free(CowlDisjUnionAxiom *axiom) {
    if (!axiom) return;
    cowl_class_release(axiom->cls);
    cowl_cls_exp_set_free(axiom->disjoints);
    cowl_axiom_free(axiom);
}

CowlDisjUnionAxiom* cowl_disj_union_axiom_get(CowlClass *cls, CowlClsExpSet *disjoints,
                                              CowlAnnotationVec *annot) {
    return cowl_disj_union_axiom_alloc(cls, disjoints, annot);
}

CowlDisjUnionAxiom* cowl_disj_union_axiom_retain(CowlDisjUnionAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_disj_union_axiom_release(CowlDisjUnionAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_disj_union_axiom_free(axiom);
    }
}

CowlClass* cowl_disj_union_axiom_get_class(CowlDisjUnionAxiom *axiom) {
    return axiom->cls;
}

CowlClsExpSet* cowl_disj_union_axiom_get_disjoints(CowlDisjUnionAxiom *axiom) {
    return axiom->disjoints;
}

CowlAnnotationVec* cowl_disj_union_axiom_get_annot(CowlDisjUnionAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

bool cowl_disj_union_axiom_equals(CowlDisjUnionAxiom *lhs, CowlDisjUnionAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_class_equals(lhs->cls, rhs->cls) &&
                                  cowl_cls_exp_set_equals(lhs->disjoints, rhs->disjoints));
}

cowl_uint_t cowl_disj_union_axiom_hash(CowlDisjUnionAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_disj_union_axiom_iterate_signature(CowlDisjUnionAxiom *axiom,
                                                 void *ctx, CowlEntityIterator iter) {
    if (!cowl_class_iterate_signature(axiom->cls, ctx, iter)) return false;
    if (!cowl_cls_exp_set_iterate_signature(axiom->disjoints, ctx, iter)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, ctx, iter)) return false;
    return true;
}
