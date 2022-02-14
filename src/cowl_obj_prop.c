/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_private.h"
#include "cowl_iri.h"
#include "cowl_iterator_private.h"
#include "cowl_object_table.h"
#include "cowl_template.h"

static UHash(CowlObjectTable) *inst_tbl = NULL;

static ulib_uint inst_tbl_hash(void *key) {
    return cowl_iri_hash(cowl_obj_prop_get_iri(key));
}

static bool inst_tbl_eq(void *lhs, void *rhs) {
    return cowl_iri_equals(cowl_obj_prop_get_iri(lhs), cowl_obj_prop_get_iri(rhs));
}

cowl_ret cowl_obj_prop_api_init(void) {
    inst_tbl = uhset_alloc_pi(CowlObjectTable, inst_tbl_hash, inst_tbl_eq);
    return inst_tbl ? COWL_OK : COWL_ERR_MEM;
}

void cowl_obj_prop_api_deinit(void) {
    uhash_free(CowlObjectTable, inst_tbl);
}

static CowlObjProp* cowl_obj_prop_alloc(CowlIRI *iri) {
    CowlObjProp *prop = ulib_alloc(prop);
    if (!prop) return NULL;

    *prop = (CowlObjProp) {
        .super = COWL_OBJ_PROP_EXP_INIT(false),
        .iri = cowl_iri_retain(iri)
    };

    return prop;
}

static void cowl_obj_prop_free(CowlObjProp *prop) {
    cowl_iri_release(prop->iri);
    ulib_free(prop);
}

CowlObjProp* cowl_obj_prop_get(CowlIRI *iri) {
    if (!iri) return NULL;
    COWL_INST_TBL_GET_IMPL(ObjProp, obj_prop, { .iri = iri }, cowl_obj_prop_alloc(iri))
}

CowlObjProp* cowl_obj_prop_retain(CowlObjProp *prop) {
    return cowl_object_incr_ref(prop);
}

void cowl_obj_prop_release(CowlObjProp *prop) {
    if (prop && !cowl_object_decr_ref(prop)) {
        uhset_remove(CowlObjectTable, inst_tbl, prop);
        cowl_obj_prop_free(prop);
    }
}

CowlObjProp* cowl_obj_prop_from_string(UString string)
    COWL_ENTITY_FROM_STRING_IMPL(ObjProp, obj_prop)

CowlIRI* cowl_obj_prop_get_iri(CowlObjProp *prop) {
    return prop->iri;
}

CowlString* cowl_obj_prop_to_string(CowlObjProp *prop)
    COWL_TO_STRING_IMPL(obj_prop, prop)

bool cowl_obj_prop_equals(CowlObjProp *lhs, CowlObjProp *rhs) {
    return lhs == rhs;
}

ulib_uint cowl_obj_prop_hash(CowlObjProp *prop) {
    return uhash_ptr_hash(prop);
}

bool cowl_obj_prop_iterate_primitives(CowlObjProp *prop, CowlPrimitiveFlags flags,
                                      CowlIterator *iter) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_OBJ_PROP) ? cowl_iterate(iter, prop) : true;
}
