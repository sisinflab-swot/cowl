/// @author Ivano Bilenchi

#ifndef COWL_INV_OBJ_PROP_AXIOM_PRIVATE_H
#define COWL_INV_OBJ_PROP_AXIOM_PRIVATE_H

#include "cowl_inv_obj_prop_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlInvObjPropAxiom,
    CowlObjPropExp *first;
    CowlObjPropExp *second;
);

COWL_END_DECLS

#endif // COWL_INV_OBJ_PROP_AXIOM_PRIVATE_H
