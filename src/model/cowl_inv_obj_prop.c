/// @author Ivano Bilenchi

#include "cowl_inv_obj_prop_private.h"
#include "cowl_obj_prop.h"

UHASH_MAP_INIT(CowlInvObjPropMap, CowlObjProp*, CowlInvObjProp*,
               cowl_obj_prop_hash, cowl_obj_prop_equals)
static UHash(CowlInvObjPropMap) *inst_map = NULL;

static CowlInvObjProp* cowl_inv_obj_prop_alloc(CowlObjProp *prop) {
    CowlInvObjProp init = {
        .super = COWL_OBJ_PROP_EXP_INIT(true),
        .prop = cowl_obj_prop_retain(prop)
    };
    cowl_struct(CowlInvObjProp) *inv = malloc(sizeof(*inv));
    memcpy(inv, &init, sizeof(*inv));
    return inv;
}

static void cowl_inv_obj_prop_free(CowlInvObjProp *inv) {
    if (!inv) return;
    cowl_obj_prop_release(inv->prop);
    free((void *)inv);
}

CowlInvObjProp* cowl_inv_obj_prop_get(CowlObjProp *prop) {
    if (!inst_map) inst_map = uhash_alloc(CowlInvObjPropMap);

    CowlInvObjProp *inv;
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlInvObjPropMap, inst_map, prop, &ret);

    if (ret == UHASH_INSERTED) {
        inv = cowl_inv_obj_prop_alloc(prop);
        uhash_value(inst_map, idx) = inv;
    } else {
        inv = uhash_value(inst_map, idx);
        cowl_object_retain(inv);
    }

    return inv;
}

CowlInvObjProp* cowl_inv_obj_prop_retain(CowlInvObjProp *inv) {
    return cowl_object_retain(inv);
}

void cowl_inv_obj_prop_release(CowlInvObjProp *inv) {
    if (inv && !cowl_object_release(inv)) {
        uhmap_remove(CowlInvObjPropMap, inst_map, inv->prop);
        cowl_inv_obj_prop_free(inv);
    }
}

CowlObjProp* cowl_inv_obj_prop_get_prop(CowlInvObjProp *inv) {
    return inv->prop;
}

bool cowl_inv_obj_prop_equals(CowlInvObjProp *lhs, CowlInvObjProp *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_inv_obj_prop_hash(CowlInvObjProp *inv) {
    return uhash_ptr_hash(inv);
}

bool cowl_inv_obj_prop_iterate_signature(CowlInvObjProp *inv, CowlEntityIterator *iter) {
    return cowl_obj_prop_iterate_signature(inv->prop, iter);
}
