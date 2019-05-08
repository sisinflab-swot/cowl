/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_ASSERT_AXIOM_PRIVATE_H
#define COWL_OBJ_PROP_ASSERT_AXIOM_PRIVATE_H

#include "cowl_obj_prop_assert_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlObjPropAssertAxiom) {
    CowlAxiom super;
    CowlIndividual *source;
    CowlIndividual *target;
    CowlObjPropExp *prop_exp;
};

COWL_END_DECLS

#endif // COWL_OBJ_PROP_ASSERT_AXIOM_PRIVATE_H
