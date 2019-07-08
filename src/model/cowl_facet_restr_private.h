/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_FACET_RESTR_PRIVATE_H
#define COWL_FACET_RESTR_PRIVATE_H

#include "cowl_facet_restr.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlFacetRestr) {
    CowlHashObject super;
    CowlFacet facet;
    CowlLiteral *value;
};

#define COWL_FACET_RESTR_INIT(F, V, H) \
    { .super = COWL_HASH_OBJECT_INIT(H), .facet = (F), .value = (V) }

COWL_END_DECLS

#endif // COWL_FACET_RESTR_PRIVATE_H
