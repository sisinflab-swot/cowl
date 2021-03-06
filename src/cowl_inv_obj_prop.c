/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_inv_obj_prop_private.h"
#include "cowl_obj_prop.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

#define cowl_inst_hash(X) cowl_obj_prop_hash((X)->prop)
#define cowl_inst_eq(A, B) cowl_obj_prop_equals((A)->prop, (B)->prop)

UHASH_INIT(CowlInvObjPropTable, CowlInvObjProp*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlInvObjPropTable) *inst_tbl = NULL;

cowl_ret cowl_inv_obj_prop_api_init(void) {
    inst_tbl = uhset_alloc(CowlInvObjPropTable);
    return inst_tbl ? COWL_OK : COWL_ERR_MEM;
}

void cowl_inv_obj_prop_api_deinit(void) {
    uhash_free(CowlInvObjPropTable, inst_tbl);
}

static CowlInvObjProp* cowl_inv_obj_prop_alloc(CowlObjProp *prop) {
    CowlInvObjProp *inv = cowl_alloc(inv);
    if (!inv) return NULL;

    *inv = (CowlInvObjProp) {
        .super = COWL_OBJ_PROP_EXP_INIT(true),
        .prop = cowl_obj_prop_retain(prop)
    };

    return inv;
}

static void cowl_inv_obj_prop_free(CowlInvObjProp *inv) {
    if (!inv) return;
    cowl_obj_prop_release(inv->prop);
    cowl_free(inv);
}

CowlInvObjProp* cowl_inv_obj_prop_get(CowlObjProp *prop) {
    if (!prop) return NULL;
    COWL_INST_TBL_GET_IMPL(InvObjProp, inv_obj_prop, { .prop = prop },
                           cowl_inv_obj_prop_alloc(prop))
}

CowlInvObjProp* cowl_inv_obj_prop_retain(CowlInvObjProp *inv) {
    return cowl_object_retain(inv);
}

void cowl_inv_obj_prop_release(CowlInvObjProp *inv) {
    if (inv && !cowl_object_release(inv)) {
        uhset_remove(CowlInvObjPropTable, inst_tbl, inv);
        cowl_inv_obj_prop_free(inv);
    }
}

CowlObjProp* cowl_inv_obj_prop_get_prop(CowlInvObjProp *inv) {
    return inv->prop;
}

CowlString* cowl_inv_obj_prop_to_string(CowlInvObjProp *inv)
    COWL_TO_STRING_IMPL(inv_obj_prop, inv)

bool cowl_inv_obj_prop_equals(CowlInvObjProp *lhs, CowlInvObjProp *rhs) {
    return lhs == rhs;
}

cowl_uint cowl_inv_obj_prop_hash(CowlInvObjProp *inv) {
    return uhash_ptr_hash(inv);
}

bool cowl_inv_obj_prop_iterate_primitives(CowlInvObjProp *inv, CowlIterator *iter,
                                          CowlPrimitiveFlags flags) {
    return cowl_obj_prop_iterate_primitives(inv->prop, iter, flags);
}
