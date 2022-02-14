/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_PRIVATE_H
#define COWL_DATA_PROP_PRIVATE_H

#include "cowl_data_prop.h"
#include "cowl_data_prop_exp_private.h"

COWL_BEGIN_DECLS

struct CowlDataProp {
    CowlDataPropExp super;
    CowlIRI *iri;
};

cowl_ret cowl_data_prop_api_init(void);
void cowl_data_prop_api_deinit(void);

COWL_END_DECLS

#endif // COWL_DATA_PROP_PRIVATE_H
