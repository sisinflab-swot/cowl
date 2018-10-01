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

    switch (lhs->type) {

        case CCET_CLASS:
            return cowl_class_equals((CowlClass *)lhs, (CowlClass *)rhs);

        case CCET_OBJ_COMPLEMENT:
            return cowl_obj_compl_equals((CowlObjCompl *)lhs, (CowlObjCompl *)rhs);

        case CCET_OBJ_INTERSECTION:
            return cowl_obj_intersection_equals((CowlObjIntersection *)lhs,
                                                (CowlObjIntersection *)rhs);

        case CCET_OBJ_UNION:
            return cowl_obj_union_equals((CowlObjUnion *)lhs, (CowlObjUnion *)rhs);

        case CCET_OBJ_SOME:
            return cowl_obj_some_equals((CowlObjSome *)lhs, (CowlObjSome *)rhs);

        case CCET_OBJ_ALL:
            return cowl_obj_all_equals((CowlObjAll *)lhs, (CowlObjAll *)rhs);

        case CCET_OBJ_MIN_CARD:
            return cowl_obj_min_card_equals((CowlObjMinCard *)lhs, (CowlObjMinCard *)rhs);

        case CCET_OBJ_MAX_CARD:
            return cowl_obj_max_card_equals((CowlObjMaxCard *)lhs, (CowlObjMaxCard *)rhs);

        case CCET_OBJ_EXACT_CARD:
            return cowl_obj_exact_card_equals((CowlObjExactCard *)lhs, (CowlObjExactCard *)rhs);

        default:
            return false;
    }
}

uint32_t cowl_cls_exp_hash(CowlClsExp const *exp) {
    switch(exp->type) {

        case CCET_CLASS:
            return cowl_class_hash((CowlClass *)exp);

        case CCET_OBJ_COMPLEMENT:
            return cowl_obj_compl_hash((CowlObjCompl *)exp);

        case CCET_OBJ_INTERSECTION:
            return cowl_obj_intersection_hash((CowlObjIntersection *)exp);

        case CCET_OBJ_UNION:
            return cowl_obj_union_hash((CowlObjUnion *)exp);

        case CCET_OBJ_SOME:
            return cowl_obj_some_hash((CowlObjSome *)exp);

        case CCET_OBJ_ALL:
            return cowl_obj_all_hash((CowlObjAll *)exp);

        case CCET_OBJ_MIN_CARD:
            return cowl_obj_min_card_hash((CowlObjMinCard *)exp);

        case CCET_OBJ_MAX_CARD:
            return cowl_obj_max_card_hash((CowlObjMaxCard *)exp);

        case CCET_OBJ_EXACT_CARD:
            return cowl_obj_exact_card_hash((CowlObjExactCard *)exp);

        default:
            return 0;
    }
}
