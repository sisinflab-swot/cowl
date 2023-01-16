/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_entity_private.h"
#include "cowl_iri.h"
#include "cowl_iterator_private.h"
#include "cowl_primitive.h"
#include "cowl_table.h"

static UHash(CowlObjectTable) inst_tbl;

static ulib_uint inst_tbl_hash(CowlAny *key) {
    ulib_uint h1 = cowl_iri_hash(cowl_entity_get_iri(key));
    ulib_uint h2 = (ulib_uint)cowl_get_type(key);
    return uhash_combine_hash(h1, h2);
}

static bool inst_tbl_eq(CowlAny *lhs, CowlAny *rhs) {
    return cowl_iri_equals(cowl_entity_get_iri(lhs), cowl_entity_get_iri(rhs)) &&
           cowl_get_type(lhs) == cowl_get_type(rhs);
}

cowl_ret cowl_entity_api_init(void) {
    inst_tbl = uhset_pi(CowlObjectTable, inst_tbl_hash, inst_tbl_eq);
    return COWL_OK;
}

void cowl_entity_api_deinit(void) {
    uhash_deinit(CowlObjectTable, &inst_tbl);
}

static CowlEntity *cowl_entity_alloc(CowlObjectType type, CowlIRI *iri) {
    CowlEntity *entity = ulib_alloc(entity);
    if (!entity) return NULL;
    *entity = (CowlEntity){ .super = COWL_OBJECT_INIT(type), .iri = cowl_iri_retain(iri) };
    return entity;
}

CowlAnyEntity *cowl_entity_get_impl(CowlObjectType type, CowlIRI *iri) {
    if (!iri) return NULL;
    ulib_uint idx;
    CowlEntity key = { .super = COWL_OBJECT_INIT(type), .iri = iri };
    uhash_ret ret = uhash_put(CowlObjectTable, &inst_tbl, &key, &idx);

    CowlEntity *entity = NULL;

    if (ret == UHASH_INSERTED) {
        entity = cowl_entity_alloc(type, iri);
        if (entity) {
            uhash_key(CowlObjectTable, &inst_tbl, idx) = entity;
        } else {
            uhash_delete(CowlObjectTable, &inst_tbl, idx);
        }
    } else if (ret == UHASH_PRESENT) {
        entity = uhash_key(CowlObjectTable, &inst_tbl, idx);
        (void)cowl_object_incr_ref(entity);
    }

    return entity;
}

void cowl_entity_release(CowlAnyEntity *entity) {
    if (entity && !cowl_object_decr_ref(entity)) {
        uhset_remove(CowlObjectTable, &inst_tbl, entity);
        cowl_iri_release(cowl_entity_get_iri(entity));
        ulib_free(entity);
    }
}

CowlAnyEntity *cowl_entity_from_string_impl(CowlObjectType type, UString string) {
    CowlEntity *entity = NULL;
    CowlIRI *iri = cowl_iri_from_string(string);

    if (iri) {
        entity = cowl_entity_get_impl(type, iri);
        cowl_iri_release(iri);
    }

    return entity;
}

CowlString *cowl_entity_to_string(CowlAnyEntity *entity) {
    return cowl_primitive_to_string(entity);
}

CowlIRI *cowl_entity_get_iri(CowlAnyEntity *entity) {
    return ((CowlEntity *)entity)->iri;
}

CowlEntityType cowl_entity_get_type(CowlAnyEntity *entity) {
    switch (cowl_get_type(entity)) {
        case COWL_OT_CE_CLASS: return COWL_ET_CLASS;
        case COWL_OT_OPE_OBJ_PROP: return COWL_ET_OBJ_PROP;
        case COWL_OT_I_NAMED: return COWL_ET_NAMED_IND;
        case COWL_OT_DPE_DATA_PROP: return COWL_ET_DATA_PROP;
        case COWL_OT_DR_DATATYPE: return COWL_ET_DATATYPE;
        default: return COWL_ET_ANNOT_PROP;
    }
}
