/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANON_IND_PRIVATE_H
#define COWL_ANON_IND_PRIVATE_H

#include "cowl_anon_ind.h"
#include "cowl_object_private.h"
#include "cowl_ret.h"

COWL_BEGIN_DECLS

struct CowlAnonInd {
    CowlObject super;
    CowlString *id;
};

cowl_ret cowl_anon_ind_api_init(void);
void cowl_anon_ind_api_deinit(void);

void cowl_anon_ind_free(CowlAnonInd *ind);

COWL_END_DECLS

#endif // COWL_ANON_IND_PRIVATE_H
