/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_EXP_PRIVATE_H
#define COWL_DATA_PROP_EXP_PRIVATE_H

#include "cowl_data_prop_exp.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

struct CowlDataPropExp {
    CowlObject super;
};

#define COWL_DATA_PROP_EXP_INIT { .super = COWL_OBJECT_INIT(COWL_OT_DPE_DATA_PROP) }

COWL_END_DECLS

#endif // COWL_DATA_PROP_EXP_PRIVATE_H
