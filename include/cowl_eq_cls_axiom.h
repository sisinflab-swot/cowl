/// @author Ivano Bilenchi

#ifndef COWL_EQ_CLS_AXIOM_H
#define COWL_EQ_CLS_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef khash_struct(CowlClsExpSet) khash_t(CowlClsExpSet);

typedef struct CowlEqClsAxiom CowlEqClsAxiom;

khash_t(CowlClsExpSet) const* cowl_eq_cls_axiom_get_classes(CowlEqClsAxiom const *axiom);

bool cowl_eq_cls_axiom_enum_signature(CowlEqClsAxiom const *axiom, void *ctx,
                                      CowlEntityIterator iter);

bool cowl_eq_cls_axiom_equals(CowlEqClsAxiom const *lhs, CowlEqClsAxiom const *rhs);
uint32_t cowl_eq_cls_axiom_hash(CowlEqClsAxiom const *axiom);

COWL_END_DECLS

#endif // COWL_EQ_CLS_AXIOM_H
