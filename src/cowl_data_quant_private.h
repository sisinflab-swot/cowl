/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_QUANT_PRIVATE_H
#define COWL_DATA_QUANT_PRIVATE_H

#include "cowl_data_quant.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

struct CowlDataQuant {
    CowlClsExp super;
    CowlDataPropExp *prop;
    CowlDataRange *range;
};

COWL_END_DECLS

#endif // COWL_DATA_QUANT_PRIVATE_H
