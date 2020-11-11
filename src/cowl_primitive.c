/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_primitive.h"
#include "cowl_annot_prop_private.h"
#include "cowl_anon_ind.h"
#include "cowl_class_private.h"
#include "cowl_data_prop_private.h"
#include "cowl_datatype_private.h"
#include "cowl_named_ind_private.h"
#include "cowl_obj_prop_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlPrimitive* cowl_primitive_retain(CowlPrimitive *primitive) {
    return cowl_object_retain(primitive);
}

void cowl_primitive_release(CowlPrimitive *primitive) {

#define GEN_RELEASE(UC, LC) cowl_##LC##_release((Cowl##UC *)primitive); break

    switch (cowl_primitive_get_type(primitive)) {
        case COWL_PT_CLASS: GEN_RELEASE(Class, class);
        case COWL_PT_OBJ_PROP: GEN_RELEASE(ObjProp, obj_prop);
        case COWL_PT_NAMED_IND: GEN_RELEASE(NamedInd, named_ind);
        case COWL_PT_ANON_IND: GEN_RELEASE(AnonInd, anon_ind);
        case COWL_PT_DATA_PROP: GEN_RELEASE(DataProp, data_prop);
        case COWL_PT_DATATYPE: GEN_RELEASE(Datatype, datatype);
        case COWL_PT_ANNOT_PROP: GEN_RELEASE(AnnotProp, annot_prop);
        default: break;
    }
}

CowlPrimitiveType cowl_primitive_get_type(CowlPrimitive *primitive) {
    switch(cowl_get_type(primitive)) {
        case COWL_OT_CE_CLASS: return COWL_PT_CLASS;
        case COWL_OT_OPE_OBJ_PROP: return COWL_PT_OBJ_PROP;
        case COWL_OT_I_NAMED: return COWL_PT_NAMED_IND;
        case COWL_OT_I_ANONYMOUS: return COWL_PT_ANON_IND;
        case COWL_OT_DPE_DATA_PROP: return COWL_PT_DATA_PROP;
        case COWL_OT_DR_DATATYPE: return COWL_PT_DATATYPE;
        default: return COWL_PT_ANNOT_PROP;
    }
}

bool cowl_primitive_is_entity(CowlPrimitive *primitive) {
    return cowl_primitive_get_type(primitive) != COWL_PT_ANON_IND;
}

CowlString* cowl_primitive_to_string(CowlPrimitive *primitive)
    COWL_TO_STRING_IMPL(primitive, primitive)

bool cowl_primitive_equals(CowlPrimitive *lhs, CowlPrimitive *rhs) {
    return lhs == rhs;
}

cowl_uint cowl_primitive_hash(CowlPrimitive *primitive) {

#define GEN_HASH(UC, LC) return cowl_##LC##_hash((Cowl##UC *)primitive)

    switch (cowl_primitive_get_type(primitive)) {
        case COWL_PT_CLASS: GEN_HASH(Class, class);
        case COWL_PT_OBJ_PROP: GEN_HASH(ObjProp, obj_prop);
        case COWL_PT_NAMED_IND: GEN_HASH(NamedInd, named_ind);
        case COWL_PT_ANON_IND: GEN_HASH(AnonInd, anon_ind);
        case COWL_PT_DATA_PROP: GEN_HASH(DataProp, data_prop);
        case COWL_PT_DATATYPE: GEN_HASH(Datatype, datatype);
        case COWL_PT_ANNOT_PROP: GEN_HASH(AnnotProp, annot_prop);
        default: return 0;
    }
}

bool cowl_primitive_iterate_primitives(CowlPrimitive *primitive, CowlIterator *iter,
                                       CowlPrimitiveFlags flags) {

#define GEN_ITER(UC, LC) return cowl_##LC##_iterate_primitives((Cowl##UC *)primitive, iter, flags)

    switch (cowl_primitive_get_type(primitive)) {
        case COWL_PT_CLASS: GEN_ITER(Class, class);
        case COWL_PT_OBJ_PROP: GEN_ITER(ObjProp, obj_prop);
        case COWL_PT_NAMED_IND: GEN_ITER(NamedInd, named_ind);
        case COWL_PT_ANON_IND: GEN_ITER(AnonInd, anon_ind);
        case COWL_PT_DATA_PROP: GEN_ITER(DataProp, data_prop);
        case COWL_PT_DATATYPE: GEN_ITER(Datatype, datatype);
        case COWL_PT_ANNOT_PROP: GEN_ITER(AnnotProp, annot_prop);
        default: return true;
    }
}
