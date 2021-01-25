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
#include "cowl_object_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlPrimitive* cowl_primitive_retain(CowlPrimitive *primitive) {
    return cowl_object_incr_ref(primitive);
}

void cowl_primitive_release(CowlPrimitive *primitive) {
    cowl_object_release((CowlObject *)primitive);
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
    return uhash_ptr_hash(primitive);
}

bool cowl_primitive_iterate_primitives(CowlPrimitive *primitive, CowlIterator *iter,
                                       CowlPrimitiveFlags flags) {
    return cowl_object_iterate_primitives((CowlObject *)primitive, iter, flags);
}
