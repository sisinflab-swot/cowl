/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CLS_EXP_PRIVATE_H
#define COWL_CLS_EXP_PRIVATE_H

#include "cowl_cls_exp.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

struct CowlClsExp {
    CowlHashObject super;
};

#define COWL_CLS_EXP_INIT(T, H) {                                                                   \
    .super = COWL_HASH_OBJECT_INIT((CowlObjectType)(T) + COWL_OT_CE_CLASS, H)                       \
}

COWL_END_DECLS

#endif // COWL_CLS_EXP_PRIVATE_H
