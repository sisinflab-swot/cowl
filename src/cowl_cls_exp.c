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

KHASH_SET_UTILS_IMPL(CowlClsExpSet, CowlClsExp const*,
                     cowl_cls_exp_hash, cowl_cls_exp_equals);

#pragma mark - Public functions

CowlClsExpType cowl_cls_exp_get_type(CowlClsExp const *exp) {
    return exp->type;
}

bool cowl_cls_exp_equals(CowlClsExp const *lhs, CowlClsExp const *rhs) {
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

uint32_t cowl_cls_exp_hash(CowlClsExp const *exp) {

#define GEN_CASE_HASH(CCET, TYPE, PREFIX) \
    case CCET: return PREFIX##_hash((TYPE *)exp)

    switch(exp->type) {

        GEN_CASE_HASH(CCET_CLASS, CowlClass, cowl_class);
        GEN_CASE_HASH(CCET_OBJ_COMPLEMENT, CowlObjCompl, cowl_obj_compl);
        GEN_CASE_HASH(CCET_OBJ_INTERSECTION, CowlObjIntersection, cowl_obj_intersection);
        GEN_CASE_HASH(CCET_OBJ_UNION, CowlObjUnion, cowl_obj_union);
        GEN_CASE_HASH(CCET_OBJ_SOME, CowlObjSome, cowl_obj_some);
        GEN_CASE_HASH(CCET_OBJ_ALL, CowlObjAll, cowl_obj_all);
        GEN_CASE_HASH(CCET_OBJ_MIN_CARD, CowlObjMinCard, cowl_obj_min_card);
        GEN_CASE_HASH(CCET_OBJ_MAX_CARD, CowlObjMaxCard, cowl_obj_max_card);
        GEN_CASE_HASH(CCET_OBJ_EXACT_CARD, CowlObjExactCard, cowl_obj_exact_card);

        default:
            return 0;
    }
}

bool cowl_cls_exp_iterate_signature(CowlClsExp const *exp, void *ctx, CowlEntityIterator iter) {

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
