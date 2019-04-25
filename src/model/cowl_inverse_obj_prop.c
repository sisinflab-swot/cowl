/// @author Ivano Bilenchi

#include "cowl_inverse_obj_prop_private.h"
#include "cowl_obj_prop.h"
#include "uhash.h"

UHASH_MAP_INIT(CowlInvObjPropMap, CowlObjProp*, CowlInverseObjProp*,
               cowl_obj_prop_hash, cowl_obj_prop_equals)
static UHash(CowlInvObjPropMap) *inst_map = NULL;

static CowlInverseObjProp* cowl_inverse_obj_prop_alloc(CowlObjProp *prop) {
    CowlInverseObjProp init = {
        .super = COWL_OBJ_PROP_EXP_INIT(true),
        .prop = cowl_obj_prop_retain(prop)
    };
    struct CowlInverseObjProp *inv = malloc(sizeof(*inv));
    memcpy(inv, &init, sizeof(*inv));
    return inv;
}

static void cowl_inverse_obj_prop_free(CowlInverseObjProp *inv) {
    if (!inv) return;
    cowl_obj_prop_release(inv->prop);
    free((void *)inv);
}

CowlInverseObjProp* cowl_inverse_obj_prop_get(CowlObjProp *prop) {
    if (!inst_map) inst_map = uhash_alloc(CowlInvObjPropMap);

    CowlInverseObjProp *inv;
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlInvObjPropMap, inst_map, prop, &ret);

    if (ret == UHASH_INSERTED) {
        inv = cowl_inverse_obj_prop_alloc(prop);
        uhash_value(inst_map, idx) = inv;
    } else {
        inv = uhash_value(inst_map, idx);
        cowl_obj_prop_exp_ref_incr(inv);
    }

    return inv;
}

CowlInverseObjProp* cowl_inverse_obj_prop_retain(CowlInverseObjProp *inv) {
    return cowl_obj_prop_exp_ref_incr(inv);
}

void cowl_inverse_obj_prop_release(CowlInverseObjProp *inv) {
    if (inv && !cowl_obj_prop_exp_ref_decr(inv)) {
        uhmap_remove(CowlInvObjPropMap, inst_map, inv->prop);
        cowl_inverse_obj_prop_free(inv);
    }
}

CowlObjProp* cowl_inverse_obj_prop_get_prop(CowlInverseObjProp *inv) {
    return inv->prop;
}

bool cowl_inverse_obj_prop_equals(CowlInverseObjProp *lhs, CowlInverseObjProp *rhs) {
    return lhs == rhs;
}

uint32_t cowl_inverse_obj_prop_hash(CowlInverseObjProp *inv) {
    return uhash_ptr_hash(inv);
}

bool cowl_inverse_obj_prop_iterate_signature(CowlInverseObjProp *inv,
                                             void *ctx, CowlEntityIterator iter) {
    return cowl_obj_prop_iterate_signature(inv->prop, ctx, iter);
}
