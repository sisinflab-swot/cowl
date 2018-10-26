/// @author Ivano Bilenchi

#include "cowl_obj_prop_exp_private.h"
#include "cowl_hash_utils.h"
#include "cowl_inverse_obj_prop_private.h"
#include "cowl_obj_prop_private.h"

CowlObjPropExp* cowl_obj_prop_exp_retain(CowlObjPropExp *prop) {
    return cowl_obj_prop_exp_ref_incr(prop);
}

void cowl_obj_prop_exp_release(CowlObjPropExp *prop) {
    if (!prop) return;

    if (prop->is_inverse) {
        cowl_inverse_obj_prop_release((CowlInverseObjProp *)prop);
    } else {
        cowl_obj_prop_release((CowlObjProp *)prop);
    }
}

bool cowl_obj_prop_exp_is_inverse(CowlObjPropExp *exp) {
    return exp->is_inverse;
}

CowlObjProp* cowl_obj_prop_exp_get_prop(CowlObjPropExp *exp) {
    if (exp->is_inverse) {
        return ((CowlInverseObjProp *)exp)->prop;
    } else {
        return (CowlObjProp *)exp;
    }
}

bool cowl_obj_prop_exp_equals(CowlObjPropExp *lhs, CowlObjPropExp *rhs) {
    if (lhs->is_inverse != rhs->is_inverse) return false;

    if (lhs->is_inverse) {
        return cowl_inverse_obj_prop_equals((CowlInverseObjProp *)lhs, (CowlInverseObjProp *)rhs);
    } else {
        return cowl_obj_prop_equals((CowlObjProp *)lhs, (CowlObjProp *)rhs);
    }
}

uint32_t cowl_obj_prop_exp_hash(CowlObjPropExp *exp) {
    if (exp->is_inverse) {
        return cowl_inverse_obj_prop_hash((CowlInverseObjProp *)exp);
    } else {
        return cowl_obj_prop_hash((CowlObjProp *)exp);
    }
}

bool cowl_obj_prop_exp_iterate_signature(CowlObjPropExp *exp, void *ctx, CowlEntityIterator iter) {
    if (exp->is_inverse) {
        return cowl_inverse_obj_prop_iterate_signature((CowlInverseObjProp *)exp, ctx, iter);
    } else {
        return cowl_obj_prop_iterate_signature((CowlObjProp *)exp, ctx, iter);
    }
}
