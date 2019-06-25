/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_RANGE_AXIOM_PRIVATE_H
#define COWL_OBJ_PROP_RANGE_AXIOM_PRIVATE_H

#include "cowl_obj_prop_range_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlObjPropRangeAxiom,
    CowlObjPropExp *prop_exp;
    CowlClsExp *range;
);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_RANGE_AXIOM_PRIVATE_H
