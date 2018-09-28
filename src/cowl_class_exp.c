/// @author Ivano Bilenchi

#include "cowl_class_exp_private.h"
#include "cowl_entity_private.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp_private.h"

#include <assert.h>

KHASH_SET_UTILS_IMPL(CowlClassExpSet, CowlClassExp const*,
                     cowl_class_exp_hash, cowl_class_exp_equals);

#pragma mark - Private functions

static inline uint32_t cowl_class_exp_set_hash(khash_t(CowlClassExpSet) const *set) {
    uint32_t hash = COWL_HASH_INIT_CLASS_EXPR;

    kh_foreach_key(set, CowlClassExp const *exp, {
        hash = cowl_hs(hash, cowl_class_exp_hash(exp));
    });

    return hash;
}

#pragma mark - Public functions

CowlClassExpType cowl_class_exp_type(CowlClassExp const *exp) {
    return exp->type;
}

CowlEntity const* cowl_class_exp_as_class(CowlClassExp const *exp) {
    assert(exp->type == CCET_CLASS);
    return exp->owl_class;
}

CowlClassExp const* cowl_class_exp_operand(CowlClassExp const *exp) {
    assert(exp->type == CCET_OBJECT_COMPLEMENT_OF);
    return exp->operand;
}

khash_t(CowlClassExpSet) const* cowl_class_exp_operands(CowlClassExp const *exp) {
    assert(exp->type == CCET_OBJECT_INTERSECTION_OF || exp->type == CCET_OBJECT_UNION_OF);
    return exp->operands;
}

CowlObjPropExp const* cowl_class_exp_property(CowlClassExp const *exp) {
    assert(exp->type == CCET_OBJECT_ALL_VALUES_FROM ||
           exp->type == CCET_OBJECT_SOME_VALUES_FROM ||
           exp->type == CCET_OBJECT_MIN_CARDINALITY ||
           exp->type == CCET_OBJECT_MAX_CARDINALITY ||
           exp->type == CCET_OBJECT_EXACT_CARDINALITY);

    if (exp->type == CCET_OBJECT_ALL_VALUES_FROM || exp->type == CCET_OBJECT_SOME_VALUES_FROM) {
        return exp->restr_prop;
    } else {
        return exp->card_prop;
    }
}

CowlClassExp const* cowl_class_exp_filler(CowlClassExp const *exp) {
    assert(exp->type == CCET_OBJECT_ALL_VALUES_FROM ||
           exp->type == CCET_OBJECT_SOME_VALUES_FROM ||
           exp->type == CCET_OBJECT_MIN_CARDINALITY ||
           exp->type == CCET_OBJECT_MAX_CARDINALITY ||
           exp->type == CCET_OBJECT_EXACT_CARDINALITY);

    if (exp->type == CCET_OBJECT_ALL_VALUES_FROM || exp->type == CCET_OBJECT_SOME_VALUES_FROM) {
        return exp->restr_filler;
    } else {
        return exp->card_filler;
    }
}

uint32_t cowl_class_exp_cardinality(CowlClassExp const *exp) {
    assert(exp->type == CCET_OBJECT_MIN_CARDINALITY ||
           exp->type == CCET_OBJECT_MAX_CARDINALITY ||
           exp->type == CCET_OBJECT_EXACT_CARDINALITY);
    return exp->cardinality;
}

bool cowl_class_exp_equals(CowlClassExp const *a, CowlClassExp const *b) {
    if (a->type != b->type) return false;

    switch (a->type) {
        case CCET_CLASS:
            return cowl_entity_equals(a->owl_class, b->owl_class);

        case CCET_OBJECT_COMPLEMENT_OF:
            return cowl_class_exp_equals(a->operand, b->operand);

        case CCET_OBJECT_INTERSECTION_OF:
        case CCET_OBJECT_UNION_OF:
            return kh_set_equals(CowlClassExpSet, a->operands, b->operands);

        case CCET_OBJECT_SOME_VALUES_FROM:
        case CCET_OBJECT_ALL_VALUES_FROM:
            return cowl_obj_prop_exp_equals(a->restr_prop, b->restr_prop) &&
                   cowl_class_exp_equals(a->restr_filler, b->restr_filler);

        case CCET_OBJECT_MIN_CARDINALITY:
        case CCET_OBJECT_MAX_CARDINALITY:
        case CCET_OBJECT_EXACT_CARDINALITY:
            return a->cardinality == b->cardinality &&
                   cowl_obj_prop_exp_equals(a->card_prop, b->card_prop) &&
                   cowl_class_exp_equals(a->card_filler, b->card_filler);

        default:
            return false;
    }
}

uint32_t cowl_class_exp_hash(CowlClassExp const *exp) {
    uint32_t hash = 0;

    switch(exp->type) {
        case CCET_CLASS:
            hash = cowl_entity_hash(exp->owl_class);
            break;

        case CCET_OBJECT_COMPLEMENT_OF:
            hash = cowl_class_exp_hash(exp->operand);
            break;

        case CCET_OBJECT_INTERSECTION_OF:
        case CCET_OBJECT_UNION_OF:
            hash = cowl_class_exp_set_hash(exp->operands);
            break;

        case CCET_OBJECT_SOME_VALUES_FROM:
        case CCET_OBJECT_ALL_VALUES_FROM:
            hash = cowl_hash_2(COWL_HASH_INIT_CLASS_EXPR,
                               cowl_obj_prop_exp_hash(exp->restr_prop),
                               cowl_class_exp_hash(exp->restr_filler));
            break;

        case CCET_OBJECT_MIN_CARDINALITY:
        case CCET_OBJECT_MAX_CARDINALITY:
        case CCET_OBJECT_EXACT_CARDINALITY:
            hash = cowl_hash_3(COWL_HASH_INIT_CLASS_EXPR,
                               exp->cardinality,
                               cowl_obj_prop_exp_hash(exp->card_prop),
                               cowl_class_exp_hash(exp->card_filler));
            break;

        default:
            break;
    }

    return cowl_hash_2(COWL_HASH_INIT_CLASS_EXPR, exp->type, hash);
}
