/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_obj_card.h"
#include "cowl_owl_vocab.h"

CowlObjCard* cowl_obj_card(CowlCardType type, CowlAnyObjPropExp *prop,
                           CowlAnyClsExp *filler, ulib_uint cardinality) {
    if (!cowl_enum_value_is_valid(CT, type)) return NULL;
    if (filler == cowl_owl_vocab()->cls.thing) filler = NULL;
    return cowl_get_impl_1_uint_opt(COWL_OT_CE_OBJ_MIN_CARD + type, prop, cardinality, filler);
}

CowlClsExp* cowl_obj_card_get_filler(CowlObjCard *restr) {
    CowlClsExp *filler = cowl_get_opt_field(restr);
    return filler ? filler : (CowlClsExp *)cowl_owl_vocab()->cls.thing;
}
