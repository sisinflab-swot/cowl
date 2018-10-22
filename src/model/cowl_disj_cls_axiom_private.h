/// @author Ivano Bilenchi

#ifndef COWL_DISJ_CLS_AXIOM_PRIVATE_H
#define COWL_DISJ_CLS_AXIOM_PRIVATE_H

#include "cowl_disj_cls_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

struct CowlDisjClsAxiom {
    CowlAxiom super;
    CowlClsExpSet *classes;
};

COWL_END_DECLS

#endif // COWL_DISJ_CLS_AXIOM_PRIVATE_H
