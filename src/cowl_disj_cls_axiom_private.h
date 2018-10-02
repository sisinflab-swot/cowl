/// @author Ivano Bilenchi

#ifndef COWL_DISJ_CLS_AXIOM_PRIVATE_H
#define COWL_DISJ_CLS_AXIOM_PRIVATE_H

#include "cowl_disj_cls_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

typedef struct CowlDisjClsAxiom {
    CowlAxiom super;
    khash_t(CowlClsExpSet) const *classes;
} CowlDisjClsAxiom;

COWL_END_DECLS

#endif // COWL_DISJ_CLS_AXIOM_PRIVATE_H
