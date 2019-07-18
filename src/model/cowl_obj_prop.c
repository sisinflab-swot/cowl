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

UHASH_INIT(CowlObjPropMap, CowlIRI*, CowlObjProp*, cowl_iri_hash, cowl_iri_equals)
static UHash(CowlObjPropMap) *inst_map = NULL;

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
    if (!inst_map) inst_map = uhmap_alloc(CowlObjPropMap);

    CowlObjProp *prop;
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlObjPropMap, inst_map, iri, &ret);

    if (ret == UHASH_INSERTED) {
        prop = cowl_obj_prop_alloc(iri);
        uhash_value(inst_map, idx) = prop;
    } else {
        prop = uhash_value(inst_map, idx);
        cowl_object_retain(prop);
    }

    return prop;
}

CowlObjProp* cowl_obj_prop_retain(CowlObjProp *prop) {
    return cowl_object_retain(prop);
}

void cowl_obj_prop_release(CowlObjProp *prop) {
    if (prop && !cowl_object_release(prop)) {
        uhmap_remove(CowlObjPropMap, inst_map, prop->iri);
        cowl_obj_prop_free(prop);
    }
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
