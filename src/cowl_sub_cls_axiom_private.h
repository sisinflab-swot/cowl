/// @author Ivano Bilenchi

#ifndef COWL_SUB_CLS_AXIOM_PRIVATE_H
#define COWL_SUB_CLS_AXIOM_PRIVATE_H

#include "cowl_sub_cls_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

typedef struct CowlSubClsAxiom {
    CowlAxiom base;
    CowlClsExp const *super_class;
    CowlClsExp const *sub_class;
} CowlSubClsAxiom;

COWL_END_DECLS

#endif // COWL_SUB_CLS_AXIOM_PRIVATE_H
