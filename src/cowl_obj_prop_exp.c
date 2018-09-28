/// @author Ivano Bilenchi

#include "cowl_obj_prop_exp_private.h"
#include "cowl_hash_utils.h"

CowlEntity const* cowl_obj_prop_exp_property(CowlObjPropExp const *exp) {
    return exp->prop;
}

bool cowl_obj_prop_exp_is_inverse(CowlObjPropExp const *exp) {
    return exp->is_inverse;
}

bool cowl_obj_prop_exp_equals(CowlObjPropExp const *a, CowlObjPropExp const *b) {
    return a->is_inverse == b->is_inverse && cowl_entity_equals(a->prop, b->prop);
}

uint32_t cowl_obj_prop_exp_hash(CowlObjPropExp const *exp) {
    return cowl_hash_2(COWL_HASH_INIT_OBJ_PROP_EXPR,
                       cowl_entity_hash(exp->prop),
                       (exp->is_inverse ? 1 : 0));
}
