/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_INDIVIDUAL_PRIVATE_H
#define COWL_INDIVIDUAL_PRIVATE_H

#include "cowl_individual.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

struct CowlIndividual {
    CowlObject super;
};

#define COWL_INDIVIDUAL_INIT(N) {                                                                   \
    .super = COWL_OBJECT_INIT((N) ? COWL_OT_I_NAMED : COWL_OT_I_ANONYMOUS)                          \
}

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_PRIVATE_H
