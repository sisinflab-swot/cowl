/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_CARD_PRIVATE_H
#define COWL_DATA_CARD_PRIVATE_H

#include "cowl_data_card.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

struct CowlDataCard {
    CowlClsExp super;
    ulib_uint cardinality;
    CowlDataPropExp *prop;
    CowlDataRange *range;
};

COWL_END_DECLS

#endif // COWL_DATA_CARD_PRIVATE_H
