/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CLS_EXP_PRIVATE_H
#define COWL_CLS_EXP_PRIVATE_H

#include "cowl_cls_exp.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlClsExp) {
    CowlHashObject super;
    CowlClsExpType type;
};

#define COWL_CLS_EXP_INIT(T, H) { .super = COWL_HASH_OBJECT_INIT(H), .type = (T) }

COWL_END_DECLS

#endif // COWL_CLS_EXP_PRIVATE_H
