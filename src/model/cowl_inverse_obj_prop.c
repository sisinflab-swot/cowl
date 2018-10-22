/// @author Ivano Bilenchi

#include "cowl_inverse_obj_prop_private.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop.h"
#include "khash_utils.h"

#pragma mark - Instance map

KHASH_MAP_UTILS_INIT(CowlInvObjPropMap, CowlObjProp const*, CowlInverseObjProp*,
                     cowl_obj_prop_hash, cowl_obj_prop_equals);
static khash_t(CowlInvObjPropMap) *inst_map = NULL;

#pragma mark - Private

static CowlInverseObjProp* cowl_inverse_obj_prop_alloc(CowlObjProp const *prop) {
    CowlInverseObjProp init = {
        .super = COWL_OBJ_PROP_EXP_INIT(true),
        .prop = cowl_obj_prop_retain(prop)
    };
    CowlInverseObjProp *inv = malloc(sizeof(*inv));
    memcpy(inv, &init, sizeof(*inv));
    return inv;
}

static void cowl_inverse_obj_prop_free(CowlInverseObjProp const *inv) {
    if (!inv) return;
    cowl_obj_prop_release(inv->prop);
    free((void *)inv);
}

#pragma mark - Public

CowlInverseObjProp const* cowl_inverse_obj_prop_get(CowlObjProp const *prop) {
    if (!inst_map) inst_map = kh_init(CowlInvObjPropMap);

    CowlInverseObjProp *inv;
    bool absent;
    khint_t idx = kh_put_key(CowlInvObjPropMap, inst_map, prop, &absent);

    if (absent) {
        inv = cowl_inverse_obj_prop_alloc(prop);
        kh_value(inst_map, idx) = inv;
    } else {
        inv = kh_value(inst_map, idx);
        cowl_obj_prop_exp_ref_incr(inv);
    }

    return inv;
}

CowlInverseObjProp const* cowl_inverse_obj_prop_retain(CowlInverseObjProp const *inv) {
    return cowl_obj_prop_exp_ref_incr(inv);
}

void cowl_inverse_obj_prop_release(CowlInverseObjProp const *inv) {
    if (inv && !cowl_obj_prop_exp_ref_decr(inv)) {
        kh_del_val(CowlInvObjPropMap, inst_map, inv->prop);
        cowl_inverse_obj_prop_free(inv);
    }
}

CowlObjProp const* cowl_inverse_obj_prop_get_prop(CowlInverseObjProp const *inv) {
    return inv->prop;
}

bool cowl_inverse_obj_prop_equals(CowlInverseObjProp const *lhs, CowlInverseObjProp const *rhs) {
    return lhs == rhs;
}

uint32_t cowl_inverse_obj_prop_hash(CowlInverseObjProp const *inv) {
    return kh_ptr_hash_func(inv);
}

bool cowl_inverse_obj_prop_iterate_signature(CowlInverseObjProp const *inv,
                                             void *ctx, CowlEntityIterator iter) {
    return cowl_obj_prop_iterate_signature(inv->prop, ctx, iter);
}
