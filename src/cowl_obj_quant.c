/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_quant_private.h"
#include "cowl_hash_utils.h"
#include "cowl_macros.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_template.h"

static CowlObjQuant* cowl_obj_quant_alloc(CowlClsExpType type, CowlObjPropExp *prop,
                                          CowlClsExp *filler) {
    CowlObjQuant *restr = ulib_alloc(restr);
    if (!restr) return NULL;

    ulib_uint hash = cowl_hash_3(COWL_HASH_INIT_OBJ_QUANT, type,
                                 cowl_obj_prop_exp_hash(prop), cowl_cls_exp_hash(filler));

    *restr = (CowlObjQuant) {
        .super = COWL_CLS_EXP_INIT(type, hash),
        .prop = cowl_obj_prop_exp_retain(prop),
        .filler = cowl_cls_exp_retain(filler)
    };

    return restr;
}

static void cowl_obj_quant_free(CowlObjQuant *restr) {
    cowl_obj_prop_exp_release(restr->prop);
    cowl_cls_exp_release(restr->filler);
    ulib_free(restr);
}

CowlObjQuant* cowl_obj_quant_get(CowlQuantType type, CowlObjPropExp *prop, CowlClsExp *filler) {
    if (!(prop && filler && cowl_enum_value_is_valid(QT, type))) return NULL;
    return cowl_obj_quant_alloc(COWL_CET_OBJ_SOME + type, prop, filler);
}

CowlObjQuant* cowl_obj_quant_retain(CowlObjQuant *restr) {
    return cowl_object_incr_ref(restr);
}

void cowl_obj_quant_release(CowlObjQuant *restr) {
    if (restr && !cowl_object_decr_ref(restr)) {
        cowl_obj_quant_free(restr);
    }
}

CowlQuantType cowl_obj_quant_get_type(CowlObjQuant *restr) {
    return (CowlQuantType)(cowl_get_type(restr) - COWL_OT_CE_OBJ_SOME);
}

CowlObjPropExp* cowl_obj_quant_get_prop(CowlObjQuant *restr) {
    return restr->prop;
}

CowlClsExp* cowl_obj_quant_get_filler(CowlObjQuant *restr) {
    return restr->filler;
}

CowlString* cowl_obj_quant_to_string(CowlObjQuant *restr)
    COWL_TO_STRING_IMPL(obj_quant, restr)

bool cowl_obj_quant_equals(CowlObjQuant *lhs, CowlObjQuant *rhs) {
    return cowl_object_type_equals(lhs, rhs) &&
           cowl_object_hash_equals(lhs, rhs) &&
           cowl_obj_prop_exp_equals(lhs->prop, rhs->prop) &&
           cowl_cls_exp_equals(lhs->filler, rhs->filler);
}

ulib_uint cowl_obj_quant_hash(CowlObjQuant *restr) {
    return cowl_object_hash_get(restr);
}

bool cowl_obj_quant_iterate_primitives(CowlObjQuant *restr, CowlPrimitiveFlags flags,
                                       CowlIterator *iter) {
    return (cowl_obj_prop_exp_iterate_primitives(restr->prop, flags, iter) &&
            cowl_cls_exp_iterate_primitives(restr->filler, flags, iter));
}
