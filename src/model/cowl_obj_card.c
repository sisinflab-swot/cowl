/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_card_private.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_hash_utils.h"
#include "cowl_str_buf.h"

static CowlObjCard* cowl_obj_card_alloc(CowlClsExpType type, CowlObjPropExp *prop,
                                        CowlClsExp *filler, cowl_uint_t cardinality) {
    cowl_uint_t hash;

    if (filler) {
        hash = cowl_hash_4(COWL_HASH_INIT_OBJ_CARD, type, cardinality,
                           cowl_obj_prop_exp_hash(prop), cowl_cls_exp_hash(filler));
        cowl_cls_exp_retain(filler);
    } else {
        hash = cowl_hash_3(COWL_HASH_INIT_OBJ_CARD, type, cardinality,
                           cowl_obj_prop_exp_hash(prop));
    }

    CowlObjCard init = {
        .super = COWL_CLS_EXP_INIT(type, hash),
        .prop = cowl_obj_prop_exp_retain(prop),
        .filler = filler,
        .cardinality = cardinality
    };

    cowl_struct(CowlObjCard) *restr = malloc(sizeof(*restr));
    memcpy(restr, &init, sizeof(*restr));
    return restr;
}

static void cowl_obj_card_free(CowlObjCard *restr) {
    if (!restr) return;
    cowl_obj_prop_exp_release(restr->prop);
    cowl_cls_exp_release(restr->filler);
    free((void *)restr);
}

CowlObjCard* cowl_obj_card_get(CowlCardType type, CowlObjPropExp *prop,
                               CowlClsExp *filler, cowl_uint_t cardinality) {
    return cowl_obj_card_alloc(COWL_CET_OBJ_MIN_CARD + type, prop, filler, cardinality);
}

CowlObjCard* cowl_obj_card_retain(CowlObjCard *restr) {
    return cowl_object_retain(restr);
}

void cowl_obj_card_release(CowlObjCard *restr) {
    if (restr && !cowl_object_release(restr)) {
        cowl_obj_card_free(restr);
    }
}

CowlCardType cowl_obj_card_get_type(CowlObjCard *restr) {
    return (CowlCardType)(restr->super.type - COWL_CET_OBJ_MIN_CARD);
}

CowlObjPropExp* cowl_obj_card_get_prop(CowlObjCard *restr) {
    return restr->prop;
}

CowlClsExp* cowl_obj_card_get_filler(CowlObjCard *restr) {
    return restr->filler;
}

cowl_uint_t cowl_obj_card_get_cardinality(CowlObjCard *restr) {
    return restr->cardinality;
}

CowlString* cowl_obj_card_to_string(CowlObjCard *restr) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_obj_card(buf, restr);
    return cowl_str_buf_to_string(buf);
}

bool cowl_obj_card_equals(CowlObjCard *lhs, CowlObjCard *rhs) {
    if (lhs->cardinality != rhs->cardinality || lhs->super.type != rhs->super.type) return false;
    if (!cowl_obj_prop_exp_equals(lhs->prop, rhs->prop)) return false;
    if (lhs->filler == rhs->filler) return true;
    if (lhs->filler && rhs->filler) return cowl_cls_exp_equals(lhs->filler, rhs->filler);
    return false;
}

cowl_uint_t cowl_obj_card_hash(CowlObjCard *restr) {
    return cowl_object_hash_get(restr);
}

bool cowl_obj_card_iterate_signature(CowlObjCard *restr, CowlEntityIterator *iter) {
    if (!cowl_obj_prop_exp_iterate_signature(restr->prop, iter)) return false;
    if (restr->filler && !cowl_cls_exp_iterate_signature(restr->filler, iter)) return false;
    return true;
}
