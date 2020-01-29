/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_PROP_PRIVATE_H
#define COWL_ANNOT_PROP_PRIVATE_H

#include "cowl_annot_prop.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlAnnotProp) {
    CowlObject super;
    CowlIRI *iri;
};

#define COWL_ANNOT_PROP_INIT(IRI) { .super = COWL_OBJECT_INIT, .iri = (IRI) }

void cowl_annot_prop_api_init(void);
void cowl_annot_prop_api_deinit(void);

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_PRIVATE_H
