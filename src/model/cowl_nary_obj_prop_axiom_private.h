/// @author Ivano Bilenchi

#ifndef COWL_NARY_OBJ_PROP_AXIOM_PRIVATE_H
#define COWL_NARY_OBJ_PROP_AXIOM_PRIVATE_H

#include "cowl_nary_obj_prop_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlNAryObjPropAxiom) {
    CowlAxiom super;
    CowlObjPropExpSet *props;
};

COWL_END_DECLS

#endif // COWL_NARY_OBJ_PROP_AXIOM_PRIVATE_H
