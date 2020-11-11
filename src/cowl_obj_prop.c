/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_private.h"
#include "cowl_iri_private.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

#define cowl_inst_hash(X) cowl_iri_hash((X)->iri)
#define cowl_inst_eq(A, B) cowl_iri_equals((A)->iri, (B)->iri)

UHASH_INIT(CowlObjPropTable, CowlObjProp*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlObjPropTable) *inst_tbl = NULL;

cowl_ret cowl_obj_prop_api_init(void) {
    inst_tbl = uhset_alloc(CowlObjPropTable);
    return inst_tbl ? COWL_OK : COWL_ERR_MEM;
}

void cowl_obj_prop_api_deinit(void) {
    uhash_free(CowlObjPropTable, inst_tbl);
}

static CowlObjProp* cowl_obj_prop_alloc(CowlIRI *iri) {
    CowlObjProp *prop = cowl_alloc(prop);
    if (!prop) return NULL;

    *prop = (CowlObjProp) {
        .super = COWL_OBJ_PROP_EXP_INIT(false),
        .iri = cowl_iri_retain(iri)
    };

    return prop;
}

static void cowl_obj_prop_free(CowlObjProp *prop) {
    if (!prop) return;
    cowl_iri_release(prop->iri);
    cowl_free(prop);
}

CowlObjProp* cowl_obj_prop_get(CowlIRI *iri) {
    if (!iri) return NULL;
    COWL_INST_TBL_GET_IMPL(ObjProp, obj_prop, { .iri = iri }, cowl_obj_prop_alloc(iri))
}

CowlObjProp* cowl_obj_prop_retain(CowlObjProp *prop) {
    return cowl_object_retain(prop);
}

void cowl_obj_prop_release(CowlObjProp *prop) {
    if (prop && !cowl_object_release(prop)) {
        uhset_remove(CowlObjPropTable, inst_tbl, prop);
        cowl_obj_prop_free(prop);
    }
}

CowlObjProp* cowl_obj_prop_from_cstring(char const *cstring, size_t length)
    COWL_ENTITY_FROM_CSTRING_IMPL(ObjProp, obj_prop)

CowlIRI* cowl_obj_prop_get_iri(CowlObjProp *prop) {
    return prop->iri;
}

CowlString* cowl_obj_prop_to_string(CowlObjProp *prop)
    COWL_TO_STRING_IMPL(obj_prop, prop)

bool cowl_obj_prop_equals(CowlObjProp *lhs, CowlObjProp *rhs) {
    return lhs == rhs;
}

cowl_uint cowl_obj_prop_hash(CowlObjProp *prop) {
    return uhash_ptr_hash(prop);
}

bool cowl_obj_prop_iterate_primitives(CowlObjProp *prop, CowlIterator *iter,
                                      CowlPrimitiveFlags flags) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_OBJ_PROP) ? cowl_iterate(iter, prop) : true;
}
