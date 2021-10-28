/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SUB_DATA_PROP_AXIOM_PRIVATE_H
#define COWL_SUB_DATA_PROP_AXIOM_PRIVATE_H

#include "cowl_sub_data_prop_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlSubDataPropAxiom,
    CowlDataPropExp *super_prop;
    CowlDataPropExp *sub_prop;
);

COWL_END_DECLS

#endif // COWL_SUB_DATA_PROP_AXIOM_PRIVATE_H
