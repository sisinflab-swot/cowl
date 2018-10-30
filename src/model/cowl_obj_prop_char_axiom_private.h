/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_CHAR_AXIOM_PRIVATE_H
#define COWL_OBJ_PROP_CHAR_AXIOM_PRIVATE_H

#include "cowl_obj_prop_char_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

struct CowlObjPropCharAxiom {
    CowlAxiom super;
    CowlObjPropExp *prop_exp;
};

COWL_END_DECLS

#endif // COWL_OBJ_PROP_CHAR_AXIOM_PRIVATE_H
