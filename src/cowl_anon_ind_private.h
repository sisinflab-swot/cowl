/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANON_IND_PRIVATE_H
#define COWL_ANON_IND_PRIVATE_H

#include "cowl_anon_ind.h"
#include "cowl_individual_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlAnonInd) {
    CowlIndividual super;
    CowlNodeID id;
};

cowl_ret cowl_anon_ind_api_init(void);
void cowl_anon_ind_api_deinit(void);

COWL_END_DECLS

#endif //COWL_ANON_IND_PRIVATE_H
