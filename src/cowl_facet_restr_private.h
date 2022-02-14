/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_FACET_RESTR_PRIVATE_H
#define COWL_FACET_RESTR_PRIVATE_H

#include "cowl_facet_restr.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

struct CowlFacetRestr {
    CowlHashObject super;
    CowlFacet facet;
    CowlLiteral *value;
};

COWL_END_DECLS

#endif // COWL_FACET_RESTR_PRIVATE_H
