/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_PRIVATE_H
#define COWL_OBJ_PROP_PRIVATE_H

#include "cowl_obj_prop.h"
#include "cowl_obj_prop_exp_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlObjProp) {
    CowlObjPropExp super;
    CowlIRI *iri;
};

COWL_END_DECLS

#endif // COWL_OBJ_PROP_PRIVATE_H
