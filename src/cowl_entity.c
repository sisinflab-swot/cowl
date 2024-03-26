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
#include "cowl_primitive_private.h"
#include "cowl_table.h"

static UHash(CowlObjectTable) inst_tbl;

#if COWL_ENTITY_IDS
#include "cowl_vector.h"
static UVec(CowlObjectPtr) id_map;
#endif

static ulib_uint inst_tbl_hash(CowlAny *key) {
    ulib_uint h1 = cowl_primitive_hash(cowl_entity_get_iri(key));
    ulib_uint h2 = (ulib_uint)cowl_get_type(key);
    return ulib_hash_combine(h1, h2);
}

static bool inst_tbl_eq(CowlAny *lhs, CowlAny *rhs) {
    return cowl_primitive_equals(cowl_entity_get_iri(lhs), cowl_entity_get_iri(rhs)) &&
           cowl_get_type(lhs) == cowl_get_type(rhs);
}

cowl_ret cowl_entity_api_init(void) {
    inst_tbl = uhset_pi(CowlObjectTable, inst_tbl_hash, inst_tbl_eq);
#if COWL_ENTITY_IDS
    id_map = uvec(CowlObjectPtr);
#endif
    return COWL_OK;
}

void cowl_entity_api_deinit(void) {
    uhash_deinit(CowlObjectTable, &inst_tbl);
#if COWL_ENTITY_IDS
    uvec_foreach (CowlObjectPtr, &id_map, e) {
        cowl_release(*e.item);
    }
    uvec_deinit(CowlObjectPtr, &id_map);
#endif
}

static CowlEntity *cowl_entity_alloc(CowlObjectType type, CowlIRI *iri) {
    CowlEntity *entity = ulib_alloc(entity);
    if (!entity) return NULL;

    entity->super = COWL_OBJECT_INIT(type);

#if COWL_ENTITY_IDS
    entity->id = uvec_count(CowlObjectPtr, &id_map);
    if (uvec_push(CowlObjectPtr, &id_map, entity) != UVEC_OK) {
        ulib_free(entity);
        return NULL;
    }
    (void)cowl_object_incr_ref(entity);
#endif

    entity->iri = cowl_retain(iri);

    return entity;
}

void cowl_entity_free(CowlAnyEntity *entity) {
    uhset_remove(CowlObjectTable, &inst_tbl, entity);
    cowl_release(cowl_entity_get_iri(entity));
    ulib_free(entity);
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

CowlAnyEntity *cowl_entity_from_string_impl(CowlObjectType type, UString string) {
    CowlEntity *entity = NULL;
    CowlIRI *iri = cowl_iri_from_string(string);

    if (iri) {
        entity = cowl_entity_get_impl(type, iri);
        cowl_release(iri);
    }

    return entity;
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

CowlIRI *cowl_entity_get_iri(CowlAnyEntity *entity) {
    return ((CowlEntity *)entity)->iri;
}

bool cowl_entity_is_reserved(CowlAnyEntity *entity) {
    return cowl_iri_is_reserved(cowl_entity_get_iri(entity));
}

#if COWL_ENTITY_IDS

ulib_uint cowl_entity_get_id(CowlAnyEntity *entity) {
    return ((CowlEntity *)entity)->id;
}

CowlAnyEntity *cowl_entity_with_id(ulib_uint id) {
    return id < uvec_count(CowlObjectPtr, &id_map) ? uvec_get(CowlObjectPtr, &id_map, id) : NULL;
}

#endif
