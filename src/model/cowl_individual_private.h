/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_INDIVIDUAL_PRIVATE_H
#define COWL_INDIVIDUAL_PRIVATE_H

#include "cowl_individual.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlIndividual) {
    CowlObject super;
    bool is_named;
};

#define COWL_INDIVIDUAL_INIT(N) { .super = COWL_OBJECT_INIT, .is_named = (N) }

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_PRIVATE_H
