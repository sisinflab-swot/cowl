/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_FACET_PRIVATE_H
#define COWL_FACET_PRIVATE_H

#include "cowl_facet.h"

COWL_BEGIN_DECLS

cowl_ret cowl_facet_init(void);
void cowl_facet_deinit(void);

#define cowl_facet_foreach(var_name) \
    for (CowlFacet var_name = COWL_FACET_FIRST; (var_name) < COWL_FACET_COUNT; ++(var_name))

COWL_END_DECLS

#endif // COWL_FACET_PRIVATE_H
