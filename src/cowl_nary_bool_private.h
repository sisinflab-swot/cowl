/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_BOOL_PRIVATE_H
#define COWL_NARY_BOOL_PRIVATE_H

#include "cowl_nary_bool.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlNAryBool) {
    CowlClsExp super;
    CowlObjectTable *operands;
};

COWL_END_DECLS

#endif // COWL_NARY_BOOL_PRIVATE_H
