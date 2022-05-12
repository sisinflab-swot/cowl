/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_HAS_KEY_AXIOM_PRIVATE_H
#define COWL_HAS_KEY_AXIOM_PRIVATE_H

#include "cowl_has_key_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlHasKeyAxiom,
    CowlClsExp *cls_exp;
    CowlVector *data_props;
    CowlVector *obj_props;
);

COWL_END_DECLS

#endif // COWL_HAS_KEY_AXIOM_PRIVATE_H
