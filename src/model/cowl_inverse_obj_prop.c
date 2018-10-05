/// @author Ivano Bilenchi

#include "cowl_inverse_obj_prop_private.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop.h"

CowlObjProp const* cowl_inverse_obj_prop_get_prop(CowlInverseObjProp const *inv) {
    return inv->prop;
}

bool cowl_inverse_obj_prop_equals(CowlInverseObjProp const *lhs, CowlInverseObjProp const *rhs) {
    return cowl_obj_prop_equals(lhs->prop, rhs->prop);
}

uint32_t cowl_inverse_obj_prop_hash(CowlInverseObjProp const *inv) {
    return cowl_hash_1(COWL_HASH_INIT_INV_OBJ_PROP, cowl_obj_prop_hash(inv->prop));
}

bool cowl_inverse_obj_prop_iterate_signature(CowlInverseObjProp const *inv,
                                             void *ctx, CowlEntityIterator iter) {
    return cowl_obj_prop_iterate_signature(inv->prop, ctx, iter);
}
