/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_primitive.h"

#include "cowl_annot_prop_private.h"
#include "cowl_anon_ind_private.h"
#include "cowl_class_private.h"
#include "cowl_data_prop_private.h"
#include "cowl_datatype_private.h"
#include "cowl_named_ind_private.h"
#include "cowl_obj_prop_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlPrimitive cowl_primitive_retain(CowlPrimitive primitive) {

#define GEN_CASE_RETAIN(CPT, PREFIX, FIELD) \
    case CPT: PREFIX##_retain(primitive.FIELD); break

    switch (primitive.type) {
        GEN_CASE_RETAIN(COWL_PT_CLASS, cowl_class, owl_class);
        GEN_CASE_RETAIN(COWL_PT_OBJ_PROP, cowl_obj_prop, obj_prop);
        GEN_CASE_RETAIN(COWL_PT_NAMED_IND, cowl_named_ind, named_ind);
        GEN_CASE_RETAIN(COWL_PT_DATA_PROP, cowl_data_prop, data_prop);
        GEN_CASE_RETAIN(COWL_PT_DATATYPE, cowl_datatype, datatype);
        GEN_CASE_RETAIN(COWL_PT_ANNOT_PROP, cowl_annot_prop, annot_prop);
        GEN_CASE_RETAIN(COWL_PT_ANON_IND, cowl_anon_ind, anon_ind);
        default: break;
    }

    return primitive;
}

void cowl_primitive_release(CowlPrimitive primitive) {

#define GEN_CASE_RELEASE(CPT, PREFIX, FIELD) \
    case CPT: PREFIX##_release(primitive.FIELD); break

    switch (primitive.type) {
        GEN_CASE_RELEASE(COWL_PT_CLASS, cowl_class, owl_class);
        GEN_CASE_RELEASE(COWL_PT_OBJ_PROP, cowl_obj_prop, obj_prop);
        GEN_CASE_RELEASE(COWL_PT_NAMED_IND, cowl_named_ind, named_ind);
        GEN_CASE_RELEASE(COWL_PT_DATA_PROP, cowl_data_prop, data_prop);
        GEN_CASE_RELEASE(COWL_PT_DATATYPE, cowl_datatype, datatype);
        GEN_CASE_RELEASE(COWL_PT_ANON_IND, cowl_anon_ind, anon_ind);
        default: break;
    }
}

CowlIRI* cowl_primitive_get_iri(CowlPrimitive primitive) {
    CowlEntity entity;
    if (cowl_primitive_get_entity(primitive, &entity)) {
        return cowl_entity_get_iri(entity);
    } else {
        return NULL;
    }
}

bool cowl_primitive_get_entity(CowlPrimitive primitive, CowlEntity *entity) {
    
#define GEN_CASE_GET_ENTITY(CPT, F) \
    case CPT: *entity = (CowlEntity){ .type = (CowlEntityType)(CPT), .F = primitive.F }; return true
    
    switch (primitive.type) {
        GEN_CASE_GET_ENTITY(COWL_PT_CLASS, owl_class);
        GEN_CASE_GET_ENTITY(COWL_PT_OBJ_PROP, obj_prop);
        GEN_CASE_GET_ENTITY(COWL_PT_NAMED_IND, named_ind);
        GEN_CASE_GET_ENTITY(COWL_PT_DATA_PROP, data_prop);
        GEN_CASE_GET_ENTITY(COWL_PT_DATATYPE, datatype);
        GEN_CASE_GET_ENTITY(COWL_PT_ANNOT_PROP, annot_prop);
        default: return false;
    }
}

CowlPrimitive cowl_primitive_from_entity(CowlEntity entity) {

#define GEN_CASE_FROM_ENTITY(CET, F) \
    case CET: return (CowlPrimitive){ .type = (CowlPrimitiveType)(CET), .F = entity.F }

    switch (entity.type) {
        GEN_CASE_FROM_ENTITY(COWL_ET_CLASS, owl_class);
        GEN_CASE_FROM_ENTITY(COWL_ET_OBJ_PROP, obj_prop);
        GEN_CASE_FROM_ENTITY(COWL_ET_NAMED_IND, named_ind);
        GEN_CASE_FROM_ENTITY(COWL_ET_DATA_PROP, data_prop);
        GEN_CASE_FROM_ENTITY(COWL_ET_DATATYPE, datatype);
        GEN_CASE_FROM_ENTITY(COWL_ET_ANNOT_PROP, annot_prop);
        default: abort();
    }
}

CowlString* cowl_primitive_to_string(CowlPrimitive primitive)
    COWL_TO_STRING_IMPL(primitive, primitive)

bool cowl_primitive_equals(CowlPrimitive lhs, CowlPrimitive rhs) {
    if (lhs.type != rhs.type) return false;

#define GEN_CASE_EQUALS(CPT, PREFIX, FIELD) \
    case CPT: return PREFIX##_equals(lhs.FIELD, rhs.FIELD)

    switch (lhs.type) {
        GEN_CASE_EQUALS(COWL_PT_CLASS, cowl_class, owl_class);
        GEN_CASE_EQUALS(COWL_PT_OBJ_PROP, cowl_obj_prop, obj_prop);
        GEN_CASE_EQUALS(COWL_PT_NAMED_IND, cowl_named_ind, named_ind);
        GEN_CASE_EQUALS(COWL_PT_DATA_PROP, cowl_data_prop, data_prop);
        GEN_CASE_EQUALS(COWL_PT_DATATYPE, cowl_datatype, datatype);
        GEN_CASE_EQUALS(COWL_PT_ANNOT_PROP, cowl_annot_prop, annot_prop);
        GEN_CASE_EQUALS(COWL_PT_ANON_IND, cowl_anon_ind, anon_ind);
        default: return false;
    }
}

cowl_uint_t cowl_primitive_hash(CowlPrimitive primitive) {

#define GEN_CASE_HASH(CPT, PREFIX, FIELD) \
    case CPT: return PREFIX##_hash(primitive.FIELD)

    switch (primitive.type) {
        GEN_CASE_HASH(COWL_PT_CLASS, cowl_class, owl_class);
        GEN_CASE_HASH(COWL_PT_OBJ_PROP, cowl_obj_prop, obj_prop);
        GEN_CASE_HASH(COWL_PT_NAMED_IND, cowl_named_ind, named_ind);
        GEN_CASE_HASH(COWL_PT_DATA_PROP, cowl_data_prop, data_prop);
        GEN_CASE_HASH(COWL_PT_DATATYPE, cowl_datatype, datatype);
        GEN_CASE_HASH(COWL_PT_ANNOT_PROP, cowl_annot_prop, annot_prop);
        GEN_CASE_HASH(COWL_PT_ANON_IND, cowl_anon_ind, anon_ind);
        default: return 0;
    }
}
