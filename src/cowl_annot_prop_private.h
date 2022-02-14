/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_PROP_PRIVATE_H
#define COWL_ANNOT_PROP_PRIVATE_H

#include "cowl_annot_prop.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

struct CowlAnnotProp {
    CowlObject super;
    CowlIRI *iri;
};

cowl_ret cowl_annot_prop_api_init(void);
void cowl_annot_prop_api_deinit(void);

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_PRIVATE_H
