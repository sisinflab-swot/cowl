/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_entity.h"
#include "cowl_annot_prop_private.h"
#include "cowl_class_private.h"
#include "cowl_data_prop_private.h"
#include "cowl_datatype_private.h"
#include "cowl_named_ind_private.h"
#include "cowl_obj_prop_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlEntity cowl_entity_retain(CowlEntity entity) {

#define GEN_CASE_RETAIN(CET, PREFIX, FIELD) \
    case CET: PREFIX##_retain(entity.FIELD); break

    switch (entity.type) {
        GEN_CASE_RETAIN(COWL_ET_CLASS, cowl_class, owl_class);
        GEN_CASE_RETAIN(COWL_ET_OBJ_PROP, cowl_obj_prop, obj_prop);
        GEN_CASE_RETAIN(COWL_ET_NAMED_IND, cowl_named_ind, named_ind);
        GEN_CASE_RETAIN(COWL_ET_DATA_PROP, cowl_data_prop, data_prop);
        GEN_CASE_RETAIN(COWL_ET_DATATYPE, cowl_datatype, datatype);
        GEN_CASE_RETAIN(COWL_ET_ANNOT_PROP, cowl_annot_prop, annot_prop);
        default: break;
    }

    return entity;
}

void cowl_entity_release(CowlEntity entity) {

#define GEN_CASE_RELEASE(CET, PREFIX, FIELD) \
    case CET: PREFIX##_release(entity.FIELD); break

    switch (entity.type) {
        GEN_CASE_RELEASE(COWL_ET_CLASS, cowl_class, owl_class);
        GEN_CASE_RELEASE(COWL_ET_OBJ_PROP, cowl_obj_prop, obj_prop);
        GEN_CASE_RELEASE(COWL_ET_NAMED_IND, cowl_named_ind, named_ind);
        GEN_CASE_RELEASE(COWL_ET_DATA_PROP, cowl_data_prop, data_prop);
        GEN_CASE_RELEASE(COWL_ET_DATATYPE, cowl_datatype, datatype);
        GEN_CASE_RELEASE(COWL_ET_ANNOT_PROP, cowl_annot_prop, annot_prop);
        default: break;
    }
}

CowlIRI* cowl_entity_get_iri(CowlEntity entity) {

#define GEN_CASE_IRI(CET, FIELD) \
    case CET: return entity.FIELD->iri

    switch (entity.type) {
        GEN_CASE_IRI(COWL_ET_CLASS, owl_class);
        GEN_CASE_IRI(COWL_ET_OBJ_PROP, obj_prop);
        GEN_CASE_IRI(COWL_ET_NAMED_IND, named_ind);
        GEN_CASE_IRI(COWL_ET_DATA_PROP, data_prop);
        GEN_CASE_IRI(COWL_ET_DATATYPE, datatype);
        GEN_CASE_IRI(COWL_ET_ANNOT_PROP, annot_prop);
        default: return NULL;
    }
}

CowlString* cowl_entity_to_string(CowlEntity entity)
    COWL_TO_STRING_IMPL(entity, entity)

bool cowl_entity_equals(CowlEntity lhs, CowlEntity rhs) {
    if (lhs.type != rhs.type) return false;

#define GEN_CASE_EQUALS(CET, PREFIX, FIELD) \
    case CET: return PREFIX##_equals(lhs.FIELD, rhs.FIELD)

    switch (lhs.type) {
        GEN_CASE_EQUALS(COWL_ET_CLASS, cowl_class, owl_class);
        GEN_CASE_EQUALS(COWL_ET_OBJ_PROP, cowl_obj_prop, obj_prop);
        GEN_CASE_EQUALS(COWL_ET_NAMED_IND, cowl_named_ind, named_ind);
        GEN_CASE_EQUALS(COWL_ET_DATA_PROP, cowl_data_prop, data_prop);
        GEN_CASE_EQUALS(COWL_ET_DATATYPE, cowl_datatype, datatype);
        GEN_CASE_EQUALS(COWL_ET_ANNOT_PROP, cowl_annot_prop, annot_prop);
        default: return false;
    }
}

cowl_uint_t cowl_entity_hash(CowlEntity entity) {

#define GEN_CASE_HASH(CET, PREFIX, FIELD) \
    case CET: return PREFIX##_hash(entity.FIELD)

    switch (entity.type) {
        GEN_CASE_HASH(COWL_ET_CLASS, cowl_class, owl_class);
        GEN_CASE_HASH(COWL_ET_OBJ_PROP, cowl_obj_prop, obj_prop);
        GEN_CASE_HASH(COWL_ET_NAMED_IND, cowl_named_ind, named_ind);
        GEN_CASE_HASH(COWL_ET_DATA_PROP, cowl_data_prop, data_prop);
        GEN_CASE_HASH(COWL_ET_DATATYPE, cowl_datatype, datatype);
        GEN_CASE_HASH(COWL_ET_ANNOT_PROP, cowl_annot_prop, annot_prop);
        default: return 0;
    }
}
