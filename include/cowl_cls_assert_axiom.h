/// @author Ivano Bilenchi

#ifndef COWL_CLS_ASSERT_AXIOM_H
#define COWL_CLS_ASSERT_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp CowlClsExp;
typedef struct CowlIndividual CowlIndividual;

typedef struct CowlClsAssertAxiom CowlClsAssertAxiom;

CowlIndividual const* cowl_cls_assert_axiom_get_individual(CowlClsAssertAxiom const *axiom);
CowlClsExp const* cowl_cls_assert_axiom_get_cls_exp(CowlClsAssertAxiom const *axiom);

bool cowl_cls_assert_axiom_equals(CowlClsAssertAxiom const *lhs, CowlClsAssertAxiom const *rhs);
uint32_t cowl_cls_assert_axiom_hash(CowlClsAssertAxiom const *axiom);

bool cowl_cls_assert_axiom_iterate_signature(CowlClsAssertAxiom const *axiom,
                                             void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_CLS_ASSERT_AXIOM_H
