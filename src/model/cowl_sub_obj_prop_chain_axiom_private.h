/// @author Ivano Bilenchi

#ifndef COWL_SUB_OBJ_PROP_CHAIN_AXIOM_PRIVATE_H
#define COWL_SUB_OBJ_PROP_CHAIN_AXIOM_PRIVATE_H

#include "cowl_sub_obj_prop_chain_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlSubObjPropChainAxiom,
    CowlObjPropExpVec *sub_props;
    CowlObjPropExp *super_prop;
);

COWL_END_DECLS

#endif // COWL_SUB_OBJ_PROP_CHAIN_AXIOM_PRIVATE_H
