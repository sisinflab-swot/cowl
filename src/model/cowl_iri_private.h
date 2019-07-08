/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_IRI_PRIVATE_H
#define COWL_IRI_PRIVATE_H

#include "cowl_iri.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlIRI) {
    CowlObject super;
    CowlString *ns;
    CowlString *rem;
};

CowlIRI* cowl_iri_get(CowlString *ns, CowlString *rem);

COWL_END_DECLS

#endif // COWL_IRI_PRIVATE_H
