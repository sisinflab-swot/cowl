/// @author Ivano Bilenchi

#include "cowl_cls_exp_private.h"
#include "cowl_class.h"
#include "cowl_obj_all.h"
#include "cowl_obj_compl.h"
#include "cowl_obj_exact_card.h"
#include "cowl_obj_intersection.h"
#include "cowl_obj_max_card.h"
#include "cowl_obj_min_card.h"
#include "cowl_obj_some.h"
#include "cowl_obj_union.h"

#pragma mark - Public functions

CowlClsExp* cowl_cls_exp_retain(CowlClsExp *exp) {
    return cowl_cls_exp_ref_incr(exp);
}

void cowl_cls_exp_release(CowlClsExp *exp) {
    if (!exp) return;

#define GEN_CASE_RELEASE(CCET, TYPE, PREFIX) \
    case CCET: return PREFIX##_release((TYPE *)exp)

    switch (exp->type) {

        GEN_CASE_RELEASE(CCET_CLASS, CowlClass, cowl_class);
        GEN_CASE_RELEASE(CCET_OBJ_COMPLEMENT, CowlObjCompl, cowl_obj_compl);
        GEN_CASE_RELEASE(CCET_OBJ_INTERSECTION, CowlObjIntersection, cowl_obj_intersection);
        GEN_CASE_RELEASE(CCET_OBJ_UNION, CowlObjUnion, cowl_obj_union);
        GEN_CASE_RELEASE(CCET_OBJ_SOME, CowlObjSome, cowl_obj_some);
        GEN_CASE_RELEASE(CCET_OBJ_ALL, CowlObjAll, cowl_obj_all);
        GEN_CASE_RELEASE(CCET_OBJ_MIN_CARD, CowlObjMinCard, cowl_obj_min_card);
        GEN_CASE_RELEASE(CCET_OBJ_MAX_CARD, CowlObjMaxCard, cowl_obj_max_card);
        GEN_CASE_RELEASE(CCET_OBJ_EXACT_CARD, CowlObjExactCard, cowl_obj_exact_card);

        default:
            break;
    }
}

CowlClsExpType cowl_cls_exp_get_type(CowlClsExp *exp) {
    return exp->type;
}

bool cowl_cls_exp_equals(CowlClsExp *lhs, CowlClsExp *rhs) {
    if (lhs->type != rhs->type) return false;

#define GEN_CASE_EQUAL(CCET, TYPE, PREFIX) \
    case CCET: return PREFIX##_equals((TYPE *)lhs, (TYPE *)rhs)

    switch (lhs->type) {

        GEN_CASE_EQUAL(CCET_CLASS, CowlClass, cowl_class);
        GEN_CASE_EQUAL(CCET_OBJ_COMPLEMENT, CowlObjCompl, cowl_obj_compl);
        GEN_CASE_EQUAL(CCET_OBJ_INTERSECTION, CowlObjIntersection, cowl_obj_intersection);
        GEN_CASE_EQUAL(CCET_OBJ_UNION, CowlObjUnion, cowl_obj_union);
        GEN_CASE_EQUAL(CCET_OBJ_SOME, CowlObjSome, cowl_obj_some);
        GEN_CASE_EQUAL(CCET_OBJ_ALL, CowlObjAll, cowl_obj_all);
        GEN_CASE_EQUAL(CCET_OBJ_MIN_CARD, CowlObjMinCard, cowl_obj_min_card);
        GEN_CASE_EQUAL(CCET_OBJ_MAX_CARD, CowlObjMaxCard, cowl_obj_max_card);
        GEN_CASE_EQUAL(CCET_OBJ_EXACT_CARD, CowlObjExactCard, cowl_obj_exact_card);

        default:
            return false;
    }
}

uint32_t cowl_cls_exp_hash(CowlClsExp *exp) {
    return cowl_cls_exp_hash_get(exp);
}

bool cowl_cls_exp_iterate_signature(CowlClsExp *exp, void *ctx, CowlEntityIterator iter) {

#define GEN_CASE_SIG(CCET, TYPE, PREFIX) \
    case CCET: return PREFIX##_iterate_signature((TYPE *)exp, ctx, iter)

    switch (exp->type) {

        GEN_CASE_SIG(CCET_CLASS, CowlClass, cowl_class);
        GEN_CASE_SIG(CCET_OBJ_COMPLEMENT, CowlObjCompl, cowl_obj_compl);
        GEN_CASE_SIG(CCET_OBJ_INTERSECTION, CowlObjIntersection, cowl_obj_intersection);
        GEN_CASE_SIG(CCET_OBJ_UNION, CowlObjUnion, cowl_obj_union);
        GEN_CASE_SIG(CCET_OBJ_SOME, CowlObjSome, cowl_obj_some);
        GEN_CASE_SIG(CCET_OBJ_ALL, CowlObjAll, cowl_obj_all);
        GEN_CASE_SIG(CCET_OBJ_MIN_CARD, CowlObjMinCard, cowl_obj_min_card);
        GEN_CASE_SIG(CCET_OBJ_MAX_CARD, CowlObjMaxCard, cowl_obj_max_card);
        GEN_CASE_SIG(CCET_OBJ_EXACT_CARD, CowlObjExactCard, cowl_obj_exact_card);

        default:
            return true;
    }
}
