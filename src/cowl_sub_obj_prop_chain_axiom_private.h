/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SUB_OBJ_PROP_CHAIN_AXIOM_PRIVATE_H
#define COWL_SUB_OBJ_PROP_CHAIN_AXIOM_PRIVATE_H

#include "cowl_sub_obj_prop_chain_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlSubObjPropChainAxiom,
    CowlObjectVec *sub_props;
    CowlObjPropExp *super_prop;
);

COWL_END_DECLS

#endif // COWL_SUB_OBJ_PROP_CHAIN_AXIOM_PRIVATE_H
