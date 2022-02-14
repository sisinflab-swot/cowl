/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_HAS_VALUE_PRIVATE_H
#define COWL_DATA_HAS_VALUE_PRIVATE_H

#include "cowl_data_has_value.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

struct CowlDataHasValue {
    CowlClsExp super;
    CowlDataPropExp *prop;
    CowlLiteral *value;
};

COWL_END_DECLS

#endif // COWL_DATA_HAS_VALUE_PRIVATE_H
