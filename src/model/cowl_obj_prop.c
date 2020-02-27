/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_prop_private.h"
#include "cowl_iri_private.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"

#define cowl_inst_hash(X) cowl_iri_hash((X)->iri)
#define cowl_inst_eq(A, B) cowl_iri_equals((A)->iri, (B)->iri)

UHASH_INIT(CowlObjPropTable, CowlObjProp*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlObjPropTable) *inst_tbl = NULL;

void cowl_obj_prop_api_init(void) {
    inst_tbl = uhset_alloc(CowlObjPropTable);
}

void cowl_obj_prop_api_deinit(void) {
    uhash_free(CowlObjPropTable, inst_tbl);
}

static CowlObjProp* cowl_obj_prop_alloc(CowlIRI *iri) {
    CowlObjProp init = { .super = COWL_OBJ_PROP_EXP_INIT(false), .iri = cowl_iri_retain(iri) };
    cowl_struct(CowlObjProp) *prop = malloc(sizeof(*prop));
    memcpy(prop, &init, sizeof(*prop));
    return prop;
}

static void cowl_obj_prop_free(CowlObjProp *prop) {
    if (!prop) return;
    cowl_iri_release(prop->iri);
    free((void *)prop);
}

CowlObjProp* cowl_obj_prop_get(CowlIRI *iri) {
    uhash_ret_t ret;
    CowlObjProp key = { .iri = iri };
    uhash_uint_t idx = uhash_put(CowlObjPropTable, inst_tbl, &key, &ret);

    CowlObjProp *prop;

    if (ret == UHASH_INSERTED) {
        prop = cowl_obj_prop_alloc(iri);
        uhash_key(inst_tbl, idx) = prop;
    } else {
        prop = uhash_key(inst_tbl, idx);
        cowl_object_retain(prop);
    }

    return prop;
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

CowlObjProp* cowl_obj_prop_from_cstring(char const *cstring, cowl_uint_t length) {
    CowlIRI *iri = cowl_iri_from_cstring(cstring, length);
    CowlObjProp *prop = cowl_obj_prop_get(iri);
    cowl_iri_release(iri);
    return prop;
}

CowlIRI* cowl_obj_prop_get_iri(CowlObjProp *prop) {
    return prop->iri;
}

CowlString* cowl_obj_prop_to_string(CowlObjProp *prop) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_obj_prop(buf, prop);
    return cowl_str_buf_to_string(buf);
}

bool cowl_obj_prop_equals(CowlObjProp *lhs, CowlObjProp *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_obj_prop_hash(CowlObjProp *prop) {
    return uhash_ptr_hash(prop);
}

bool cowl_obj_prop_iterate_signature(CowlObjProp *prop, CowlEntityIterator *iter) {
    return cowl_iterate(iter, cowl_entity_wrap_obj_prop(prop));
}
