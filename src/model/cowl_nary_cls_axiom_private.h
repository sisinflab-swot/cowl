/// @author Ivano Bilenchi

#ifndef COWL_NARY_CLS_AXIOM_PRIVATE_H
#define COWL_NARY_CLS_AXIOM_PRIVATE_H

#include "cowl_nary_cls_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

struct CowlNAryClsAxiom {
    CowlAxiom super;
    CowlClsExpSet *classes;
};

COWL_END_DECLS

#endif // COWL_NARY_CLS_AXIOM_PRIVATE_H
