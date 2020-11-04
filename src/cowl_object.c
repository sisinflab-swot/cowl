/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_object_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlObjectType cowl_object_get_type(CowlObject *object) {
    return cowl_object_flags_get_type(object->flags);
}

bool cowl_object_is_entity(CowlObject *object) {
    CowlObjectType type = cowl_object_get_type(object);
    return (type == COWL_OT_CE_CLASS || type == COWL_OT_DR_DATATYPE ||
            type == COWL_OT_OPE_OBJ_PROP || type == COWL_OT_DPE_DATA_PROP ||
            type == COWL_OT_ANNOT_PROP || type == COWL_OT_I_NAMED);
}

bool cowl_object_is_axiom(CowlObject *object) {
    CowlObjectType type = cowl_object_get_type(object);
    return type >= COWL_OT_A_DECL && type <= COWL_OT_A_ANNOT_PROP_RANGE;
}

bool cowl_object_is_cls_exp(CowlObject *object) {
    CowlObjectType type = cowl_object_get_type(object);
    return type >= COWL_OT_CE_CLASS && type <= COWL_OT_CE_OBJ_ONE_OF;
}

bool cowl_object_is_obj_prop_exp(CowlObject *object) {
    CowlObjectType type = cowl_object_get_type(object);
    return type >= COWL_OT_OPE_OBJ_PROP && type <= COWL_OT_OPE_INV_OBJ_PROP;
}

bool cowl_object_is_data_prop_exp(CowlObject *object) {
    return cowl_object_get_type(object) == COWL_OT_DPE_DATA_PROP;
}

bool cowl_object_is_individual(CowlObject *object) {
    CowlObjectType type = cowl_object_get_type(object);
    return type >= COWL_OT_I_ANONYMOUS && type <= COWL_OT_I_NAMED;
}

bool cowl_object_is_data_range(CowlObject *object) {
    CowlObjectType type = cowl_object_get_type(object);
    return type >= COWL_OT_DR_DATATYPE && type <= COWL_OT_DR_DATA_ONE_OF;
}

CowlString* cowl_object_to_string(CowlObject *object)
    COWL_TO_STRING_IMPL(object, object)
