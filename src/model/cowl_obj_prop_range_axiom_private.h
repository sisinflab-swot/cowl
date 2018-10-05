/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_RANGE_AXIOM_PRIVATE_H
#define COWL_OBJ_PROP_RANGE_AXIOM_PRIVATE_H

#include "cowl_obj_prop_range_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

typedef struct CowlObjPropRangeAxiom {
    CowlAxiom super;
    CowlObjPropExp const *prop_exp;
    CowlClsExp const *range;
} CowlObjPropRangeAxiom;

COWL_END_DECLS

#endif // COWL_OBJ_PROP_RANGE_AXIOM_PRIVATE_H
