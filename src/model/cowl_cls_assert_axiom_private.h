/// @author Ivano Bilenchi

#ifndef COWL_CLS_ASSERT_AXIOM_PRIVATE_H
#define COWL_CLS_ASSERT_AXIOM_PRIVATE_H

#include "cowl_cls_assert_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

struct CowlClsAssertAxiom {
    CowlAxiom super;
    CowlIndividual *individual;
    CowlClsExp *cls_exp;
};

COWL_END_DECLS

#endif // COWL_CLS_ASSERT_AXIOM_PRIVATE_H
