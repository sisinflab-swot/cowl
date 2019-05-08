/// @author Ivano Bilenchi

#ifndef COWL_SUB_CLS_AXIOM_PRIVATE_H
#define COWL_SUB_CLS_AXIOM_PRIVATE_H

#include "cowl_sub_cls_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlSubClsAxiom) {
    CowlAxiom super;
    CowlClsExp *super_class;
    CowlClsExp *sub_class;
};

COWL_END_DECLS

#endif // COWL_SUB_CLS_AXIOM_PRIVATE_H
