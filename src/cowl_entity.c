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

CowlEntity* cowl_entity_retain(CowlEntity *entity) {
    return cowl_object_retain(entity);
}

void cowl_entity_release(CowlEntity *entity) {

#define GEN_RELEASE(UC, LC) cowl_##LC##_release((Cowl##UC *)entity); break

    switch (cowl_entity_get_type(entity)) {
        case COWL_ET_CLASS: GEN_RELEASE(Class, class);
        case COWL_ET_OBJ_PROP: GEN_RELEASE(ObjProp, obj_prop);
        case COWL_ET_NAMED_IND: GEN_RELEASE(NamedInd, named_ind);
        case COWL_ET_DATA_PROP: GEN_RELEASE(DataProp, data_prop);
        case COWL_ET_DATATYPE: GEN_RELEASE(Datatype, datatype);
        case COWL_ET_ANNOT_PROP: GEN_RELEASE(AnnotProp, annot_prop);
        default: break;
    }
}

CowlEntityType cowl_entity_get_type(CowlEntity *entity) {
    switch(cowl_get_type(entity)) {
        case COWL_OT_CE_CLASS: return COWL_ET_CLASS;
        case COWL_OT_OPE_OBJ_PROP: return COWL_ET_OBJ_PROP;
        case COWL_OT_I_NAMED: return COWL_ET_NAMED_IND;
        case COWL_OT_DPE_DATA_PROP: return COWL_ET_DATA_PROP;
        case COWL_OT_DR_DATATYPE: return COWL_ET_DATATYPE;
        default: return COWL_ET_ANNOT_PROP;
    }
}

CowlIRI* cowl_entity_get_iri(CowlEntity *entity) {

#define GEN_IRI(UC, LC) return cowl_##LC##_get_iri((Cowl##UC *)entity)

    switch (cowl_entity_get_type(entity)) {
        case COWL_ET_CLASS: GEN_IRI(Class, class);
        case COWL_ET_OBJ_PROP: GEN_IRI(ObjProp, obj_prop);
        case COWL_ET_NAMED_IND: GEN_IRI(NamedInd, named_ind);
        case COWL_ET_DATA_PROP: GEN_IRI(DataProp, data_prop);
        case COWL_ET_DATATYPE: GEN_IRI(Datatype, datatype);
        case COWL_ET_ANNOT_PROP: GEN_IRI(AnnotProp, annot_prop);
        default: return NULL;
    }
}

CowlString* cowl_entity_to_string(CowlEntity *entity)
    COWL_TO_STRING_IMPL(entity, entity)

bool cowl_entity_equals(CowlEntity *lhs, CowlEntity *rhs) {
    return lhs == rhs;
}

cowl_uint cowl_entity_hash(CowlEntity *entity) {

#define GEN_HASH(UC, LC) return cowl_##LC##_hash((Cowl##UC *)entity)

    switch (cowl_entity_get_type(entity)) {
        case COWL_ET_CLASS: GEN_HASH(Class, class);
        case COWL_ET_OBJ_PROP: GEN_HASH(ObjProp, obj_prop);
        case COWL_ET_NAMED_IND: GEN_HASH(NamedInd, named_ind);
        case COWL_ET_DATA_PROP: GEN_HASH(DataProp, data_prop);
        case COWL_ET_DATATYPE: GEN_HASH(Datatype, datatype);
        case COWL_ET_ANNOT_PROP: GEN_HASH(AnnotProp, annot_prop);
        default: return 0;
    }
}

bool cowl_entity_iterate_primitives(CowlEntity *entity, CowlIterator *iter,
                                    CowlPrimitiveFlags flags) {

#define GEN_ITER(UC, LC) return cowl_##LC##_iterate_primitives((Cowl##UC *)entity, iter, flags)

    switch (cowl_entity_get_type(entity)) {
        case COWL_ET_CLASS: GEN_ITER(Class, class);
        case COWL_ET_OBJ_PROP: GEN_ITER(ObjProp, obj_prop);
        case COWL_ET_NAMED_IND: GEN_ITER(NamedInd, named_ind);
        case COWL_ET_DATA_PROP: GEN_ITER(DataProp, data_prop);
        case COWL_ET_DATATYPE: GEN_ITER(Datatype, datatype);
        case COWL_ET_ANNOT_PROP: GEN_ITER(AnnotProp, annot_prop);
        default: return true;
    }
}
