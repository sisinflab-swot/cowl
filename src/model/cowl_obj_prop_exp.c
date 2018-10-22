/// @author Ivano Bilenchi

#include "cowl_obj_prop_exp_private.h"
#include "cowl_hash_utils.h"
#include "cowl_inverse_obj_prop.h"
#include "cowl_obj_prop.h"

CowlObjPropExp const* cowl_obj_prop_exp_retain(CowlObjPropExp const *prop) {
    return cowl_obj_prop_exp_ref_incr(prop);
}

void cowl_obj_prop_exp_release(CowlObjPropExp const *prop) {
    if (!prop) return;

    if (prop->is_inverse) {
        cowl_inverse_obj_prop_release((CowlInverseObjProp *)prop);
    } else {
        cowl_obj_prop_release((CowlObjProp *)prop);
    }
}

bool cowl_obj_prop_exp_is_inverse(CowlObjPropExp const *exp) {
    return exp->is_inverse;
}

bool cowl_obj_prop_exp_equals(CowlObjPropExp const *lhs, CowlObjPropExp const *rhs) {
    if (lhs->is_inverse != rhs->is_inverse) return false;

    if (lhs->is_inverse) {
        return cowl_inverse_obj_prop_equals((CowlInverseObjProp *)lhs, (CowlInverseObjProp *)rhs);
    } else {
        return cowl_obj_prop_equals((CowlObjProp *)lhs, (CowlObjProp *)rhs);
    }
}

uint32_t cowl_obj_prop_exp_hash(CowlObjPropExp const *exp) {
    if (exp->is_inverse) {
        return cowl_inverse_obj_prop_hash((CowlInverseObjProp *)exp);
    } else {
        return cowl_obj_prop_hash((CowlObjProp *)exp);
    }
}

bool cowl_obj_prop_exp_iterate_signature(CowlObjPropExp const *exp,
                                         void *ctx, CowlEntityIterator iter) {
    if (exp->is_inverse) {
        return cowl_inverse_obj_prop_iterate_signature((CowlInverseObjProp *)exp, ctx, iter);
    } else {
        return cowl_obj_prop_iterate_signature((CowlObjProp *)exp, ctx, iter);
    }
}
