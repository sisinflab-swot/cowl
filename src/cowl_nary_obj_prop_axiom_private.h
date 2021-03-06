/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_OBJ_PROP_AXIOM_PRIVATE_H
#define COWL_NARY_OBJ_PROP_AXIOM_PRIVATE_H

#include "cowl_nary_obj_prop_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlNAryObjPropAxiom,
    CowlObjPropExpSet *props;
);

COWL_END_DECLS

#endif // COWL_NARY_OBJ_PROP_AXIOM_PRIVATE_H
