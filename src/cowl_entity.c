/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_entity.h"
#include "cowl_annot_prop.h"
#include "cowl_class.h"
#include "cowl_data_prop.h"
#include "cowl_datatype.h"
#include "cowl_named_ind.h"
#include "cowl_obj_prop.h"

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
