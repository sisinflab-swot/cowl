/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_primitive.h"

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
