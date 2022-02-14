/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NAMED_IND_PRIVATE_H
#define COWL_NAMED_IND_PRIVATE_H

#include "cowl_named_ind.h"
#include "cowl_individual_private.h"

COWL_BEGIN_DECLS

struct CowlNamedInd {
    CowlIndividual super;
    CowlIRI *iri;
};

cowl_ret cowl_named_ind_api_init(void);
void cowl_named_ind_api_deinit(void);

COWL_END_DECLS

#endif //COWL_NAMED_IND_PRIVATE_H
