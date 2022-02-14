/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_card_private.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_hash_utils.h"
#include "cowl_macros.h"
#include "cowl_template.h"

static CowlObjCard* cowl_obj_card_alloc(CowlClsExpType type, CowlObjPropExp *prop,
                                        CowlClsExp *filler, ulib_uint cardinality) {
    CowlObjCard *restr = ulib_alloc(restr);
    if (!restr) return NULL;

    ulib_uint hash;

    if (filler) {
        hash = cowl_hash_4(COWL_HASH_INIT_OBJ_CARD, type, cardinality,
                           cowl_obj_prop_exp_hash(prop), cowl_cls_exp_hash(filler));
        cowl_cls_exp_retain(filler);
    } else {
        hash = cowl_hash_3(COWL_HASH_INIT_OBJ_CARD, type, cardinality,
                           cowl_obj_prop_exp_hash(prop));
    }

    *restr = (CowlObjCard) {
        .super = COWL_CLS_EXP_INIT(type, hash),
        .prop = cowl_obj_prop_exp_retain(prop),
        .filler = filler,
        .cardinality = cardinality
    };

    return restr;
}

static void cowl_obj_card_free(CowlObjCard *restr) {
    cowl_obj_prop_exp_release(restr->prop);
    cowl_cls_exp_release(restr->filler);
    ulib_free(restr);
}

CowlObjCard* cowl_obj_card_get(CowlCardType type, CowlObjPropExp *prop,
                               CowlClsExp *filler, ulib_uint cardinality) {
    if (!(prop && cowl_enum_value_is_valid(CT, type))) return NULL;
    return cowl_obj_card_alloc(COWL_CET_OBJ_MIN_CARD + type, prop, filler, cardinality);
}

CowlObjCard* cowl_obj_card_retain(CowlObjCard *restr) {
    return cowl_object_incr_ref(restr);
}

void cowl_obj_card_release(CowlObjCard *restr) {
    if (restr && !cowl_object_decr_ref(restr)) {
        cowl_obj_card_free(restr);
    }
}

CowlCardType cowl_obj_card_get_type(CowlObjCard *restr) {
    return (CowlCardType)(cowl_get_type(restr) - COWL_OT_CE_OBJ_MIN_CARD);
}

CowlObjPropExp* cowl_obj_card_get_prop(CowlObjCard *restr) {
    return restr->prop;
}

CowlClsExp* cowl_obj_card_get_filler(CowlObjCard *restr) {
    return restr->filler;
}

ulib_uint cowl_obj_card_get_cardinality(CowlObjCard *restr) {
    return restr->cardinality;
}

CowlString* cowl_obj_card_to_string(CowlObjCard *restr)
    COWL_TO_STRING_IMPL(obj_card, restr)

bool cowl_obj_card_equals(CowlObjCard *lhs, CowlObjCard *rhs) {
    if (lhs->cardinality != rhs->cardinality) return false;
    if (!cowl_object_type_equals(lhs, rhs)) return false;
    if (!cowl_object_hash_equals(lhs, rhs)) return false;
    if (!cowl_obj_prop_exp_equals(lhs->prop, rhs->prop)) return false;
    if (lhs->filler == rhs->filler) return true;
    if (lhs->filler && rhs->filler) return cowl_cls_exp_equals(lhs->filler, rhs->filler);
    return false;
}

ulib_uint cowl_obj_card_hash(CowlObjCard *restr) {
    return cowl_object_hash_get(restr);
}

bool cowl_obj_card_iterate_primitives(CowlObjCard *restr, CowlPrimitiveFlags flags,
                                      CowlIterator *iter) {
    if (!cowl_obj_prop_exp_iterate_primitives(restr->prop, flags, iter)) return false;
    if (restr->filler && !cowl_cls_exp_iterate_primitives(restr->filler, flags, iter)) return false;
    return true;
}
