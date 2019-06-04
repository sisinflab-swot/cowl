/// @author Ivano Bilenchi

#ifndef COWL_HAS_KEY_AXIOM_PRIVATE_H
#define COWL_HAS_KEY_AXIOM_PRIVATE_H

#include "cowl_has_key_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlHasKeyAxiom) {
    CowlAxiom super;
    CowlClsExp *cls_exp;
    CowlDataPropExpSet *data_props;
    CowlObjPropExpSet *obj_props;
};

COWL_END_DECLS

#endif // COWL_HAS_KEY_AXIOM_PRIVATE_H
