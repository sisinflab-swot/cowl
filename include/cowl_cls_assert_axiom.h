/// @author Ivano Bilenchi

#ifndef COWL_CLS_ASSERT_AXIOM_H
#define COWL_CLS_ASSERT_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp const CowlClsExp;
typedef struct CowlIndividual const CowlIndividual;

typedef struct CowlClsAssertAxiom const CowlClsAssertAxiom;

CowlClsAssertAxiom* cowl_cls_assert_axiom_get(CowlIndividual *ind, CowlClsExp *exp);
CowlClsAssertAxiom* cowl_cls_assert_axiom_retain(CowlClsAssertAxiom *axiom);
void cowl_cls_assert_axiom_release(CowlClsAssertAxiom *axiom);

CowlIndividual* cowl_cls_assert_axiom_get_individual(CowlClsAssertAxiom *axiom);
CowlClsExp* cowl_cls_assert_axiom_get_cls_exp(CowlClsAssertAxiom *axiom);

bool cowl_cls_assert_axiom_equals(CowlClsAssertAxiom *lhs, CowlClsAssertAxiom *rhs);
uint32_t cowl_cls_assert_axiom_hash(CowlClsAssertAxiom *axiom);

bool cowl_cls_assert_axiom_iterate_signature(CowlClsAssertAxiom *axiom,
                                             void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_CLS_ASSERT_AXIOM_H
