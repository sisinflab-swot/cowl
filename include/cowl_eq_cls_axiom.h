/// @author Ivano Bilenchi

#ifndef COWL_EQ_CLS_AXIOM_H
#define COWL_EQ_CLS_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef khash_struct(CowlClsExpSet) const CowlClsExpSet;

typedef struct CowlEqClsAxiom const CowlEqClsAxiom;

CowlEqClsAxiom* cowl_eq_cls_axiom_get(CowlClsExpSet *classes);
CowlEqClsAxiom* cowl_eq_cls_axiom_retain(CowlEqClsAxiom *axiom);
void cowl_eq_cls_axiom_release(CowlEqClsAxiom *axiom);

CowlClsExpSet* cowl_eq_cls_axiom_get_classes(CowlEqClsAxiom *axiom);

bool cowl_eq_cls_axiom_equals(CowlEqClsAxiom *lhs, CowlEqClsAxiom *rhs);
uint32_t cowl_eq_cls_axiom_hash(CowlEqClsAxiom *axiom);

bool cowl_eq_cls_axiom_iterate_signature(CowlEqClsAxiom *axiom,
                                         void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_EQ_CLS_AXIOM_H
