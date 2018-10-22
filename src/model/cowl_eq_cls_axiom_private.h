/// @author Ivano Bilenchi

#ifndef COWL_EQ_CLS_AXIOM_PRIVATE_H
#define COWL_EQ_CLS_AXIOM_PRIVATE_H

#include "cowl_eq_cls_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

struct CowlEqClsAxiom {
    CowlAxiom super;
    CowlClsExpSet *classes;
};

COWL_END_DECLS

#endif // COWL_EQ_CLS_AXIOM_PRIVATE_H
