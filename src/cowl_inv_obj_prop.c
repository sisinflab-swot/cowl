/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_inv_obj_prop_private.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop.h"
#include "cowl_template.h"

static CowlInvObjProp* cowl_inv_obj_prop_alloc(CowlObjProp *prop) {
    CowlInvObjProp *inv = ulib_alloc(inv);
    if (!inv) return NULL;

    *inv = (CowlInvObjProp) {
        .super = COWL_OBJ_PROP_EXP_INIT(true),
        .prop = cowl_obj_prop_retain(prop)
    };

    return inv;
}

static void cowl_inv_obj_prop_free(CowlInvObjProp *inv) {
    cowl_obj_prop_release(inv->prop);
    ulib_free(inv);
}

CowlInvObjProp* cowl_inv_obj_prop_get(CowlObjProp *prop) {
    return prop ? cowl_inv_obj_prop_alloc(prop) : NULL;
}

CowlInvObjProp* cowl_inv_obj_prop_retain(CowlInvObjProp *inv) {
    return cowl_object_incr_ref(inv);
}

void cowl_inv_obj_prop_release(CowlInvObjProp *inv) {
    if (inv && !cowl_object_decr_ref(inv)) {
        cowl_inv_obj_prop_free(inv);
    }
}

CowlObjProp* cowl_inv_obj_prop_get_prop(CowlInvObjProp *inv) {
    return inv->prop;
}

CowlString* cowl_inv_obj_prop_to_string(CowlInvObjProp *inv)
    COWL_TO_STRING_IMPL(inv_obj_prop, inv)

bool cowl_inv_obj_prop_equals(CowlInvObjProp *lhs, CowlInvObjProp *rhs) {
    return cowl_obj_prop_equals(lhs->prop, rhs->prop);
}

ulib_uint cowl_inv_obj_prop_hash(CowlInvObjProp *inv) {
    return cowl_hash_1(COWL_HASH_INIT_INV_OBJ_PROP, cowl_obj_prop_hash(inv->prop));
}

bool cowl_inv_obj_prop_iterate_primitives(CowlInvObjProp *inv, CowlPrimitiveFlags flags,
                                          CowlIterator *iter) {
    return cowl_obj_prop_iterate_primitives(inv->prop, flags, iter);
}
